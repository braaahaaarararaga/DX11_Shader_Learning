#include "Field.h"
#include "scene.h"
#include "input.h"


Field::Field()
	:
	m_Rotation(0.0f, 0.0f, 0.0f)
{
}


Field::~Field()
{
}

void Field::Init()
{
	VERTEX_3D_NORMAL vertex[4];

	vertex[0].Position = XMFLOAT3(-10.0f, 0.0f, 10.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Binormal = XMFLOAT3(1.0f, 0.0f, 0.0f);
	vertex[0].Tangent = XMFLOAT3(0.0f, 0.0f, 1.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(10.0f, 0.0f,10.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Binormal = XMFLOAT3(1.0f, 0.0f, 0.0f);
	vertex[1].Tangent = XMFLOAT3(0.0f, 0.0f, 1.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(-10.0f, 0.0f, -10.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Binormal = XMFLOAT3(1.0f, 0.0f, 0.0f);
	vertex[2].Tangent = XMFLOAT3(0.0f, 0.0f, 1.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(10.0f, 0.0f, -10.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Binormal = XMFLOAT3(1.0f, 0.0f, 0.0f);
	vertex[3].Tangent = XMFLOAT3(0.0f, 0.0f, 1.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);


	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D_NORMAL) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	m_Texture[0] = new CTexture();
	m_Texture[0]->Load("data/TEXTURE/Rock_Normal.tga");
	m_Texture[1] = new CTexture();
	m_Texture[1]->Load("data/TEXTURE/cocoon.tga");

	m_Shader = new CShader();
	m_Shader->Init("x64/Debug/shader3DTestVS.cso", "x64/Debug/Shader3DTextPS.cso");
}

void Field::Uninit()
{
	m_Shader->Uninit();
	delete m_Shader;

	m_VertexBuffer->Release();

	m_Texture[0]->Unload();
	m_Texture[1]->Unload();
	delete m_Texture[0];
	delete m_Texture[1];
}

void Field::Update()
{
	int input = CInput::GetKeyPress('J') - CInput::GetKeyPress('L');
	if (input)
	{
		m_Rotation.z += input * 0.1f;
	}
	input = CInput::GetKeyPress('I') - CInput::GetKeyPress('K');
	if (input)
	{
		m_Rotation.x += input * 0.1f;
	}
}

void Field::Draw()
{

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D_NORMAL);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	CRenderer::SetTexture(m_Texture[0], m_Texture[1]);

	XMMATRIX world;
	world = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	world *= XMMatrixTranslation(0.0f, -5.0f, 0.0f);

	XMFLOAT4X4 projection;
	XMFLOAT4X4 matrix;
	DirectX::XMStoreFloat4x4(&projection, XMMatrixPerspectiveFovLH(XM_PI / 2, (float)SCREEN_WIDTH/ (float)SCREEN_HEIGHT, 0.1f, 1000.0f));
	XMStoreFloat4x4(&matrix, world);
	m_Shader->SetWorldMatrix(&matrix);
	Camera* camera = CManager::GetScene()->GetGameObjects<Camera>().front();
	XMStoreFloat4x4(&matrix, camera->GetViewMatrix());
	m_Shader->SetViewMatrix(&matrix);
	m_Shader->SetProjectionMatrix(&projection);
	XMFLOAT3 camPos = camera->GetPosition();
	m_Shader->SetCameraPosition(camPos);

	m_Shader->Set();


	// プリミティブトポロジ設定
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴン描画
	CRenderer::GetDeviceContext()->Draw(4, 0);
}
