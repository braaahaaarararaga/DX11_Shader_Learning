cbuffer ConstantBuffer:register(b0)
{
	matrix Projection;
}


void main(
	in float4 inPosition : POSITION0,
	out float4 outPosition : SV_POSITION
)
{
	outPosition = mul(inPosition, Projection);
}