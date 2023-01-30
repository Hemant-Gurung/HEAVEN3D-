struct VS_INPUT
{
	float4 position:POSITION0;
	float2 texcoord:TEXCOORD0;
	
};

struct VS_OUTPUT
{
	float4 position:SV_POSITION;
	float2 texcoord:TEXCOORD0;
};


cbuffer constant:register(b0)
{
	row_major float4x4 world;
	row_major  float4x4 view;
	row_major  float4x4 proj;
	float m_angle;
};

VS_OUTPUT vsmain(VS_INPUT input)
{
	
	VS_OUTPUT output =(VS_OUTPUT)0;
	//output.position = lerp(input.position, input.position1, (sin(m_angle) + 1.0f) / 2.0f);
	// change to world space
	output.position = mul(input.position, world);
	//view space
	output.position = mul(output.position, view);
	//ScreenSpace
	output.position = mul(output.position, proj);

	output.texcoord = input.texcoord;
	return output;
}
