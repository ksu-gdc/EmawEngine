//globals
cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
}

Texture2D ModelTexture : register(t0);
SamplerState MeshTextureSampler
{
    Filter = MIN_MAG_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};

//structs
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

	
	pt1 = mul(worldMatrix, pt1);
	pt1 = mul(viewMatrix, pt1);
	pt1 = mul(projectionMatrix, pt1);
	pt2 = mul(worldMatrix, pt2);
	pt2 = mul(viewMatrix, pt2);
	pt2 = mul(projectionMatrix, pt2);
	pt3 = mul(worldMatrix, pt3);
	pt3 = mul(viewMatrix, pt3);
	pt3 = mul(projectionMatrix, pt3);
	pt4 = mul(worldMatrix, pt4);
	pt4 = mul(viewMatrix, pt4);
	pt4 = mul(projectionMatrix, pt4);
	pt5 = mul(worldMatrix, pt5);
	pt5 = mul(viewMatrix, pt5);
	pt5 = mul(projectionMatrix, pt5);
	pt6 = mul(worldMatrix, pt6);
	pt6 = mul(viewMatrix, pt6);
	pt6 = mul(projectionMatrix, pt6);
	pt7 = mul(worldMatrix, pt7);
	pt7 = mul(viewMatrix, pt7);
	pt7 = mul(projectionMatrix, pt7);
	pt8 = mul(worldMatrix, pt8);
	pt8 = mul(viewMatrix, pt8);
	pt8 = mul(projectionMatrix, pt8);
	

	//actually put vertices in the triStream (hopefully in the right order)(I need to change this to use an index buffer)
	
	v.position = pt4;//1 vertice number
	v.color.r = 1.0f;
	v.color.g = 1.0f;
	triStream.Append(v);

	v.position = pt1;//2
	v.color.r = 0.0f;
	v.color.g = 1.0f;
	triStream.Append(v);

	v.position = pt3;//3
	v.color.r = 1.0f;
	v.color.g = 0.0f;
	triStream.Append(v);

	v.position = pt2;//4
	v.color.r = 0.0f;
	v.color.g = 0.0f;
	triStream.Append(v);

	v.position = pt6;//5
	v.color.r = 1.0f;
	v.color.g = 1.0f;
	triStream.Append(v);

	v.position = pt8;//6
	v.color.r = 0.0f;
	v.color.g = 1.0f;
	triStream.Append(v);

	v.position = pt5;//7
	v.color.r = 1.0f;
	v.color.g = 0.0f;
	triStream.Append(v);

	v.position = pt7;//8
	v.color.r = 0.0f;
	v.color.g = 0.0f;
	triStream.Append(v);

	//make a new triangle strip 'cause I couldn't figure out a way to do the whole cube in one go (there's definitely a way to do it though)
	triStream.RestartStrip();

	v.position = pt8;//9
	v.color.r = 0.0f;
	v.color.g = 0.0f;
	triStream.Append(v);

	v.position = pt2;//10
	v.color.r = 1.0f;
	v.color.g = 0.0f;
	triStream.Append(v);

	v.position = pt7;//11
	v.color.r = 0.0f;
	v.color.g = 1.0f;
	triStream.Append(v);

	v.position = pt1;//12
	v.color.r = 1.0f;
	v.color.g = 1.0f;
	triStream.Append(v);

	v.position = pt5;//13
	v.color.r = 0.0f;
	v.color.g = 0.0f;
	triStream.Append(v);

	v.position = pt4;//14
	v.color.r = 1.0f;
	v.color.g = 0.0f;
	triStream.Append(v);

	v.position = pt6;//15
	v.color.r = 0.0f;
	v.color.g = 1.0f;
	triStream.Append(v);

	v.position = pt3;//16
	v.color.r = 1.0f;
	v.color.g = 1.0f;
	triStream.Append(v);
}


float4 PShader(float4 position : SV_POSITION, float4 color : COLOR) : SV_TARGET
{
	float2 pos;
	pos = float2(color.r, color.g);
    return ModelTexture.Sample(MeshTextureSampler, pos);
}