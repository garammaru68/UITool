#pragma once
#include "SCore.h"
#include "SObject.h"
#include "SInput.h"
#include "SShape.h"

class UIObject : public SObject
{
public:
	SShapeUI m_PlaneUI;
public:
	Matrix	m_matUiWorld;
	Matrix	m_matUiView;
	Matrix	m_matUiProj;

	Vector2	m_vUIScale;
	Vector2	m_vUIRotate;
	Vector3	m_vUIPos;

	float		m_fSpeed = 100.0f;

	RECT		m_rt;
public:
	void	SetData(float fLeft);
	void	Move(float x, float y);
	void	Scale(float x, float y);
	void	MouseScale(float x, float y);
	bool	UpdateSRT();
	bool	UpdateMat();
	bool	Save();

public:
	bool Init();
	bool Frame();
	bool Render();
	virtual bool Release();
};