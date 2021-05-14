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

// 렉트 9개 - 마우스로 크기 조정
// 리스트에서 클릭해서 드래그하고 놓으면 출력 되도록
// 선택한 텍스쳐 크기 조절, 선택한 렉트 표시