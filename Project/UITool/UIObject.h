#pragma once
#include "SShape.h"

class UIObject
{
public:
	SShapeUI m_PlaneUI;
public:
	Matrix	m_matUiWorld;
	Matrix	m_matUiView;
	Matrix	m_matUiProj;

	Vector2	m_vUIScale;
	Vector2	m_vUIRotate;
	Vector2	m_vUIPos;

	RECT		m_rt;
public:
	void	Move(float x, float y);
	void	Scale(float x, float y);
	bool	Update();
	bool	matUpdate();
	bool	Save();

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
};