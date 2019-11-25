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
}
cbuffer LightBuffer : register(b1)
{
    LIGHT Light;

}

void main(
	in float4 inPosition : POSITION0, in float4 inNormal : NORMAL, in float4 inDiffuse : DIFFUSE, in float2 inTexcoord : TEXCOORD,
	out float4 outPosition : SV_POSITION, out float4 outNormal : NORMAL, out float4 outDiffuse : DIFFUSE, out float2 outTexcoord : TEXCOORD
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

    outPosition = mul(inPosition, wvp);
    outNormal = inNormal;
    outDiffuse = inDiffuse * light;
    outTexcoord = inTexcoord;
}