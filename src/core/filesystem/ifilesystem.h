#ifndef CORE_FILESYSTEM_IFILESYSTEM_H
#define CORE_FILESYSTEM_IFILESYSTEM_H

#ifdef _MSC_VER
#	pragma once
#endif // _MSC_VER

namespace solunar
{

class IFile;

class IFileSystem
{
public:
	//! Is file exist.
	virtual bool fileExist(const char* path) = 0;

	//! Create directory.
	virtual bool createDirectory(const char* path) = 0;

	//! Open file.
	virtual IFile* openFile(const char* path, bool read = true) = 0;
};

extern IFileSystem* g_fileSystem;

}

#endif