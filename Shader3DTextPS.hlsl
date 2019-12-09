struct LIGHT
{
    float4 Direction;
    float4 Diffuse;
    float4 Ambient;
};
cbuffer LightBuffer : register(b1)
{
    LIGHT Light;

}

Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);

void main(in float4 inPosition : SV_POSITION, in float4 inWorld : POSITION1, in float4 inNormal : NORMAL0, in float4 inDiffuse : DIFFUSE, in float2 inTexCoord : TEXCOORD,
	out float4 outDiffuse : SV_Target)
{
    outDiffuse = g_Texture.Sample(g_SamplerState, inTexCoord);
    //outDiffuse *= g_Texture[1].Sample(g_SamplerState, inTexCoord);
    outDiffuse *= inDiffuse;
    //outDiffuse += inSpecular;
    inNormal = normalize(inNormal);
    float light = -dot(inNormal.xyz, Light.Direction.xyz);
    light = saturate(light);
    outDiffuse *= light;
    outDiffuse.a = 1.0;
    // monochrome outDiffuse.rgb = (outDiffuse.r * 0.299 + outDiffuse.g * 0.587 + outDiffuse.b * 0.114);
   
}