#ifndef CORE_FILESYSTEM_VFS_H
#define CORE_FILESYSTEM_VFS_H

#include <vector>
#include <string>

namespace solunar
{

// Forward declaration
class IFileSystem;
class IFile;

//! Describe mounting point
struct MountPointDesc
{
	IFileSystem* m_filesystem;
	const char* m_path;
};

class VirtualFileSystem
{
public:
	static VirtualFileSystem* getInstance();

public:
	void mount(const MountPointDesc& mountDesc);
	void mount(const char* path, IFileSystem* filesystem);

	bool fileExist(const std::string& filename);
	IFile* openFile(const std::string& filename);
	
private:
	MountPointDesc* getMountingPoint(const std::string& filename);

private:
	std::vector<MountPointDesc> m_mountingPoints;
};

}

#endif // !CORE_VFS_H
