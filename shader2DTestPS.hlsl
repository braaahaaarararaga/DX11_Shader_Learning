
Texture2D g_Texture[2] : register(t0);
SamplerState g_SamplerState : register(s0);

void main(in float4 inPosition : SV_POSITION, in float4 inDiffuse : DIFFUSE, in float2 inTexCoord : TEXCOORD,
	out float4 outDiffuse : SV_Target)
{
	outDiffuse = g_Texture[0].Sample(g_SamplerState, inTexCoord); 
	outDiffuse *= g_Texture[1].Sample(g_SamplerState, inTexCoord); 
    // monochrome outDiffuse.rgb = (outDiffuse.r * 0.299 + outDiffuse.g * 0.587 + outDiffuse.b * 0.114);
   
}