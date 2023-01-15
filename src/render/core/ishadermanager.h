#ifndef RENDER_ISHADERMANAGER_H
#define RENDER_ISHADERMANAGER_H

namespace solunar
{

class IShaderManager 
{
public:
	virtual ~IShaderManager() {}

	virtual void init() = 0;
	virtual void shutdown() = 0;
};

extern IShaderManager* g_shaderManager;

}

#endif // !RENDER_ISHADERMANAGER_H
