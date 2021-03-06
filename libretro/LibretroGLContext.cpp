
#include "Common/Log.h"
#include "Core/Config.h"
#include "Core/ConfigValues.h"
#include "Core/System.h"
#include "gfx_es2/gpu_features.h"
#include <glsym/rglgen.h>
#include "libretro/LibretroGLContext.h"

bool LibretroGLContext::Init() {
	if (!LibretroHWRenderContext::Init(true))
		return false;

	g_Config.iGPUBackend = (int)GPUBackend::OPENGL;
	return true;
}

extern const struct rglgen_sym_map rglgen_symbol_map_ppsspp;
void LibretroGLContext::CreateDrawContext() {
	if (!glewInitDone) {
		rglgen_resolve_symbols_custom(&eglGetProcAddress, &rglgen_symbol_map_ppsspp);
		CheckGLExtensions();
        glewInitDone = true;
	}
	draw_ = Draw::T3DCreateGLContext();
	renderManager_ = (GLRenderManager *)draw_->GetNativeObject(Draw::NativeObject::RENDER_MANAGER);
}

void LibretroGLContext::DestroyDrawContext() {
	LibretroHWRenderContext::DestroyDrawContext();
	renderManager_ = nullptr;
}
