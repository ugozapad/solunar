#ifdef __unix__

#include "core/filesystem/filesystem_unix.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

namespace solunar
{

static int s_stdioSeekDir[] = { SEEK_SET, SEEK_CUR, SEEK_END };

FileUnix::FileUnix(const char* filename, bool read)
{
	m_file = fopen(filename, (read == true) ? "rb" : "wb");
	//m_file.open(filename, (read == true) ? std::ios_base::in : std::ios_base::out);
}

FileUnix::~FileUnix()
{
	if (m_file)
	{
		fclose(m_file);
		m_file = nullptr;
	}
}

size_t FileUnix::read(void* buffer, size_t size)
{
	return fread(buffer, 1, size, m_file);
}

size_t FileUnix::write(void* buffer, size_t size)
{
	return fwrite(buffer, 1, size, m_file);
}

size_t FileUnix::tell()
{
	return ftell(m_file);
}

void FileUnix::seek(size_t offset, FileSeek fileseek)
{
	fseek(m_file, (long)offset, s_stdioSeekDir[(int)fileseek]);
}

void FileUnix::flush()
{
	fflush(m_file);
}

FileSystemUnix::FileSystemUnix(const std::string& path) :
	m_path(path)
{
}

FileSystemUnix::~FileSystemUnix()
{
}

bool FileSystemUnix::fileExist(const char* path)
{
	std::string filepath = computePath(path);
	return (access(filepath.c_str(), F_OK) != -1);
}

bool FileSystemUnix::createDirectory(const char* path)
{
	std::string filepath = computePath(path);

	const int dir_err = mkdir(filepath.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	if (dir_err == -1)
		return false;

	return true;
}

IFile* FileSystemUnix::openFile(const char* path, bool read /*= true*/)
{
	std::string filepath = computePath(path);

	if (read && !fileExist(path))
		return nullptr;

	return new FileUnix(filepath.c_str(), read);
}

std::string FileSystemUnix::computePath(const char* path)
{
	std::string filename = path;

	// if filepath doesn't have path symbol at begin
	if (filename[0] != '/')
		filename.insert(0, 1, '/');

	for (int i = 0; i < filename.size(); i++)
	{
		// If path contains Windows-like path we need to convert it to unix-like
		if (filename[i] == '\\')
			filename[i] = '/';
	}

	// add current directory path
	std::string finalFilepath = m_path;
	finalFilepath += filename;

	return finalFilepath;
}

}

#endif // __unix__
