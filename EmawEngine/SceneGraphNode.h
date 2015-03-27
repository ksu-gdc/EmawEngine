#pragma once

#include "stdafx.h"
#include "Transform.h"
#include <string>

class SceneGraphNode {

private:

	std::vector<SceneGraphNode*> children;
	Transform* transform;

public:

	virtual void input() = 0;
	virtual void update(D3DXMATRIX*) = 0;
	virtual void render(std::vector<VERTEX>*) = 0;

};