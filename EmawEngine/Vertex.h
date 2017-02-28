#pragma once


#include "Vector2.h"
#include "Vector3.h"
#include "Color.h"

enum VertexType
{
	VertexStandard,
	VertexColored,
	VertexCount
};

struct Vertex
{
	Vector3 Position;
	Vector3 Normal;
	Vector2 Texture;

	VertexType GetVertexType()
	{
		return VertexStandard;
	}

	Vertex(Vector3 position, Vector3 normal, Vector2 texture);
	Vertex(f32 x = 0.f, f32 y = 0.f, f32 z = 0.f, 
		f32 nx = 0.f, f32 ny = 0.f, f32 nz = 0.f, 
		f32 u = 0.f, f32 v = 0.f);
};

struct VertexColor : public Vertex
{
	ColorFloat vertexColor;

	VertexType GetVertexType()
	{
		return VertexColored;
	}

	VertexColor(Vector3 position, Vector3 normal, Vector2 texture, ColorFloat color);
	VertexColor(f32 x = 0.f, f32 y = 0.f, f32 z = 0.f, 
		f32 nx = 0.f, f32 ny = 0.f, f32 nz = 0.f, 
		f32 u = 0.f, f32 v = 0.f, 
		f32 r = 0.f, f32 g = 0.f, f32 b = 0.f, f32 a = 1.f);
};

inline u32 GetSize(VertexType type)
{
	if (type == VertexStandard)
		return sizeof(Vertex);

	if (type == VertexColored)
		return sizeof(VertexColor);
}

void* GetLayout(VertexType type);