#pragma once

#include <vector>
#include <string>
#include <string_view>
#include <memory>
#include <utility>

#include "Utility/Memory/Blob.h"
#include "Utility/Streams/InputStream.h"
#include "Utility/Streams/OutputStream.h"

#include "FileSystemPath.h"
#include "FileSystemEnums.h"
#include "FileSystemFwd.h"

struct FileStat {
    FileStat() = default;
    FileStat(FileType type, std::int64_t size) : type(type), size(size) {}

    FileType type = FILE_INVALID; // Invalid means file doesn't exist.
    std::int64_t size = 0; // Always zero for directories.

    explicit operator bool() const {
        return type != FILE_INVALID;
    }

    friend bool operator==(const FileStat &l, const FileStat &r) = default;
};

struct DirectoryEntry {
    DirectoryEntry() = default;
    DirectoryEntry(std::string name, FileType type) : name(std::move(name)), type(type) {}

    std::string name;
    FileType type = FILE_INVALID; // When returned from FileSystem::ls, this one is never invalid.

    friend bool operator==(const DirectoryEntry &l, const DirectoryEntry &r) = default;
};

/**
 * File system interface.
 *
 * All user-facing methods take paths as UTF8-encoded `std::string_view`s, and users are expected to just use
 * `std::string`s to store paths.
 *
 * Paths are normalized internally, and then processed by the implementation in a derived class. Both `".."` and `"."`
 * special dirs are supported, but peeking outside of the root directory is not - root is considered a parent of itself,
 * so `"../.."` is normalized into an empty path.
 *
 * Unlike a real file system, this interface doesn't have a concept of a "current directory." All methods take
 * root-relative paths, so `"foo/bar"` and `"/foo/bar"` are equivalent.
 *
 * Root folder of the file system always exists. Thus, `exists("")` always returns `true`, `stat("")` always returns
 * `FILE_DIRECTORY`, `ls("")` never throws, `remove("")` and `rename("", "foo")` always throw.
 *
 * @see ReadOnlyFileSystem
 */
class FileSystem {
 public:
    FileSystem() = default;
    virtual ~FileSystem() = default;

    /**
     * @param path                      Path to check.
     * @return                          Whether the given path exists.
     * @throws std::runtime_error       On error, e.g. if the current user doesn't have the necessary permissions.
     */
    [[nodiscard]] bool exists(std::string_view path) const;
    [[nodiscard]] bool exists(const FileSystemPath &path) const;

    /**
     * @param path                      Path to a file of a folder to get information for.
     * @return                          Information for a file or directory at `path`. `FileStat::type` will be set to
     *                                  `FILE_INVALID` if `path` doesn't exist.
     * @throws std::runtime_error       On error, e.g. if the current user doesn't have the necessary permissions.
     */
    [[nodiscard]] FileStat stat(std::string_view path) const;
    [[nodiscard]] FileStat stat(const FileSystemPath &path) const;

    /**
     * @param path                      Path to an existing directory to list.
     * @return                          List of directory entries.
     * @throws std::runtime_error       If `path` doesn't exist, or on any other error.
     */
    [[nodiscard]] std::vector<DirectoryEntry> ls(std::string_view path) const;
    [[nodiscard]] std::vector<DirectoryEntry> ls(const FileSystemPath &path) const;

    /**
     * @param path                      Path to an existing file to read or map into memory.
     * @return                          File contents. Implementations are encouraged to use memory mapping.
     * @throws std::runtime_error       If `path` doesn't exist, or on any other error.
     */
    [[nodiscard]] Blob read(std::string_view path) const;
    [[nodiscard]] Blob read(const FileSystemPath &path) const;

    /**
     * @param path                      Path to a file to write. If parent directory doesn't exist, it will be created.
     *                                  If a file with the provided name exists, it will be overwritten.
     * @param data                      File contents to write.
     * @throws std::runtime_error       On error, e.g. if the current user doesn't have the necessary permissions.
     */
    void write(std::string_view path, const Blob &data);
    void write(const FileSystemPath &path, const Blob &data);

    /**
     * @param path                      Path to an existing file to open for reading.
     * @return                          Input stream for reading from a file.
     * @throws std::runtime_error       If `path` doesn't exist, or on any other error.
     */
    [[nodiscard]] std::unique_ptr<InputStream> openForReading(std::string_view path) const;
    [[nodiscard]] std::unique_ptr<InputStream> openForReading(const FileSystemPath &path) const;

    /**
     * @param path                      Path to a file to write. If parent directory doesn't exist, it will be created.
     *                                  If a file with the provided name exists, it will be overwritten.
     * @return                          Output stream for writing into a file.
     * @throws std::runtime_error       On error, e.g. if the current user doesn't have the necessary permissions.
     */
    [[nodiscard]] std::unique_ptr<OutputStream> openForWriting(std::string_view path);
    [[nodiscard]] std::unique_ptr<OutputStream> openForWriting(const FileSystemPath &path);

    /**
     * Renames a file or a folder.
     *
     * Default implementation removes `dstPath` first, then copies the `srcPath` over, then removes `srcPath`.
     *
     * Derived classes working on top of an actual file system might implement this using POSIX `rename`.
     *
     * @param srcPath                   Source path for renaming. Path must exist and must not be root.
     * @param dstPath                   Target path for renaming. If source path is a directory, then target path must
     *                                  not exist. If source path is a file, then target path must either not exist, or
     *                                  be a file. If parent directory of `dstPath` doesn't exist, it will be created.
     * @throws std::runtime_error       On error, e.g. if the current user doesn't have the necessary permissions.
     */
    void rename(std::string_view srcPath, std::string_view dstPath);
    void rename(const FileSystemPath &srcPath, const FileSystemPath &dstPath);

    /**
     * @param path                      Path to a file or a directory to remove. A directory will be removed even if it
     *                                  is not empty. Must not be root.
     * @return                          `true` if the file or folder was deleted, `false` if it did not exist.
     * @throws std::runtime_error       On error, e.g. if the current user doesn't have the necessary permissions.
     */
    bool remove(std::string_view path);
    bool remove(const FileSystemPath &path);

 protected:
    template<class T>
    using FileSystemTrieNode = detail::FileSystemTrieNode<T>;
    template<class T>
    using FileSystemTrie = detail::FileSystemTrie<T>;

    friend class ProxyFileSystem; // It's OK for the default proxy implementation to call into the private methods.

 protected:
    [[nodiscard]] virtual bool _exists(const FileSystemPath &path) const = 0;
    [[nodiscard]] virtual FileStat _stat(const FileSystemPath &path) const = 0;
    [[nodiscard]] virtual std::vector<DirectoryEntry> _ls(const FileSystemPath &path) const = 0;
    [[nodiscard]] virtual Blob _read(const FileSystemPath &path) const = 0;
    virtual void _write(const FileSystemPath &path, const Blob &data) = 0;
    [[nodiscard]] virtual std::unique_ptr<InputStream> _openForReading(const FileSystemPath &path) const = 0;
    [[nodiscard]] virtual std::unique_ptr<OutputStream> _openForWriting(const FileSystemPath &path) = 0;
    virtual void _rename(const FileSystemPath &srcPath, const FileSystemPath &dstPath);
    virtual bool _remove(const FileSystemPath &path) = 0;
};


