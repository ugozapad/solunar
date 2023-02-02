// test hlsl shader

cbuffer GlobalData : register(b0)
{
	float4x4 g_modelMatrix;
	float4x4 g_viewMatrix;
	float4x4 g_projectionMatrix;
}

struct VS_INPUT
{
	float3 position : POSITION;
	float3 normal : NORMAL;
	float2 texcoord : TEXCOORD;
};

struct PS_INPUT
{
	float4 position : SV_POSITION;
	float3 normal : TEXCOORD0;
	float2 texcoord : TEXCOORD1;
};

PS_INPUT VSMain(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT)0;

	// translate vertex to mvp matrix
	output.position = mul(float4(input.position, 1.0f), g_modelMatrix);
	output.position = mul(output.position, g_viewMatrix);
	output.position = mul(output.position, g_projectionMatrix);

	// translate normal to world space
	output.normal = mul(input.normal, (float3x3)g_modelMatrix);

	// texcoord
	output.texcoord = input.texcoord;

	return output;
}

float4 PSMain(PS_INPUT input) : SV_Target
{
	return float4(0.2f, 0.3f, 0.4f, 1.0f);
}
