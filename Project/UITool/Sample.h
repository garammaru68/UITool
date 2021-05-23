#pragma once
#include "SCore.h"
#include "SShape.h"
#include "UIObject.h"

class Sample : public SCore
{
public:
	bool		m_bRS;
	bool		m_bClickState;
	POINT		sCursorPos;
	POINT		eCursorPos;
	Vector2	vUiPos;
	Vector2	v2;
	Vector2	m_vDownPos;
	Vector2	m_vUpPos;
	STexture*					m_Texture;
	STexture*					m_ChangeTexture;
	UIObject*					m_pSelectUI;
	std::vector<UIObject*>	m_vUIList;
	std::vector<int>		m_iTest;

public:
	UIObject*	CreateUI(POINT cursor, STexture* texture);
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

// ��Ʈ 9�� - ���콺�� ũ�� ����
// ����Ʈ���� Ŭ���ؼ� �巡���ϰ� ������ ��� �ǵ���
// ������ �ؽ��� ũ�� ����, ������ ��Ʈ ǥ��