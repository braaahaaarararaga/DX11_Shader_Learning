cbuffer ConstantBuffer:register(b0)
{
	matrix Projection;
}


void main(
	in float4 inPosition : POSITION0, in float4 inDiffuse : DIFFUSE,
	out float4 outPosition : SV_POSITION, out float4 outDiffuse : DIFFUSE
)
{
	outPosition = mul(inPosition, Projection);
	outDiffuse = inDiffuse;
}