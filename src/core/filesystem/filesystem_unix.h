#ifndef CORE_FILESYSTEM_UNIX_H
#define CORE_FILESYSTEM_UNIX_H

#include "core/filesystem/file.h"
#include "core/filesystem/ifilesystem.h"

#include <stdlib.h>
#include <string>

namespace solunar
{

class FileUnix : public IFile
{
public:
	FileUnix(const char* filename, bool read);
	~FileUnix();

	size_t read(void* buffer, size_t size) override;
	size_t write(void* buffer, size_t size) override;

	size_t tell() override;

	void seek(size_t offset, FileSeek fileseek) override;

	void flush() override;

private:
	FILE* m_file;

};

class FileSystemUnix : public IFileSystem
{
public:
	FileSystemUnix(const std::string& path);
	~FileSystemUnix();

	bool fileExist(const char* path) override;

	bool createDirectory(const char* path) override;

	IFile* openFile(const char* path, bool read = true) override;

private:
	std::string computePath(const char* path);

private:
	std::string m_path;
};

}

#endif // !CORE_FILESYSTEM_UNIX_H
