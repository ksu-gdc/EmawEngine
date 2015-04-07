#include "stdafx.h"
#include "Model.h"

// Sometimes models will read in extremely small values.
// We might as well set these values to 0. So this const
// is just used as a minimum value.
const float MINIMUM_TRANSFORMATION_VALUE = 0.00005;

Model::Model()
{
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
	char *filename = &str[0u];

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
		manager->Destroy();
		return NULL;
	}
	success = importer->Import(scene);
	if (!success) {
		OutputDebugString(L"some kinda failure\n");
		manager->Destroy();
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

			// Pull initial transformation values out of the mesh.
			setInitialTransforms(mesh);

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
					node->Destroy();
					mesh->Destroy();
					manager->Destroy();
					return NULL;
				}
				for (int k = 0; k < numVerticies; k++) {
					int controlPointIndex = mesh->GetPolygonVertex(j, k);
					VERTEX vertex;
					vertex.X = (float)verticies[controlPointIndex].mData[0];
					vertex.Y = (float)verticies[controlPointIndex].mData[1];
					vertex.Z = (float)verticies[controlPointIndex].mData[2];
					vertex.W = 1.0f;
					//vertex.Color = DirectX::XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f); // grey
					// generate random color
					float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
					float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
					float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
					vertex.Color = DirectX::XMFLOAT4(r,g, b, 1.0f);

					vertexBuffer.push_back(vertex);
				}
			}
			mesh->Destroy();
		}
	}

	node->Destroy();
	manager->Destroy();
	
	return NULL;
}

void Model::setInitialTransforms(FbxMesh* mesh){

	// Models can come with scale, translation, and rotation. This
	// code will extract those values and store them in the model so that
	// the models will render correctly.
	FbxDouble3 initialTranslate = mesh->GetNode()->LclTranslation.Get();
	FbxDouble3 initialScale = mesh->GetNode()->LclScaling.Get();
	FbxDouble3 initialRotate = mesh->GetNode()->LclRotation.Get();

	if (initialTranslate.mData[0] > MINIMUM_TRANSFORMATION_VALUE){
		*m_InitPos->x = initialTranslate.mData[0];
	}
	if (initialTranslate.mData[1] > MINIMUM_TRANSFORMATION_VALUE){
		*m_InitPos->y = initialTranslate.mData[1];
	}
	if (initialTranslate.mData[2] > MINIMUM_TRANSFORMATION_VALUE){
		*m_InitPos->z = initialTranslate.mData[2];
	}

	if (initialScale.mData[0] > MINIMUM_TRANSFORMATION_VALUE){
		*m_InitScale->x = initialScale.mData[0];
	}
	if (initialScale.mData[1] > MINIMUM_TRANSFORMATION_VALUE){
		*m_InitScale->y = initialScale.mData[1];
	}
	if (initialScale.mData[2] > MINIMUM_TRANSFORMATION_VALUE){
		*m_InitScale->z = initialScale.mData[2];
	}

	if (initialRotate.mData[0] > MINIMUM_TRANSFORMATION_VALUE){
		*m_InitRot->x = initialRotate.mData[0];
	}
	if (initialRotate.mData[1] > MINIMUM_TRANSFORMATION_VALUE){
		*m_InitRot->y = initialRotate.mData[1];
	}
	if (initialRotate.mData[2] > MINIMUM_TRANSFORMATION_VALUE){
		*m_InitRot->z = initialRotate.mData[2];
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