void main(in float4 inPosition : SV_POSITION, in float4 inDiffuse : DIFFUSE,
	out float4 outDiffuse : SV_Target)
{
	outDiffuse =inDiffuse;
}