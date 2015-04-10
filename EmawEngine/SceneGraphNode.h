#pragma once

#include "stdafx.h"
#include "Transform.h"
#include <string>

class SceneGraphNode {

public:

	virtual void update(D3DXMATRIX*) = 0;
	virtual void render() = 0;
	virtual void setGraphicsDeviceInterface(GraphicsDeviceInterface*) = 0;

protected:

	std::vector<SceneGraphNode*> children;
	Transform* transform;
	GraphicsDeviceInterface* gdi;

};