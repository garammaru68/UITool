#include "pch.h"
#include "UIObject.h"

bool UIObject::Init()
{
	m_vUIPos.x = 0;
	m_vUIPos.y = 0;
	m_vUIScale.x = 100;
	m_vUIScale.y = 100;
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
	m_PlaneUI.m_matWorld._41 = m_PlaneUI.m_matWorld._41 + m_vUIPos.x;
	m_PlaneUI.m_matWorld._42 = m_PlaneUI.m_matWorld._42 + m_vUIPos.y;
	m_PlaneUI.m_matWorld._11 = m_vUIScale.x;
	m_PlaneUI.m_matWorld._22 = m_vUIScale.y;

	return true;
}
bool UIObject::matUpdate()
{
	Matrix matScale = Matrix::CreateScale(m_vUIScale.x, m_vUIScale.y, 1);
	m_PlaneUI.m_matWorld = matScale * m_PlaneUI.m_matWorld;
	g_pImmediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_PlaneUI.SetMatrix(&m_PlaneUI.m_matWorld, &m_PlaneUI.m_matView, &m_PlaneUI.m_matProj);
	return true;
}