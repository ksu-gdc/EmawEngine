#include "stdafx.h"
#include "Model.h"

// Sometimes models will read in extremely small values.
// We might as well set these values to 0. So this const
// is just used as a minimum value.
const float MINIMUM_TRANSFORMATION_VALUE = 0.00005;

Model::Model()
{
	m_Texture = 0;
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