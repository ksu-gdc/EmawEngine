#include "stdafx.h"
#include "Transform.h"
#include <D3DX10.h>

Transform::Transform(){

	rotateMatrixX = Transform::createIdentity();
	rotateMatrixY = Transform::createIdentity();
	rotateMatrixZ = Transform::createIdentity();
	translateMatrix = Transform::createIdentity();
	scaleMatrix = Transform::createIdentity();
	transformMatrix = Transform::createIdentity();

}

Transform::~Transform(){
	delete rotateMatrixX;
	delete rotateMatrixY;
	delete rotateMatrixZ;
	delete translateMatrix;
	delete scaleMatrix;
	delete transformMatrix;
}

void Transform::createTransform(){
	resetTransformMatrix();
	D3DXMatrixMultiply(transformMatrix, transformMatrix, rotateMatrixX);
	D3DXMatrixMultiply(transformMatrix, transformMatrix, rotateMatrixY);
	D3DXMatrixMultiply(transformMatrix, transformMatrix, rotateMatrixZ);
	D3DXMatrixMultiply(transformMatrix, transformMatrix, scaleMatrix);
	D3DXMatrixMultiply(transformMatrix, transformMatrix, translateMatrix);
}

void Transform::applyTransformation(D3DXMATRIX* otherTransform){
	
	D3DXMatrixMultiply(transformMatrix, transformMatrix, otherTransform);
}

D3DXMATRIX* Transform::getTransformMatrix(){
	return transformMatrix;
}

void Transform::rotateX(float angle){
	D3DXMatrixRotationX(rotateMatrixX, angle);
}

void Transform::rotateY(float angle){
	D3DXMatrixRotationY(rotateMatrixY, angle);
}

void Transform::rotateZ(float angle){
	D3DXMatrixRotationZ(rotateMatrixZ, angle);
}

void Transform::scale(float x, float y, float z){
	D3DXMatrixScaling(scaleMatrix, x, y, z);
}

void Transform::translate(float x, float y, float z){
	D3DXMatrixTranslation(translateMatrix, x, y, z);
}

void Transform::resetTransformMatrix(){
	transformMatrix = Transform::createIdentity();
}

void Transform::resetTranslateMatrix(){
	resetTransformMatrix();
	translateMatrix = Transform::createIdentity();
}

void Transform::resetRotationMatrix(){
	resetTransformMatrix();
	rotateMatrixX = Transform::createIdentity();
	rotateMatrixY = Transform::createIdentity();
	rotateMatrixZ = Transform::createIdentity();
}

void Transform::resetScaleMatrix(){
	resetTransformMatrix();
	scaleMatrix = Transform::createIdentity();
}

D3DXMATRIX* Transform::createIdentity(){

	D3DXMATRIX* i = new D3DXMATRIX();

	i->_11 = 1.0;
	i->_12 = 0.0;
	i->_13 = 0.0;
	i->_14 = 0.0;
	i->_21 = 0.0;
	i->_22 = 1.0;
	i->_23 = 0.0;
	i->_24 = 0.0;
	i->_31 = 0.0;
	i->_32 = 0.0;
	i->_33 = 1.0;
	i->_34 = 0.0;
	i->_41 = 0.0;
	i->_42 = 0.0;
	i->_43 = 0.0;
	i->_44 = 1.0;

	return i;

}
