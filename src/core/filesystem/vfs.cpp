#include <cstring>

#include "core/filesystem/vfs.h"
#include "core/filesystem/ifilesystem.h"

namespace solunar
{

VirtualFileSystem* VirtualFileSystem::getInstance()
{
	static VirtualFileSystem instance;
	return &instance;
}

void VirtualFileSystem::mount(const MountPointDesc& mountDesc)
{
	m_mountingPoints.push_back(mountDesc);
}

void VirtualFileSystem::mount(const char* path, IFileSystem* filesystem)
{
	MountPointDesc mountingDesc;
	memset(&mountingDesc, 0, sizeof(mountingDesc));
	mountingDesc.m_path = path;
	mountingDesc.m_filesystem = filesystem;
	mount(mountingDesc);
}

bool VirtualFileSystem::fileExist(const std::string& filename)
{
	if (MountPointDesc* mountPoint = getMountingPoint(filename))
	{
		return mountPoint->m_filesystem->fileExist(filename.c_str());
	}

	return false;
}

IFile* VirtualFileSystem::openFile(const std::string& filename)
{
	if (MountPointDesc* mountPoint = getMountingPoint(filename))
	{
		return mountPoint->m_filesystem->openFile(filename.c_str());
	}

	return nullptr;
}

MountPointDesc* VirtualFileSystem::getMountingPoint(const std::string& filename)
{
	// Try to find mouting point name.
	size_t beginPathLocation = filename.find_first_of('/');
	if (beginPathLocation == std::string::npos)
		return nullptr;

	// substract path name and try to find mouting point
	std::string pathname = filename.substr(0, beginPathLocation + 1);
	for (MountPointDesc& mountPoint : m_mountingPoints)
	{
		// #TODO: This is not case sensitive, make our own strcmpi 
		if (strcmp(mountPoint.m_path, pathname.c_str()) == 0)
		{
			return &mountPoint;
		}
	}

	return nullptr;
}

}