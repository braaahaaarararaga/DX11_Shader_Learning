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

cbuffer CommonBuffer : register(b2)
{
    float4 cameraPosition;
}

Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);

void main(
    in float4 inPosition : SV_POSITION,
    in float4 inWorld : POSITION1,
    in float4 inNormal : NORMAL0,
    in float4 inBinormal : BINORMAL0,
    in float4 inTangent : TANGENT0,
    in float4 inDiffuse : DIFFUSE,
    in float2 inTexCoord : TEXCOORD,
	out float4 outDiffuse : SV_Target)
{
    float3 normalMap = g_Texture.Sample(g_SamplerState, inTexCoord).xyz;
    float3 normal = (normalMap * 2.0) - 1.0;
    normal.y *= -1;
    //normalMap = (normalMap.x * inBinormal) + (normalMap.y * inTangent) + (normalMap.z * inNormal);
    float3x3 tbn = float3x3(normalize(inBinormal.xyz), normalize(inTangent.xyz), normalize(inNormal.xyz));
    normal = normalize(mul(normalMap, tbn));
    //outDiffuse *= g_Texture[1].Sample(g_SamplerState, inTexCoord);
    outDiffuse = inDiffuse *0.3;
    float3 refv = reflect(Light.Direction.xyz, normal); // ”½ŽË‚ðŒvŽZ‚·‚é
    refv = normalize(refv);
    float3 eyev = inWorld - cameraPosition;
    eyev = normalize(eyev);
    float specular = -dot(eyev, refv);
    specular = saturate(specular);
    specular = pow(specular, 128);
    outDiffuse += specular;
    
    float light = -dot(normal, Light.Direction.xyz);
    light = saturate(light);
    outDiffuse *= light;
    outDiffuse.a = 1.0;
    // monochrome outDiffuse.rgb = (outDiffuse.r * 0.299 + outDiffuse.g * 0.587 + outDiffuse.b * 0.114);
   
}