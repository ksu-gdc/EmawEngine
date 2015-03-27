#pragma once

#include "stdafx.h"
#include "Transform.h"
#include "SceneGraphNode.h"
#include <string>

class GameNode : public SceneGraphNode {

private:

	std::vector<SceneGraphNode*> children;
	Transform* transform;

public:

	GameNode();
	~GameNode();

	void input();
	void update(D3DXMATRIX*);
	void render(std::vector<VERTEX>*);
	void addChild(SceneGraphNode*);

};