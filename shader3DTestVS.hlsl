cbuffer ConstantBuffer : register(b0)
{
    matrix World;
    matrix View;
    matrix Projection;
}

void main(
	in float4 inPosition : POSITION0, in float4 inDiffuse : DIFFUSE, in float2 inTexcoord : TEXCOORD,
	out float4 outPosition : SV_POSITION, out float4 outDiffuse : DIFFUSE, out float2 outTexcoord : TEXCOORD
)
{
    matrix wvp;
    wvp = mul(World, View);
    wvp = mul(wvp, Projection);

    outPosition = mul(inPosition, wvp);
    outDiffuse = inDiffuse;
    outTexcoord = inTexcoord;
}