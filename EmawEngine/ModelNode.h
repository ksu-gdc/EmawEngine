#pragma once

#include "stdafx.h"
#include "Transform.h"
#include "SceneGraphNode.h"
#include <string>

class ModelNode : public SceneGraphNode {

private:

	std::vector<SceneGraphNode*> children;
	Transform* transform;
	Model* model;
	GraphicsDeviceInterface* gdi;

public:
	ModelNode();
	ModelNode(Model*);
	~ModelNode();

	void update(D3DXMATRIX*);
	void render();
	void addChild(SceneGraphNode*);
	void setGraphicsDeviceInterface(GraphicsDeviceInterface*);
	void rotateX(float);
	void rotateY(float);
	void rotateZ(float);
	void scale(float, float, float);
	void translate(float, float, float);
	void resetTransformMatrix();

};