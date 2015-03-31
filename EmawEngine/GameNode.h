#pragma once

#include "stdafx.h"
#include "Transform.h"
#include "SceneGraphNode.h"
#include <string>

class GameNode : public SceneGraphNode {

private:

	std::vector<SceneGraphNode*> children;
	Transform* transform;
	GraphicsDeviceInterface* gdi;

public:

	GameNode();
	~GameNode();

	void update(D3DXMATRIX*);
	void render();
	void addChild(SceneGraphNode*);
	void setGraphicsDeviceInterface(GraphicsDeviceInterface*);

};