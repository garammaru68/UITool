#include "pch.h"
#include "UIObject.h"

bool UIObject::Init()
{
	m_vUIPos.x = 0;
	m_vUIPos.y = 0;

	return true;
}
bool UIObject::Frame()
{
	return true;
}
bool UIObject::Render()
{
	return true;
}
bool UIObject::Release()
{
	return true;
}
void UIObject::Move(float x, float y)
{
	m_vUIPos.x += x;
	m_vUIPos.y += y;
}
void UIObject::Scale(float x, float y)
{
	m_vUIScale.x += x;
	m_vUIScale.y += y;
}
bool UIObject::Update()
{
	Matrix matScale = Matrix::CreateScale(m_vUIScale.x, m_vUIScale.y, 1);
	Matrix matRotate = Matrix::CreateFromYawPitchRoll(m_vUIRotate.x, m_vUIRotate.y, 1);
	m_matUiWorld = matScale * matRotate;
	m_matUiWorld._41 = m_vUIPos.x;
	m_matUiWorld._42 = m_vUIPos.y;

	return true;
}