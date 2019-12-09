#pragma once
#include "main.h"
#include "renderer.h"
#include "game_object.h"
#include "texture.h"
#include "ShaderNormal.h"
#include "manager.h"
#include "Camera.h"

class CScene;
class Field : public CGameObject
{
private:

	ID3D11Buffer*	m_VertexBuffer = NULL;
	ShaderNormal*		m_Shader;

	CTexture*		m_Texture;

	XMFLOAT3 m_Rotation;

public:
	Field();
	~Field();

	void Init();
	void Uninit();
	void Update();
	void Draw();
};

