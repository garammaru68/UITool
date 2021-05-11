#pragma once
#include "SCore.h"
#include "SShape.h"

class Sample : public SCore
{
public:
	SShapePlane		m_Plane;
public:
	Matrix		m_matPlane;
	Matrix		m_matView;
	Matrix		m_matProj;
public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};
//SGAME_RUN;