//globals
cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
}

//structs
struct VIn
{
	float4 position : POSITION;
	float4 color : COLOR;
};

struct VOut
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

VOut VShader(float4 position : POSITION, float4 color : COLOR)
{
    VOut output;

    output.position = position;
    output.color = color;

    return output;
}

[maxvertexcount(16)]

void GShader( point VOut voxel[1], inout TriangleStream<VOut> triStream)
{
	VOut v;
	v.color = voxel[0].color;

	//create cube vertices
	//float4 pt1 = { voxel[0].position[0], voxel[0].position[1], voxel[0].position[2], 1.0f };
	//float4 pt2 = { voxel[0].position[0], voxel[0].position[1] + 1.0f, voxel[0].position[2], 1.0f };
	//float4 pt3 = { voxel[0].position[0] + 1.0f, voxel[0].position[1], voxel[0].position[2], 1.0f };
	//float4 pt4 = { voxel[0].position[0] + 1.0f, voxel[0].position[1] + 1.0f, voxel[0].position[2], 1.0f };
	
	float4 pt1 = { voxel[0].position[0] - voxel[0].position[3], voxel[0].position[1] - voxel[0].position[3], voxel[0].position[2] - voxel[0].position[3], 1.0f };
	float4 pt2 = { voxel[0].position[0] - voxel[0].position[3], voxel[0].position[1] + voxel[0].position[3], voxel[0].position[2] - voxel[0].position[3], 1.0f };
	float4 pt3 = { voxel[0].position[0] + voxel[0].position[3], voxel[0].position[1] + voxel[0].position[3], voxel[0].position[2] - voxel[0].position[3], 1.0f };
	float4 pt4 = { voxel[0].position[0] + voxel[0].position[3], voxel[0].position[1] - voxel[0].position[3], voxel[0].position[2] - voxel[0].position[3], 1.0f };
	float4 pt5 = { voxel[0].position[0] + voxel[0].position[3], voxel[0].position[1] - voxel[0].position[3], voxel[0].position[2] + voxel[0].position[3], 1.0f };
	float4 pt6 = { voxel[0].position[0] + voxel[0].position[3], voxel[0].position[1] + voxel[0].position[3], voxel[0].position[2] + voxel[0].position[3], 1.0f };
	float4 pt7 = { voxel[0].position[0] - voxel[0].position[3], voxel[0].position[1] - voxel[0].position[3], voxel[0].position[2] + voxel[0].position[3], 1.0f };
	float4 pt8 = { voxel[0].position[0] - voxel[0].position[3], voxel[0].position[1] + voxel[0].position[3], voxel[0].position[2] + voxel[0].position[3], 1.0f };
	
	//actually put vertices in the triStream (hopefully in the right order)(I need to change this to use an index buffer)
	
	v.position = pt1;//1 vertice number
	triStream.Append(v);

	v.position = pt2;//2
	triStream.Append(v);

	v.position = pt3;//3
	triStream.Append(v);

	v.position = pt8;//4
	triStream.Append(v);

	v.position = pt6;//5
	triStream.Append(v);

	v.position = pt7;//6
	triStream.Append(v);

	v.position = pt5;//7
	triStream.Append(v);

	v.position = pt1;//8
	triStream.Append(v);

	v.position = pt4;//9
	triStream.Append(v);
	
	v.position = pt3;//10
	triStream.Append(v);

	v.position = pt6;//11
	triStream.Append(v);

	v.position = pt5;//12
	triStream.Append(v);

	//make a new triangle strip 'cause I couldn't figure out a way to do the whole cube in one go (there's definitely a way to do it though)
	triStream.RestartStrip();

	v.position = pt8;//13
	triStream.Append(v);

	v.position = pt2;//14
	triStream.Append(v);

	v.position = pt7;//15
	triStream.Append(v);

	v.position = pt1;//16
	triStream.Append(v);
}


float4 PShader(float4 position : SV_POSITION, float4 color : COLOR) : SV_TARGET
{
    return color;
}