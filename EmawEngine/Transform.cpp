#include "stdafx.h"
#include "Transform.h"

Transform::Transform(){
	matrix = new float[9];
	matrix[0] = 1;
	matrix[4] = 1;
	matrix[7] = 1;
}

Transform::Transform(float* otherMatrix){
	
	matrix = new float[9];

	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			matrix[3 * i + j] = otherMatrix[3 * i + j];
		}
	}
}

Transform::~Transform(){

}

Transform* Transform::multiply(Transform* multiplier){

	float* product = new float[9];

	// Iterate through the rows of multiplicand matrix.
	for (int row = 0; row < 3; row++){

		// Iterate through the columns of the multiplier matrix;
		for (int col = 0; col < 3; col++){

			// Index to multiply.
			for (int i = 0; i < 3; i++){

				product[3 * row + col] += matrix[3 * row + i] * multiplier->getMatrix()[3 * i + col];

			}
		}
	}

	return new Transform(product);
}

VERTEX Transform::transformVertex(VERTEX vertex){

	VERTEX transformedVertex;

	transformedVertex.Color = vertex.Color;
	transformedVertex.W = vertex.W;
	transformedVertex.X = (matrix[0] * vertex.X) + (matrix[1] * vertex.Y) + (matrix[2] * vertex.Z);
	transformedVertex.Y = (matrix[3] * vertex.X) + (matrix[4] * vertex.Y) + (matrix[5] * vertex.Z);
	transformedVertex.Z = (matrix[6] * vertex.X) + (matrix[7] * vertex.Y) + (matrix[8] * vertex.Z);

	return transformedVertex;
}

float* Transform::getMatrix(){
	return matrix;
}