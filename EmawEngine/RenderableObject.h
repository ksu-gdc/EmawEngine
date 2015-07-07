#pragma once
#include "GameObject.h"
class RenderableObject :
	public GameObject
{
public:
	RenderableObject();
	~RenderableObject();

	virtual void render() = 0;
};