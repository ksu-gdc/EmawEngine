#pragma once

#include "stdafx.h"
#include "Transform.h"
#include <string>

class GameObjectNode {

private:

	std::vector<GameObjectNode*> children;
	Transform* transform;

public:

	virtual void input() = 0;
	virtual std::vector<VERTEX>* update(Transform*) = 0;
	virtual void render() = 0;

};