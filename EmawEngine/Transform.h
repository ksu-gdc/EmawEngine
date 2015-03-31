#pragma once

#include "stdafx.h"
#include <list>
#include <string>
#include <D3DX10.h>

class Transform {

private:

	D3DXMATRIX* rotateMatrixX;
	D3DXMATRIX* rotateMatrixY;
	D3DXMATRIX* rotateMatrixZ;
	D3DXMATRIX* translateMatrix;
	D3DXMATRIX* scaleMatrix;
	D3DXMATRIX* transformMatrix;


public:
	Transform();
	~Transform();

	void applyTransformation(D3DXMATRIX*);
	D3DXMATRIX* getTransformMatrix();
	void createTransform();
	static D3DXMATRIX* createIdentity();
	void rotateX(float);
	void rotateY(float);
	void rotateZ(float);
	void scale(float, float, float);
	void translate(float, float, float);
	void resetTransformMatrix();
};