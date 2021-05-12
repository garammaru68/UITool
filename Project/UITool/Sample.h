#pragma once
#include "SCore.h"
#include "SShape.h"

class Sample : public SCore
{
public:
	SShapePlane		m_Plane;
	STexture*		m_Texture;
	std::vector<SShapePlane*>	m_vPlaneList;
public:
	Matrix		m_matPlane;
	Matrix		m_matView;
	Matrix		m_matProj;
	std::vector<Matrix>		m_vMatrixList;
public:
	SShapePlane* AddUI();
	bool		Update(POINT cursor);

public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};
//SGAME_RUN;