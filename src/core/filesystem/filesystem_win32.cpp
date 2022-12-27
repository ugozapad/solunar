#include "core/filesystem/filesystem_win32.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace solunar
{

static int s_stdioSeekDir[] = { SEEK_SET, SEEK_CUR, SEEK_END };

StdFile::StdFile(const char* filename, bool read)
{
	m_file = fopen(filename, (read == true) ? "rb" : "wb");
	//m_file.open(filename, (read == true) ? std::ios_base::in : std::ios_base::out);
}

StdFile::~StdFile()
{
	if (m_file)
	{
		fclose(m_file);
		m_file = nullptr;
	}
}

size_t StdFile::read(void* buffer, size_t size)
{
	return fread(buffer, 1, size, m_file);
}

size_t StdFile::write(void* buffer, size_t size)
{
	return fwrite(buffer, 1, size, m_file);
}

size_t StdFile::tell()
{
	return ftell(m_file);
}

void StdFile::seek(size_t offset, FileSeek fileseek)
{
	fseek(m_file, (long)offset, s_stdioSeekDir[(int)fileseek]);
}

void StdFile::flush()
{
	fflush(m_file);
}

FileSystemWin32::FileSystemWin32(const std::string& path) :
	m_path(path)
{
}

FileSystemWin32::~FileSystemWin32()
{
}

bool FileSystemWin32::fileExist(const char* path)
{
	std::string filepath = computePath(path);

	DWORD dwAttrib = GetFileAttributesA(filepath.c_str());
	return (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

bool FileSystemWin32::createDirectory(const char* path)
{
	if (::CreateDirectoryA(path, NULL))
		return true;

	return false;
}

IFile* FileSystemWin32::openFile(const char* path, bool read)
{
	std::string filepath = computePath(path);

	if (read && !fileExist(path))
		return nullptr;

	return new StdFile(filepath.c_str(), read);
}

std::string FileSystemWin32::computePath(const char* path)
{
	std::string filename = path;

	// if filepath doesn't have path symbol at beggin
	if (filename[0] != '/')
		filename.insert(0, 1, '/');

	for (int i = 0; i < filename.size(); i++)
	{
		// Convert unix path to windows
		if (filename[i] == '/')
			filename[i] = '\\';
	}

	// add current directory path
	std::string finalFilepath = m_path;
	finalFilepath += filename;

	return finalFilepath;
}

}