#include "pch.h"
#include "UIObject.h"

bool UIObject::Init()
{
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
void UIObject::SetData(float fLeft)
{
	m_PlaneUI.fLeft = 1.0f - fLeft;
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
void UIObject::MouseScale(float x, float y)
{
	m_vUIScale.x = x;
	m_vUIScale.y = y;
}
bool UIObject::UpdateSRT()
{
	m_PlaneUI.m_matWorld._11 = m_vUIScale.x;
	m_PlaneUI.m_matWorld._22 = m_vUIScale.y;

	return true;
}
bool UIObject::UpdateMat()
{
	Matrix matScale = Matrix::CreateScale(m_vUIScale.x, m_vUIScale.y, 1);
	m_PlaneUI.m_matWorld = matScale * m_PlaneUI.m_matWorld;
	g_pImmediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_PlaneUI.SetMatrix(&m_PlaneUI.m_matWorld, &m_PlaneUI.m_matView, &m_PlaneUI.m_matProj);
	return true;
}