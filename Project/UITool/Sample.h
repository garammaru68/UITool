#pragma once
#include "SCore.h"
#include "SShape.h"
#include "UIObject.h"

class Sample : public SCore
{
public:
	bool		m_bRS;
	bool		m_bClickState;
	float		m_fLeft;
	POINT		sCursorPos;
	POINT		eCursorPos;
	Vector2	v2;
	Vector2	vUiPos;
	Vector2	m_vDownPos;
	Vector2	m_vUpPos;
	Vector2	m_vUiScale;
	Vector2	m_vDownScale;
	Vector2	m_vUpScale;
	STexture*					m_Texture;
	STexture*					m_ChangeTexture;
	UIObject*					m_pSelectUI;
	std::vector<UIObject*>	m_vUIList;

public:
	//UIObject*	CreateUI(POINT cursor, STexture* texture);
	UIObject*	CreateUI(Vector2 uiScale, STexture* texture);
	UIObject*	SelectUI();
	Vector2		ClickDown();
	Vector2		ClickUp();
	POINT		MoveDistance();
	bool		Delete();

public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
public:
	Sample(void);
	virtual ~Sample(void);
};

// 렉트 9개 - 마우스로 크기 조정
// 리스트에서 클릭해서 드래그하고 놓으면 출력 되도록
// 선택한 텍스쳐 크기 조절, 선택한 렉트 표시