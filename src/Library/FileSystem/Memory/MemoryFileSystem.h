#pragma once

#include <utility>
#include <vector>
#include <memory>
#include <string>

#include "Library/FileSystem/Interface/FileSystem.h"
#include "Library/FileSystem/Trie/FileSystemTrie.h"

namespace detail {
struct MemoryFileData {
    Blob blob;
    int readerCount = 0;
    int writerCount = 0;

    explicit MemoryFileData(Blob blob) : blob(std::move(blob)) {}
};
} // namespace detail


/**
 * In-memory file system.
 *
 * Works almost like a regular FS, with some minor differences:
 * - Doesn't support empty folders. If a folder becomes empty, it is instantly deleted.
 * - Doesn't support concurrent reading and writing. If a file is open for writing, all read calls will fail. If
 *   a file is open for reading, all write calls will fail.
 * - Is not thread safe, even if you're only using `const` methods. Use a locking wrapper if you need thread safety.
 *
 * Also, like a proper file system, it allows removing and renaming files while they are open for reading / writing.
 */
class MemoryFileSystem : public FileSystem {
 public:
    explicit MemoryFileSystem(std::string_view displayName);

    void clear();

 private:
    virtual bool _exists(const FileSystemPath &path) const override;
    virtual FileStat _stat(const FileSystemPath &path) const override;
    virtual void _ls(const FileSystemPath &path, std::vector<DirectoryEntry> *entries) const override;
    virtual Blob _read(const FileSystemPath &path) const override;
    virtual void _write(const FileSystemPath &path, const Blob &data) override;
    virtual std::unique_ptr<InputStream> _openForReading(const FileSystemPath &path) const override;
    virtual std::unique_ptr<OutputStream> _openForWriting(const FileSystemPath &path) override;
    virtual void _rename(const FileSystemPath &srcPath, const FileSystemPath &dstPath) override;
    virtual bool _remove(const FileSystemPath &path) override;
    virtual std::string _displayPath(const FileSystemPath &path) const override;

 private:
    using MemoryFileData = detail::MemoryFileData;
    using Node = FileSystemTrieNode<std::shared_ptr<MemoryFileData>>;

    const Node *nodeForReading(const FileSystemPath &path) const;
    Node *nodeForWriting(const FileSystemPath &path);

 private:
    std::string _displayName;
    FileSystemTrie<std::shared_ptr<MemoryFileData>> _trie;
};
