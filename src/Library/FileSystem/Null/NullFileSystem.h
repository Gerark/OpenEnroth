#pragma once

#include <memory>
#include <vector>

#include "Library/FileSystem/Interface/ReadOnlyFileSystem.h"

/**
 * Empty read-only filesystem.
 */
class NullFileSystem : public ReadOnlyFileSystem {
 private:
    virtual bool _exists(const FileSystemPath &path) const override;
    virtual FileStat _stat(const FileSystemPath &path) const override;
    virtual std::vector<DirectoryEntry> _ls(const FileSystemPath &path) const override;
    virtual Blob _read(const FileSystemPath &path) const override;
    virtual std::unique_ptr<InputStream> _openForReading(const FileSystemPath &path) const override;

    [[noreturn]] void reportReadError(const FileSystemPath &path) const;
};
