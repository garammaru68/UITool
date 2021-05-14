#pragma once
#include "SCore.h"
#include "SShape.h"
#include "UIObject.h"

class Sample : public SCore
{
public:
	bool m_bRS;
	STexture*					m_Texture;
	UIObject*					m_pSelectUI;
	std::vector<UIObject*>	m_vUIList;
public:
	UIObject* CreateUI(POINT cursor, STexture* texture);
	UIObject* SelectUI();

public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};

// ��Ʈ 9�� - ���콺�� ũ�� ����
// ����Ʈ���� Ŭ���ؼ� �巡���ϰ� ������ ��� �ǵ���
// ������ �ؽ��� ũ�� ����, ������ ��Ʈ ǥ��