#pragma once

#include "stdafx.h"
#include "Transform.h"
#include "GameObjectNode.h"
#include <string>

class GameNode : public GameObjectNode {

private:

	std::vector<GameObjectNode*> children;
	Transform* transform;

public:

	GameNode();
	~GameNode();

	void input();
	std::vector<VERTEX>* update(Transform*);
	void render();
	void addChild(GameObjectNode*);

};