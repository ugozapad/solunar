#include <cstdint>

#include "render/core/dx11/dx11profiler.h"
#include "render/core/dx11/dx11renderer.h"

#include <d3d9.h>
#include <d3d11_1.h>

namespace solunar
{

ID3DUserDefinedAnnotation* g_d3dUserDefinedAnnotation = nullptr;
bool g_forceD3DPERF = true;

void dx11ProfilerInit()
{
	// Try to get ID3DUserDefinedAnnotation
	g_dx11Renderer->getDeviceContext()->QueryInterface(__uuidof(ID3DUserDefinedAnnotation), (void **)&g_d3dUserDefinedAnnotation);
}

void dx11ProfilerShutdown()
{
	if (g_d3dUserDefinedAnnotation)
	{
		g_d3dUserDefinedAnnotation->Release();
		g_d3dUserDefinedAnnotation = nullptr;
	}
}

void dx11BeginMarker(uint32_t color, wchar_t* message)
{
	if (g_d3dUserDefinedAnnotation && !g_forceD3DPERF)
		g_d3dUserDefinedAnnotation->BeginEvent(message);
	else
		D3DPERF_BeginEvent(color, message);
}

void dx11EndMarker()
{
	if (g_d3dUserDefinedAnnotation && !g_forceD3DPERF)
		g_d3dUserDefinedAnnotation->EndEvent();
	else
		D3DPERF_EndEvent();
}

}
