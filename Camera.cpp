
#include "Camera.h"




void Camera::Init()
{

	m_Position = XMFLOAT3(0.0f, 5.0f, -10.0f);
	m_Rotation = XMFLOAT3(0.5f, 0.0f, 0.0f);


	m_Viewport.left = 0;
	m_Viewport.top = 0;
	m_Viewport.right = SCREEN_WIDTH;
	m_Viewport.bottom = SCREEN_HEIGHT;


	// �r���[�|�[�g�ݒ�
	D3D11_VIEWPORT dxViewport;
	dxViewport.Width = (float)(m_Viewport.right - m_Viewport.left);
	dxViewport.Height = (float)(m_Viewport.bottom - m_Viewport.top);
	dxViewport.MinDepth = 0.0f;
	dxViewport.MaxDepth = 1.0f;
	dxViewport.TopLeftX = (float)m_Viewport.left;
	dxViewport.TopLeftY = (float)m_Viewport.top;

	CRenderer::GetDeviceContext()->RSSetViewports(1, &dxViewport);

	// �v���W�F�N�V�����}�g���N�X�ݒ�
	m_ProjectionMatrix = XMMatrixPerspectiveFovLH(1.0f, dxViewport.Width / dxViewport.Height, 1.0f, 1000.0f);

	// �r���[�}�g���N�X�ݒ�
	m_InvViewMatrix = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	m_InvViewMatrix *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

	XMVECTOR det;
	m_ViewMatrix = XMMatrixInverse(&det, m_InvViewMatrix);

}

void Camera::Uninit()
{


}


void Camera::Update()
{
	inputValid = CheckInput();

	if (inputValid)
	{
		// �r���[�}�g���N�X�ݒ�
		m_InvViewMatrix = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
		m_InvViewMatrix *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

		XMVECTOR det;
		m_ViewMatrix = XMMatrixInverse(&det, m_InvViewMatrix);
	}
}

bool Camera::CheckInput()
{
	return false;
}

XMMATRIX & Camera::GetViewMatrix()
{
	return m_ViewMatrix;
}

void Camera::Draw()
{
}