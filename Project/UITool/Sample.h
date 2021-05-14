#pragma once
#include "SCore.h"
#include "SShape.h"
#include "UIObject.h"

class Sample : public SCore
{
public:
	//SShapePlane		m_Plane;
	STexture*		m_Texture;
	std::vector<UIObject*>		m_vUIList;
public:
	Matrix		m_matPlane;
	Matrix		m_matView;
	Matrix		m_matProj;
public:
	UIObject*	m_pUIObject;
	UIObject* CreateUI(POINT cursor, STexture* texture);
	UIObject* CreateUIForm(POINT cursor, STexture* texture);

public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};
//SGAME_RUN;

// ��Ʈ 9�� - ���콺�� ũ�� ����
// ����Ʈ���� Ŭ���ؼ� �巡���ϰ� ������ ��� �ǵ���