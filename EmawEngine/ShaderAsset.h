#pragma once
#include "Asset.h"
#include "graphics_device_interface.h"
#include "EmawEngine.h"
class ShaderAsset : public Asset
{
private:

public:
	ShaderStruct Shaders;
	ShaderAsset(GraphicsDeviceInterface*);
	~ShaderAsset();
	void* load(char*);
	void* getData();
	bool unload();

};

