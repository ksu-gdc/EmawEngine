#pragma once

#include "stdafx.h"
#include <list>
#include <string>

class Transform {

private:

	float* matrix;

public:
	Transform();
	Transform(float*);
	~Transform();

	Transform* multiply(Transform*);
	VERTEX transformVertex(VERTEX);
	float* getMatrix();
};