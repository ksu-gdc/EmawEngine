#include "stdafx.h"
#include "Vertex.h"


Vertex::Vertex(Vector3 position, Vector3 normal, Vector2 texture)
{
	this->Position = position;
	this->Normal = normal;
	this->Texture = texture;
}


Vertex::Vertex(f32 x, f32 y, f32 z, f32 nx, f32 ny, f32 nz, f32 u, f32 v) : 
	Vertex(Vector3(x, y, z), Vector3(nx, ny, nz), Vector2(u, v))
{
}


VertexColor::VertexColor(Vector3 position, Vector3 normal, Vector2 textureCoord, 
	ColorFloat vertexColor) : Vertex(position, normal, textureCoord)
{
	this->vertexColor = vertexColor;
}

VertexColor::VertexColor(f32 x, f32 y, f32 z, f32 nx, f32 ny, f32 nz, 
	f32 u, f32 v, f32 r, f32 g, f32 b, f32 a) : 
	VertexColor(Vector3(x, y, z), Vector3(nx, ny, nz), Vector2(u, v),
	ColorFloat(r, g, b, a))
{
}