#pragma once
#include "main.h"
#include "renderer.h"
#include "game_object.h"
class Camera : public CGameObject
{
	XMMATRIX	m_ViewMatrix;
	XMMATRIX	m_InvViewMatrix;
	XMMATRIX	m_ProjectionMatrix;

	bool inputValid;
	RECT m_Viewport;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	bool CheckInput();
	XMMATRIX& GetViewMatrix();

};

