#include "LodReader.h"

#include <cassert>
#include <utility>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <vector>

#include "Library/Compression/Compression.h"
#include "Library/Snapshots/SnapshotSerialization.h"

#include "Utility/Streams/BlobInputStream.h"
#include "Utility/Exception.h"
#include "Utility/String.h"

#include "LodSnapshots.h"
#include "LodEnums.h"

static LodHeader parseHeader(InputStream &stream, std::string_view path, LodVersion *version) {
    LodHeader header;
    deserialize(stream, &header, tags::via<LodHeader_MM6>);

    if (header.signature != "LOD")
        throw Exception("File '{}' is not a valid LOD: expected signature '{}', got '{}'", path, "LOD", toPrintable(header.signature));

    if (!tryDeserialize(header.version, version))
        throw Exception("File '{}' is not a valid LOD: version '{}' is not recognized", path, toPrintable(header.version));

    // While LOD structure itself support multiple directories, all LOD files associated with
    // vanilla MM6/7/8 games use a single directory.
    if (header.numDirectories != 1)
        throw Exception("File '{}' is not a valid LOD: expected a single directory, got '{}' directories", path, header.numDirectories);

    return header;
}

static LodEntry parseDirectoryEntry(InputStream &stream, LodVersion version, std::string_view path, size_t lodSize) {
    LodEntry result;
    deserialize(stream, &result, tags::via<LodEntry_MM6>);

    size_t expectedDataSize = result.numItems * fileEntrySize(version);
    if (result.dataSize < expectedDataSize)
        throw Exception("File '{}' is not a valid LOD: invalid root directory index size, expected at least {} bytes, got {} bytes", path, expectedDataSize, result.dataSize);

    if (result.dataOffset + result.dataSize > lodSize)
        throw Exception("File '{}' is not a valid LOD: root directory index points outside the LOD file", path);

    return result;
}

static std::vector<LodEntry> parseFileEntries(InputStream &stream, const LodEntry &directoryEntry, LodVersion version, std::string_view path) {
    std::vector<LodEntry> result;
    if (version == LOD_VERSION_MM8) {
        deserialize(stream, &result, tags::presized(directoryEntry.numItems), tags::via<LodFileEntry_MM8>);
    } else {
        deserialize(stream, &result, tags::presized(directoryEntry.numItems), tags::via<LodEntry_MM6>);
    }

    for (const LodEntry &entry : result) {
        if (entry.numItems != 0)
            throw Exception("File '{}' is not a valid LOD: subdirectories are not supported, but '{}' is a subdirectory", path, entry.name);
        if (entry.dataOffset + entry.dataSize > directoryEntry.dataSize)
            throw Exception("File '{}' is not a valid LOD: entry '{}' points outside the LOD file", path, entry.name);
    }

    return result;
}


LodReader::LodReader() = default;

LodReader::LodReader(std::string_view path, LodOpenFlags openFlags) {
    open(path, openFlags);
}

LodReader::LodReader(Blob blob, std::string_view path, LodOpenFlags openFlags) {
    open(std::move(blob), path, openFlags);
}

LodReader::~LodReader() {
    close();
}

void LodReader::open(std::string_view path, LodOpenFlags openFlags) {
    open(Blob::fromFile(path), path, openFlags); // Blob::fromFile throws if the file doesn't exist.
}

void LodReader::open(Blob blob, std::string_view path, LodOpenFlags openFlags) {
    close();

    size_t expectedSize = sizeof(LodHeader_MM6) + sizeof(LodEntry_MM6); // Header + directory entry.
    if (blob.size() < expectedSize)
        throw Exception("File '{}' is not a valid LOD: expected file size at least {} bytes, got {} bytes", path, expectedSize, _lod.size());

    BlobInputStream lodStream(blob);
    LodVersion version = LOD_VERSION_MM6;
    LodHeader header = parseHeader(lodStream, path, &version);
    LodEntry rootEntry = parseDirectoryEntry(lodStream, version, path, blob.size());

    // LODs that come with the Russian version of MM7 are broken.
    rootEntry.dataSize = blob.size() - rootEntry.dataOffset;

    BlobInputStream dirStream(blob.subBlob(rootEntry.dataOffset, rootEntry.dataSize));
    std::unordered_map<std::string, LodRegion> files;
    for (const LodEntry &entry : parseFileEntries(dirStream, rootEntry, version, path)) {
        std::string name = toLower(entry.name);
        if (files.contains(name)) {
            if (openFlags & LOD_ALLOW_DUPLICATES) {
                continue; // Only the first entry is kept in this case.
            } else {
                throw Exception("File '{}' is not a valid LOD: contains duplicate entries for '{}'", path, name);
            }
        }

        LodRegion region;
        region.offset = rootEntry.dataOffset + entry.dataOffset;
        region.size = entry.dataSize;
        files.emplace(std::move(name), region);
    }

    // All good, this is a valid LOD, can update `this`.
    _lod = std::move(blob);
    _path = path;
    _info.version = version;
    _info.description = std::move(header.description);
    _info.rootName = std::move(rootEntry.name);
    _files = std::move(files);
}

void LodReader::close() {
    // Double-closing is OK.
    _lod = Blob();
    _path = {};
    _info = {};
    _files = {};
}

bool LodReader::exists(std::string_view filename) const {
    assert(isOpen());

    return _files.contains(toLower(filename));
}

Blob LodReader::read(std::string_view filename) const {
    assert(isOpen());

    const auto pos = _files.find(toLower(filename));
    if (pos == _files.cend())
        throw Exception("Entry '{}' doesn't exist in LOD file '{}'", filename, _path);

    return _lod.subBlob(pos->second.offset, pos->second.size);
}

std::vector<std::string> LodReader::ls() const {
    assert(isOpen());

    std::vector<std::string> result;
    for (const auto &[name, _] : _files)
        result.push_back(name);
    std::sort(result.begin(), result.end());
    return result;
}

[[nodiscard]] const LodInfo &LodReader::info() const {
    assert(isOpen());

    return _info;
}

