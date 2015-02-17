#pragma once
#include "Asset.h"
#include "graphics_device_interface.h"
#include "EmawEngine.h"


class ShaderAsset : public Asset
{
public:
	ShaderStruct Shaders;
	ShaderAsset(GraphicsDeviceInterface* gdi);
	~ShaderAsset();
	void* load(char*);
	void* getData();
	bool unload();

private:
	GraphicsDeviceInterface* gInterface;
};

