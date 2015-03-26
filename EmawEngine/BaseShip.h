#pragma once

#include "stdafx.h"
#include "Transform.h"
#include "GameObjectNode.h"
#include <string>

class BaseShip : public GameObjectNode {

private:

	std::vector<GameObjectNode*> children;
	Transform* transform;
	vector<VERTEX> vertexBuffer;
	Model model;

public:
	BaseShip();
	BaseShip(std::vector<VERTEX>*);
	~BaseShip();

	void input();
	std::vector<VERTEX>* update(Transform*);
	void render();
	void addChild(GameObjectNode*);

};