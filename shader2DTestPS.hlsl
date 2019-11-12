
Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);

void main(in float4 inPosition : SV_POSITION, in float4 inDiffuse : DIFFUSE, in float4 inTexCoord : TEXCOORD,
	out float4 outDiffuse : SV_Target)
{
	outDiffuse = g_Texture.Sample(g_SamplerState, inTexCoord);
	//outDiffuse *=inDiffuse;
}