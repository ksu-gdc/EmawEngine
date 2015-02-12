#pragma once

#include "resource.h"
#include "graphics_device_interface.h"


class Asset{
private:
public:
	Asset();
	~Asset();
	virtual void* load(char*)  =0;

};