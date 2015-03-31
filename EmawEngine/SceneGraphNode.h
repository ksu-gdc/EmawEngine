#pragma once

#include "stdafx.h"
#include "Transform.h"
#include <string>

class SceneGraphNode {

private:

	std::vector<SceneGraphNode*> children;
	Transform* transform;
	GraphicsDeviceInterface* gdi;

public:

	virtual void update(D3DXMATRIX*) = 0;
	virtual void render() = 0;
	virtual void setGraphicsDeviceInterface(GraphicsDeviceInterface*) = 0;

};