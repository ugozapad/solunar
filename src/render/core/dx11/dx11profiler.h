#ifndef RENDER_CORE_DX11_DX11PROFILER_H
#define RENDER_CORE_DX11_DX11PROFILER_H


namespace solunar
{

void dx11ProfilerInit();
void dx11ProfilerShutdown();

void dx11BeginMarker(uint32_t color, wchar_t* message);
void dx11EndMarker();

}

#endif // !RENDER_CORE_DX11_DX11PROFILER_H
