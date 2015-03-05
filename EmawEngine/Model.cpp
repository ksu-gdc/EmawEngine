#include "stdafx.h"
#include "Model.h"


Model::Model()
{
}


Model::~Model()
{
	this->unload();
}

void* Model::load(char* filename) {
	if (strlen(filename) <= 4) {
		OutputDebugString(L"file is of incorrect length\n");
		return NULL;
	}
	// todo: fix for upper case input
	if (strncmp(".fbx", filename + (strlen(filename) - 4), 4) != 0) {
		OutputDebugString(L"file extension is incorrect\n");
		return NULL;
	}

	// initialize fbx loader thing
	// the following block should be moved to the asset manager
	FbxManager* manager = NULL;
	manager = FbxManager::Create();
	FbxIOSettings* IOsettings = FbxIOSettings::Create(manager, IOSROOT);
	manager->SetIOSettings(IOsettings);
	FbxImporter* importer = FbxImporter::Create(manager, "");
	FbxScene* scene = FbxScene::Create(manager, "");

	bool success = importer->Initialize(filename, -1,
		manager->GetIOSettings());
	if (!success) {
		OutputDebugString(L"failed to load model\n");
		return NULL;
	}
	success = importer->Import(scene);
	if (!success) {
		OutputDebugString(L"some kinda failure\n");
		return NULL;
	}

	importer->Destroy();

	FbxNode* node = scene->GetRootNode();
	if (node) {
		for (int i = 0; i < node->GetChildCount(); i++) {
			FbxNode* childNode = node->GetChild(i);
			if (childNode->GetNodeAttribute() == NULL) {
				continue;
			}
			FbxNodeAttribute::EType attributeType = childNode->GetNodeAttribute()->GetAttributeType();
			if (attributeType != FbxNodeAttribute::eMesh) {
				continue;
			}
			FbxMesh* mesh = (FbxMesh*)childNode->GetNodeAttribute();
			FbxVector4* verticies = mesh->GetControlPoints();
			for (int j = 0; j < mesh->GetPolygonCount(); j++) {
				int numVerticies = mesh->GetPolygonSize(j);
				if (numVerticies != 3) {
					// yeah, I know that this is awful, but strings were being real difficult.
					OutputDebugString(L"3 verticies expected; ");
					switch (numVerticies) {
					case 4:
						OutputDebugString(L"4");
						break;
					default:
						OutputDebugString(L"unknown");
						break;
					}
					OutputDebugString(L" given; make sure your model only has triangles.\n");
					return NULL;
				}
				for (int k = 0; k < numVerticies; k++) {
					int controlPointIndex = mesh->GetPolygonVertex(j, k);
					Vertex vertex;
					vertex.x = (float)verticies[controlPointIndex].mData[0];
					vertex.y = (float)verticies[controlPointIndex].mData[1];
					vertex.z = (float)verticies[controlPointIndex].mData[2];

					vertexBuffer.push_back(vertex);
				}
			}
		}
	}

	return NULL;
}

void* Model::getData() {
	return NULL;
}

bool Model::unload() {
	vertexBuffer.clear();
	return true;
}

std::vector<Vertex> Model::getVertexBuffer() {
	return vertexBuffer;
}