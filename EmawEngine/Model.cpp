#include "stdafx.h"
#include "Model.h"


Model::Model()
{
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

void Model::GetFbxInfo(FbxNode* Node)
{
	int children = Node->GetChildCount();
	FbxNode* child = 0;

	for (int i = 0; i < children; i++)
	{
		child = Node->GetChild(i);
		FbxMesh* mesh = child->GetMesh();

		if (mesh != NULL)
		{
			//get vertices, indices, uv, etc.

			//======================== Texture ===============================
			int materialCount = child->GetSrcObjectCount<FbxSurfaceMaterial>();

			for (int index = 0; index < materialCount; index++)
			{
				FbxSurfaceMaterial* material = (FbxSurfaceMaterial*)child->GetSrcObject<FbxSurfaceMaterial>(j);

				if (material != NULL)
				{
					//This only gets the material of type sDiffuse, might need to traverse all 
					//standard material property by its name to get all possible textures.
					FbxProperty prop = material->FindProperty(FbxSurfaceMaterial::sDiffuse);

					//Check if the texture is layered
					int layeredTextureCount = prop.GetSrcObjectCount<FbxLayeredTexture>();

					if (layeredTextureCount > 0)
					{
						for (int j = 0; j < layeredTextureCount; j++)
						{
							FbxLayeredTexture* layered_texture = FbxCast<FbxLayeredTexture>(prop.GetSrcObject<FbxLayeredTexture>(j));
							int layerCount = layered_texture->GetSrcObjectCount<FbxTexture>();

							for (int k = 0; k < layerCount; k++)
							{
								FbxTexture* texture = FbxCast<FbxTexture>(layered_texture->GetSrcObject<FbxTexture>(k));
								//Now we can get all the properties of the texture, including its name
								const char* textureName = (FbxFileTexture*)texture->GetName();
								OutputDebugString((LPCWSTR)textureName);
							}
						}
					}
					else
					{
						//Directly get textures 
						int textureCount = prop.GetSrcObjectCount<FbxTexture>();
						for (int j = 0; j < textureCount; j++)
						{
							FbxTexture* texture = FbxCast<FbxTexture>(prop.GetSrcObject<FbxTexture>(j));
							//Now we can get all the properties of the texture, including its name
							const char* textureName = texture->GetName();
							OutputDebugString((LPCWSTR)textureName);

							FbxProperty p = texture->RootProperty.Find("Filename");

							HRESULT hr;
							D3DX11CreateTextureFromFile(Game::GetInstance()->GetRenderer()->GetDevice(), textureName, 0, 0, &m_texture, &hr);
						}
					}
				}
			}
		}
	}
}