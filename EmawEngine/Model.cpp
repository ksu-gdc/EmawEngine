#include "stdafx.h"
#include "Model.h"

// Sometimes models will read in extremely small values.
// We might as well set these values to 0. So this const
// is just used as a minimum value.
const float MINIMUM_TRANSFORMATION_VALUE = 0.00005;

Model::Model()
{
	m_Texture = 0;

	m_InitPos = new Vector3();
	m_InitScale = new Vector3();
	m_InitRot = new Vector3();
	m_InitPos->x = new float();
	m_InitPos->y = new float();
	m_InitPos->z = new float();
	m_InitScale->x = new float();
	m_InitScale->y = new float();
	m_InitScale->z = new float();
	m_InitRot->x = new float();
	m_InitRot->y = new float();
	m_InitRot->z = new float();
}

Model::Model(std::vector<VERTEX> vBuffer){
	this->vertexBuffer = vBuffer;
}

Model::~Model()
{
}

void* Model::load(std::string str) {
	// obj model loading
	ifstream fin;
	fin.open(str);
	if (!fin.good()) {
		OutputDebugString(L"model file not found\n");
		return NULL;
	}

	// create buffer to hold all vertices
	const int MAX_VERTICES = 1000;
	VERTEX vertices[MAX_VERTICES];
	int num_vertices = 0;

	// create buffer to hold uv coordinates
	const int MAX_UV = 1000;
	float us[MAX_UV];
	float vs[MAX_UV];
	int num_uv = 0;

	const int MAX_CHARS = 500;
	while (!fin.eof()) {
		char buf[MAX_CHARS];
		fin.getline(buf, MAX_CHARS);
		if (strlen(buf) == 0) {
			break;
		}
		string prefix = strtok(buf, " ");

		// vertex
		if (prefix.compare("v") == 0) {
			
			vertices[num_vertices].X = stof(strtok(0, " "));
			vertices[num_vertices].Y = stof(strtok(0, " "));
			vertices[num_vertices].Z = stof(strtok(0, " "));
			vertices[num_vertices].W = 1.0f;

			// generate random color
			float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			vertices[num_vertices].Color = DirectX::XMFLOAT4(r, g, b, 1.0f);

			num_vertices++;
		}
		else if (prefix.compare("vt") == 0) {
			us[num_uv] = stof(strtok(0, " "));
			vs[num_uv] = stof(strtok(0, " "));
			num_uv++;
		}
		else if (prefix.compare("f") == 0) {
			for (int i = 0; i < 3; i++) {
				string entry = strtok(0, " ");
				// stoi will properly ignore the '/'
				int index = stoi(entry) - 1;
				// add uv data to vertex
				int uv_index = stoi(entry.substr(entry.find('/')+1));
				vertices[index].U = us[uv_index];
				vertices[index].V = vs[uv_index];
				vertexBuffer.push_back(vertices[index]);
				
			}
		}
		
		else {
			int x = 3;
		}


	}
	return NULL;
}

void Model::LoadTexture(ID3D11Device* device, string filename){

	m_Texture = new Texture(device);
	m_Texture->load(filename);

}

ID3D11ShaderResourceView* Model::GetTexture(){
	return m_Texture->getTexture();
}

void Model::setInitialTransforms(FbxMesh* mesh){

	// Models can come with scale, translation, and rotation. This
	// code will extract those values and store them in the model so that
	// the models will render correctly.
	FbxDouble3 initialTranslate = mesh->GetNode()->LclTranslation.Get();
	FbxDouble3 initialScale = mesh->GetNode()->LclScaling.Get();
	FbxDouble3 initialRotate = mesh->GetNode()->LclRotation.Get();

	if (abs(initialTranslate.mData[0]) > MINIMUM_TRANSFORMATION_VALUE){
		*m_InitPos->x = initialTranslate.mData[0];
	}
	if (abs(initialTranslate.mData[1]) > MINIMUM_TRANSFORMATION_VALUE){
		*m_InitPos->y = initialTranslate.mData[1];
	}
	if (abs(initialTranslate.mData[2]) > MINIMUM_TRANSFORMATION_VALUE){
		*m_InitPos->z = initialTranslate.mData[2];
	}

	if (abs(initialScale.mData[0]) > MINIMUM_TRANSFORMATION_VALUE){
		*m_InitScale->x = initialScale.mData[0];
	}
	if (abs(initialScale.mData[1]) > MINIMUM_TRANSFORMATION_VALUE){
		*m_InitScale->y = initialScale.mData[1];
	}
	if (abs(initialScale.mData[2]) > MINIMUM_TRANSFORMATION_VALUE){
		*m_InitScale->z = initialScale.mData[2];
	}

	if (abs(initialRotate.mData[0]) > MINIMUM_TRANSFORMATION_VALUE){
		*m_InitRot->x = initialRotate.mData[0];
	}
	if (abs(initialRotate.mData[1]) > MINIMUM_TRANSFORMATION_VALUE){
		*m_InitRot->y = initialRotate.mData[1];
	}
	if (abs(initialRotate.mData[2]) > MINIMUM_TRANSFORMATION_VALUE){
		*m_InitRot->z = initialRotate.mData[2];
	}

}

void Model::applyInitialTransformations(){

	D3DXMATRIX* rotateMatrixX = new D3DXMATRIX();
	D3DXMATRIX* rotateMatrixY = new D3DXMATRIX();
	D3DXMATRIX* rotateMatrixZ = new D3DXMATRIX();
	D3DXMATRIX* translateMatrix = new D3DXMATRIX();
	D3DXMATRIX* scaleMatrix = new D3DXMATRIX();
	D3DXMATRIX* transformMatrix = new D3DXMATRIX();

	D3DXMatrixIdentity(rotateMatrixX);
	D3DXMatrixIdentity(rotateMatrixY);
	D3DXMatrixIdentity(rotateMatrixZ);
	D3DXMatrixIdentity(translateMatrix);
	D3DXMatrixIdentity(scaleMatrix);
	D3DXMatrixIdentity(transformMatrix);

	D3DXMatrixTranslation(translateMatrix, *m_InitPos->x, *m_InitPos->y, *m_InitPos->z);
	D3DXMatrixScaling(scaleMatrix, *m_InitScale->x, *m_InitScale->z, *m_InitScale->y);
	D3DXMatrixRotationZ(rotateMatrixZ, *m_InitRot->z * 0.0174532925);
	D3DXMatrixRotationY(rotateMatrixY, *m_InitRot->y * 0.0174532925);
	D3DXMatrixRotationX(rotateMatrixX, *m_InitRot->x * 0.0174532925);

	D3DXMatrixMultiply(transformMatrix, transformMatrix, rotateMatrixX);
	D3DXMatrixMultiply(transformMatrix, transformMatrix, rotateMatrixY);
	D3DXMatrixMultiply(transformMatrix, transformMatrix, rotateMatrixZ);
	D3DXMatrixMultiply(transformMatrix, transformMatrix, scaleMatrix);
	D3DXMatrixMultiply(transformMatrix, transformMatrix, translateMatrix);

	for (int i = 0; i < vertexBuffer.size(); i++){

		D3DXVECTOR4* transformedVertex = new D3DXVECTOR4();
		D3DXVECTOR3* vertex = new D3DXVECTOR3();

		vertex->x = vertexBuffer.at(i).X;
		vertex->y = vertexBuffer.at(i).Y;
		vertex->z = vertexBuffer.at(i).Z;

		D3DXVec3Transform(transformedVertex, vertex, transformMatrix);

		vertexBuffer.at(i).X = transformedVertex->x;
		vertexBuffer.at(i).Y = transformedVertex->y;
		vertexBuffer.at(i).Z = transformedVertex->z;

	}

}

void* Model::getData() {
	return NULL;
}

bool Model::unload() {
	vertexBuffer.clear();
	return true;
}

std::vector<VERTEX> Model::getVertexBuffer() {
	return vertexBuffer;
}