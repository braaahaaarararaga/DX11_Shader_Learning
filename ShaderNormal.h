#pragma once
#include "main.h"
#include "renderer.h"


struct CONSTANT_NORMAL
{
	XMFLOAT4X4 WorldMatrix;
	XMFLOAT4X4 ViewMatrix;
	XMFLOAT4X4 ProjectionMatrix;
};

struct CONSTANT_COMMON
{
	XMFLOAT4   CameraPosition;
};

class ShaderNormal 
{
private:
	ID3D11VertexShader*     m_VertexShader;
	ID3D11PixelShader*      m_PixelShader;
	ID3D11InputLayout*      m_VertexLayout;

	ID3D11Buffer*			m_ConstantBuffer;
	ID3D11Buffer*			m_CommonBuffer;
	ID3D11Buffer*			m_LightBuffer;
	CONSTANT_NORMAL			m_Constant;
	CONSTANT_COMMON			m_Constant_common;
	LIGHT					m_Light;

public:
	void Init(const char* VertexShader, const char* PixelShader);
	void Uninit();
	void Set();

	void SetProjectionMatrix(XMFLOAT4X4* ProjectionMatrix) { m_Constant.ProjectionMatrix = Transpose(ProjectionMatrix); }
	void SetViewMatrix(XMFLOAT4X4* ViewMatrix) { m_Constant.ViewMatrix = Transpose(ViewMatrix); }
	void SetWorldMatrix(XMFLOAT4X4* WorldMatrix) { m_Constant.WorldMatrix = Transpose(WorldMatrix); }
	void SetCameraPosition(XMFLOAT3& cameraPosition)
	{
		XMFLOAT4 camPos;
		camPos.x = cameraPosition.x;
		camPos.y = cameraPosition.y;
		camPos.z = cameraPosition.z;
		camPos.w = 0.0f;
		m_Constant_common.CameraPosition = camPos;
	}

	XMFLOAT4X4 Transpose(XMFLOAT4X4* Matrix)
	{
		XMFLOAT4X4 outMatrix;

		outMatrix._11 = Matrix->_11;
		outMatrix._12 = Matrix->_21;
		outMatrix._13 = Matrix->_31;
		outMatrix._14 = Matrix->_41;

		outMatrix._21 = Matrix->_12;
		outMatrix._22 = Matrix->_22;
		outMatrix._23 = Matrix->_32;
		outMatrix._24 = Matrix->_42;

		outMatrix._31 = Matrix->_13;
		outMatrix._32 = Matrix->_23;
		outMatrix._33 = Matrix->_33;
		outMatrix._34 = Matrix->_43;

		outMatrix._41 = Matrix->_14;
		outMatrix._42 = Matrix->_24;
		outMatrix._43 = Matrix->_34;
		outMatrix._44 = Matrix->_44;

		return outMatrix;
	}

};

