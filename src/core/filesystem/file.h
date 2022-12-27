#ifndef CORE_FILESYSTEM_FILE_H
#define CORE_FILESYSTEM_FILE_H

namespace solunar
{

enum FileSeek
{
	FileSeek_Begin,
	FileSeek_Current,
	FileSeek_End
};

//! Interface to native IO file
class IFile
{
public:
	virtual ~IFile() {}

	virtual size_t read(void* buffer, size_t size) = 0;
	virtual size_t write(void* buffer, size_t size) = 0;

	virtual size_t tell() = 0;

	virtual void seek(size_t offset, FileSeek fileseek) = 0;

	virtual void flush() = 0;
};

}

#endif // !CORE_FILE_H
