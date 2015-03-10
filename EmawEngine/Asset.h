#pragma once

#include "resource.h"


class Asset{
private:
public:
	Asset();
	~Asset();
	virtual void* load(std::string) = 0;
	virtual bool unload() = 0;
};