struct LIGHT
{
    float4 Direction;
    float4 Diffuse;
    float4 Ambient;
};

cbuffer ConstantBuffer : register(b0)
{
    matrix World;
    matrix View;
    matrix Projection;
    float4 CameraPosition;
}
cbuffer LightBuffer : register(b1)
{
    LIGHT Light;

}

void main(
	in float4 inPosition : POSITION0, in float4 inNormal : NORMAL, in float4 inDiffuse : DIFFUSE, in float2 inTexcoord : TEXCOORD,
	out float4 outPosition : SV_POSITION, out float4 outNormal : NORMAL, out float4 outDiffuse : DIFFUSE, out float4  outSpecular : COLOAR1, out float2 outTexcoord : TEXCOORD
)
{
    matrix wvp;
    wvp = mul(World, View);
    wvp = mul(wvp, Projection);
    inNormal.w = 0.0;
    float4 worldNormal = mul(inNormal, World);
    worldNormal = normalize(worldNormal);
    float light = -dot(worldNormal, Light.Direction);
    light = saturate(light);

    float4 worldPosition = mul(inPosition, World);
    float3 refv = reflect(Light.Direction.xyz, worldNormal.xyz); // ”½ŽË‚ðŒvŽZ‚·‚é
    refv = normalize(refv);
    float3 eyev = worldPosition - CameraPosition;
    eyev = normalize(eyev);
    float specular = -dot(eyev, refv);
    specular = saturate(specular);
    specular = pow(specular, 10);
    outSpecular = specular;
    
    outPosition = mul(inPosition, wvp);
    outNormal = inNormal;
    outDiffuse = inDiffuse * light;
    outTexcoord = inTexcoord;
}