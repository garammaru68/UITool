#pragma once
#include "SShape.h"

class UIObject
{
public:
	//SShapePlane m_PlaneUI;
	SShapeUI m_PlaneUI;

public:
	Matrix m_matUI;
	Matrix m_matView;
	Matrix m_matProj;
public:
	bool	Update(Matrix View, Matrix Proj, POINT cursor);
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
};

class UIForm : public UIObject
{
public:
	std::vector<SShapePlane*> m_pUIFormList;
public:
	//SShapePlane* CreateUIForm(Matrix View, Matrix Proj, POINT cursor, STexture* texture);
	
};