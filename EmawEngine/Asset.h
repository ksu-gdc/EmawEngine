#pragma once

#include "resource.h"


class Asset{
private:
public:
	Asset();
	~Asset();
	virtual void* load(char*) = 0;
	virtual void* getData() = 0;
	virtual bool unload() = 0;
};