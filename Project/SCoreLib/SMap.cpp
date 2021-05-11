#include "SMap.h"
float SMap::GetHeightmap(int row, int col)
{
	return m_VertexList[row * m_iNumRows + col].p.y;// *1m_MapDesc.fScaleHeight;
}
float SMap::Lerp(float fStart, float fEnd, float fTangent)
{
	return fStart - (fStart*fTangent) + (fEnd*fTangent);
}

float SMap::GetHeightMap(float fPosX, float fPosZ)
{
	// fPosX/fPosZ�� ��ġ�� �ش��ϴ� ���̸ʼ��� ã�´�.
	// m_iNumCols��m_iNumRows�� ����/������ ���� ũ�Ⱚ��.
	float fCellX = (float)(m_iNumCellCols*m_fCellDistance / 2.0f + fPosX);
	float fCellZ = (float)(m_iNumCellRows*m_fCellDistance / 2.0f - fPosZ);

	// ���� ũ��� ������ 0~1 ������ ������ �ٲپ� ���̸� �迭�� �����Ѵ�.
	fCellX /= (float)m_fCellDistance;
	fCellZ /= (float)m_fCellDistance;

	// fCellX, fCellZ ������ �۰ų� ���� �ִ� ����( �Ҽ��κ��� �߶󳽴�.)
	float fVertexCol = ::floorf(fCellX);
	float fVertexRow = ::floorf(fCellZ);

	// ���̸� ������ ����� ������ �ʱ�ȭ �Ѵ�.
	if (fVertexCol < 0.0f)  fVertexCol = 0.0f;
	if (fVertexRow < 0.0f)  fVertexRow = 0.0f;
	if ((float)(m_iNumCols - 2) < fVertexCol)	fVertexCol = (float)(m_iNumCols - 2);
	if ((float)(m_iNumRows - 2) < fVertexRow)	fVertexRow = (float)(m_iNumRows - 2);

	// ���� ���� �÷��� �����ϴ� 4�� ������ ���̰��� ã�´�. 
	//  A   B
	//  *---*
	//  | / |
	//  *---*  
	//  C   D
	float A = GetHeightmap((int)fVertexRow, (int)fVertexCol);
	float B = GetHeightmap((int)fVertexRow, (int)fVertexCol + 1);
	float C = GetHeightmap((int)fVertexRow + 1, (int)fVertexCol);
	float D = GetHeightmap((int)fVertexRow + 1, (int)fVertexCol + 1);

	// A������ ��ġ���� ������ ��(������)�� ����Ѵ�. 0 ~ 1.0f
	float fDeltaX = fCellX - fVertexCol;
	float fDeltaZ = fCellZ - fVertexRow;
	// �����۾��� ���� ���� ���ս��� ã�´�. 
	float fHeight = 0.0f;
	// �����̽��� �������� �����Ѵ�.
	// fDeltaZ + fDeltaX < 1.0f
	if (fDeltaZ < (1.0f - fDeltaX))  //ABC
	{
		float uy = B - A; // A->B
		float vy = C - A; // A->C	
						  // �� ������ ���̰��� ���̸� ���Ͽ� ��ŸX�� ���� ���� �������� ã�´�.		
		fHeight = A + Lerp(0.0f, uy, fDeltaX) + Lerp(0.0f, vy, fDeltaZ);
	}
	// �Ʒ����̽��� �������� �����Ѵ�.
	else // DCB
	{
		float uy = C - D; // D->C
		float vy = B - D; // D->B
						  // �� ������ ���̰��� ���̸� ���Ͽ� ��ŸZ�� ���� ���� �������� ã�´�.		
		fHeight = D + Lerp(0.0f, uy, 1.0f - fDeltaX) + Lerp(0.0f, vy, 1.0f - fDeltaZ);
	}
	return fHeight;
}
float   SMap::GetHeight(UINT index)
{
	return 0.0f;
}
bool    SMap::CreateVertexData()
{
	// ���� ���� �� ���� = 2N��+1
	m_VertexList.resize(m_iNumVertices);
	float fHalfCols = (m_iNumCols - 1) / 2.0f;
	float fHalfRows = (m_iNumRows - 1) / 2.0f;
	float fOffsetU = 1.0f / (m_iNumCols - 1);
	float fOffsetV = 1.0f / (m_iNumRows - 1);
	for (int iRow = 0; iRow < m_iNumRows; iRow++)
	{
		for (int iCol = 0; iCol < m_iNumCols; iCol++)
		{
			int iIndex = iRow * m_iNumCols + iCol;
			m_VertexList[iIndex].p.x = (iCol - fHalfCols)*m_fCellDistance;
			m_VertexList[iIndex].p.y = GetHeight(iIndex);
			m_VertexList[iIndex].p.z = (iRow - fHalfRows)*m_fCellDistance*-1.f;
			m_VertexList[iIndex].t.x = iCol * fOffsetU * 1;
			m_VertexList[iIndex].t.y = iRow * fOffsetV * 1;

			m_VertexList[iIndex].n = GetNormalOfVertex(iIndex);
			m_VertexList[iIndex].c = { 1,1,1,1 };
		}
	}
	return true;
}
Vector3 SMap::GetNormalOfVertex(UINT Index)
{
	return Vector3(0.0f, 1.0f, 0.0f);
}
bool    SMap::CreateIndexData()
{
	m_IndexList.resize(m_iNumFaces * 3);
	int iIndex = 0;
	for (int iRow = 0; iRow < m_iNumCellRows; iRow++)
	{
		for (int iCol = 0; iCol < m_iNumCellCols; iCol++)
		{
			int iNextRow = iRow + 1;
			int iNextCol = iCol + 1;
			m_IndexList[iIndex + 0] = iRow * m_iNumCols + iCol;
			m_IndexList[iIndex + 1] = iRow * m_iNumCols + iNextCol;
			m_IndexList[iIndex + 2] = iNextRow * m_iNumCols + iCol;
			m_IndexList[iIndex + 3] = m_IndexList[iIndex + 2];
			m_IndexList[iIndex + 4] = m_IndexList[iIndex + 1];
			m_IndexList[iIndex + 5] = iNextRow * m_iNumCols + iNextCol;
			iIndex += 6;
		}
	}
	m_iNumFaces = m_IndexList.size() / 3;
	GetVertexNormal();

	return true;
}
void SMap::GetVertexNormal()
{
	InitFaceNormals();
	GenNormalLookupTable();
	CalcPerVertexNormalsFastLookup();
}
Vector3 SMap::ComputeFaceNormal(DWORD i0, DWORD i1, DWORD i2)
{
	Vector3 normal;
	Vector3 v0 = m_VertexList[i1].p - m_VertexList[i0].p;
	Vector3 v1 = m_VertexList[i2].p - m_VertexList[i0].p;
	normal = v0.Cross(v1);
	normal.Normalize();
	return normal;
}
void SMap::CalcFaceNormals()
{
	int index = 0;
	for (int i = 0; i < m_iNumFaces * 3; i += 3)
	{
		m_FaceNormals[index++] = ComputeFaceNormal(
			m_IndexList[i],
			m_IndexList[i + 1],
			m_IndexList[i + 2]);
	}
}
void SMap::InitFaceNormals()
{
	m_FaceNormals.resize(m_iNumFaces);
	for (int i = 0; i < m_iNumFaces; i++)
	{
		m_FaceNormals[i] = Vector3::Zero;
	}
}
void SMap::GenNormalLookupTable()
{
	m_LookupTable.resize(m_iNumVertices);
	for (int iFace = 0; iFace < m_iNumFaces; iFace++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 6; k++)
			{
				int id = m_IndexList[iFace * 3 + j];
				if (m_LookupTable[id].index[k] == -1)
				{
					m_LookupTable[id].index[k] = iFace;
					break;
				}
			}
		}
	}
}
void SMap::CalcPerVertexNormalsFastLookup()
{
	CalcFaceNormals();
	for (int i = 0; i < m_iNumVertices; i++)
	{
		Vector3 avgNormal = { 0,0,0 };
		for (int f = 0; f < 6; f++)
		{
			int index = m_LookupTable[i].index[f];
			if (index != -1)
			{
				avgNormal += m_FaceNormals[index];
			}
			else
			{
				break;
			}
		}
		m_VertexList[i].n = avgNormal;
		m_VertexList[i].n.Normalize();
	}
}
bool	SMap::Frame()
{
	return true;
}
bool	SMap::PostRender(ID3D11DeviceContext*	pd3dContext)
{
	pd3dContext->DrawIndexed(m_iNumFaces * 3, 0, 0);
	return true;
}
bool SMap::CreateMap(ID3D11Device* pDevice,
	ID3D11DeviceContext* pContext, SMapDesc  desc)
{
	m_MapDesc = desc;
	m_iNumRows = desc.iNumRows;
	m_iNumCols = desc.iNumCols;
	m_iNumCellCols = m_iNumCols - 1;
	m_iNumCellRows = m_iNumRows - 1;
	m_iNumVertices = m_iNumCols * m_iNumRows;
	m_iNumFaces = m_iNumCellCols * m_iNumCellRows * 2;
	m_fCellDistance = desc.fCellDistance;

	Create(pDevice,
		desc.szVS,
		desc.szPS,
		desc.szTexFile);
	return true;
}
SMap::SMap()
{

}
SMap::~SMap()
{

}
//#include "SMap.h"
//float SMap::GetHeightmap(int row, int col)
//{
//	return m_VertexList[row * m_iNumRows + col].p.y;// * m_MapDesc.fScaleHeight;
//}
//float SMap::GetHeightOfVertex(UINT Index)
//{
//	return 0.0f;
//};
//Vector3 SMap::GetNormalOfVertex(UINT Index)
//{
//	return Vector3(0.0f, 1.0f, 0.0f);
//};
//Vector4 SMap::GetColorOfVertex(UINT Index)
//{
//	return Vector4(1, 1, 1, 1.0f);
//};
//Vector2 SMap::GetTextureOfVertex(float fOffsetX, float fOffsetY)
//{
//	return Vector2(fOffsetX, fOffsetY);
//};
//
//float SMap::Lerp(float fStart, float fEnd, float fTangent)
//{
//	return fStart - (fStart*fTangent) + (fEnd*fTangent);
//}
//
//float SMap::GetHeight(float fPosX, float fPosZ)
//{
//	// fPosX/fPosZ�� ��ġ�� �ش��ϴ� ���̸ʼ��� ã�´�.
//	// m_iNumCols��m_iNumRows�� ����/������ ���� ũ�Ⱚ��.
//	float fCellX = (float)(m_iNumCellCols*m_fCellDistance / 2.0f + fPosX);
//	float fCellZ = (float)(m_iNumCellRows*m_fCellDistance / 2.0f - fPosZ);
//
//	// ���� ũ��� ������ 0~1 ������ ������ �ٲپ� ���̸� �迭�� �����Ѵ�.
//	fCellX /= (float)m_fCellDistance;
//	fCellZ /= (float)m_fCellDistance;
//
//	// fCellX, fCellZ ������ �۰ų� ���� �ִ� ����( �Ҽ��κ��� �߶󳽴�.)
//	float fVertexCol = ::floorf(fCellX);
//	float fVertexRow = ::floorf(fCellZ);
//
//	// ���̸� ������ ����� ������ �ʱ�ȭ �Ѵ�.
//	if (fVertexCol < 0.0f)  fVertexCol = 0.0f;
//	if (fVertexRow < 0.0f)  fVertexRow = 0.0f;
//	if ((float)(m_iNumCols - 2) < fVertexCol)	fVertexCol = (float)(m_iNumCols - 2);
//	if ((float)(m_iNumRows - 2) < fVertexRow)	fVertexRow = (float)(m_iNumRows - 2);
//
//	// ���� ���� �÷��� �����ϴ� 4�� ������ ���̰��� ã�´�. 
//	//  A   B
//	//  *---*
//	//  | / |
//	//  *---*  
//	//  C   D
//	float A = GetHeightmap((int)fVertexRow, (int)fVertexCol);
//	float B = GetHeightmap((int)fVertexRow, (int)fVertexCol + 1);
//	float C = GetHeightmap((int)fVertexRow + 1, (int)fVertexCol);
//	float D = GetHeightmap((int)fVertexRow + 1, (int)fVertexCol + 1);
//
//	// A������ ��ġ���� ������ ��(������)�� ����Ѵ�. 0 ~ 1.0f
//	float fDeltaX = fCellX - fVertexCol;
//	float fDeltaZ = fCellZ - fVertexRow;
//	// �����۾��� ���� ���� ���ս��� ã�´�. 
//	float fHeight = 0.0f;
//	// �����̽��� �������� �����Ѵ�.
//	// fDeltaZ + fDeltaX < 1.0f
//	if (fDeltaZ < (1.0f - fDeltaX))  //ABC
//	{
//		float uy = B - A; // A->B
//		float vy = C - A; // A->C	
//						  // �� ������ ���̰��� ���̸� ���Ͽ� ��ŸX�� ���� ���� �������� ã�´�.		
//		fHeight = A + Lerp(0.0f, uy, fDeltaX) + Lerp(0.0f, vy, fDeltaZ);
//	}
//	// �Ʒ����̽��� �������� �����Ѵ�.
//	else // DCB
//	{
//		float uy = C - D; // D->C
//		float vy = B - D; // D->B
//						  // �� ������ ���̰��� ���̸� ���Ͽ� ��ŸZ�� ���� ���� �������� ã�´�.		
//		fHeight = D + Lerp(0.0f, uy, 1.0f - fDeltaX) + Lerp(0.0f, vy, 1.0f - fDeltaZ);
//	}
//	return fHeight;
//}
//bool    SMap::CreateVertexData()
//{
//	// ���� ���� �� ���� = 2N��+1
//	m_VertexList.resize(m_iNumVertices);
//	float fHalfCols = (m_iNumCols - 1) / 2.0f;
//	float fHalfRows = (m_iNumRows - 1) / 2.0f;
//	float fOffsetU = 1.0f / (m_iNumCols - 1);
//	float fOffsetV = 1.0f / (m_iNumRows - 1);
//	for (int iRow = 0; iRow < m_iNumRows; iRow++)
//	{
//		for (int iCol = 0; iCol < m_iNumCols; iCol++)
//		{
//			int iIndex = iRow * m_iNumCols + iCol;
//			m_VertexList[iIndex].p.x = (iCol - fHalfCols)*m_fCellDistance;
//			m_VertexList[iIndex].p.y = GetHeightOfVertex(iIndex);
//			m_VertexList[iIndex].p.z = (iRow - fHalfRows)*m_fCellDistance*-1.f;
//			m_VertexList[iIndex].t.x = iCol * fOffsetU * 1;
//			m_VertexList[iIndex].t.y = iRow * fOffsetV * 1;
//
//			m_VertexList[iIndex].n = { 0,1,0 };
//			m_VertexList[iIndex].c = { 1,1,1,1 };
//		}
//	}
//	return true;
//}
//bool    SMap::CreateIndexData()
//{
//	m_IndexList.resize(m_iNumFaces * 3);
//	int iIndex = 0;
//	for (int iRow = 0; iRow < m_iNumCellRows; iRow++)
//	{
//		for (int iCol = 0; iCol < m_iNumCellCols; iCol++)
//		{
//			int iNextRow = iRow + 1;
//			int iNextCol = iCol + 1;
//			m_IndexList[iIndex + 0] = iRow * m_iNumCols + iCol;
//			m_IndexList[iIndex + 1] = iRow * m_iNumCols + iNextCol;
//			m_IndexList[iIndex + 2] = iNextRow * m_iNumCols + iCol;
//			m_IndexList[iIndex + 3] = m_IndexList[iIndex + 2];
//			m_IndexList[iIndex + 4] = m_IndexList[iIndex + 1];
//			m_IndexList[iIndex + 5] = iNextRow * m_iNumCols + iNextCol;
//			iIndex += 6;
//		}
//	}
//	m_iNumFaces = m_IndexList.size() / 3;
//
//	GetVertexNormal();
//
//	return true;
//}
//bool	SMap::Frame()
//{
//	return true;
//}
//bool	SMap::PostRender(ID3D11DeviceContext*	pd3dContext)
//{
//	pd3dContext->DrawIndexed(m_iNumFaces * 3, 0, 0);
//	return true;
//}
//
//bool SMap::Release()
//{
//	if (m_pNormalLookupTable)
//	{
//		free(m_pNormalLookupTable);
//		m_pNormalLookupTable = NULL;
//	}
//
//	if (m_pFaceNormals != NULL)
//	{
//		delete m_pFaceNormals;
//		m_pFaceNormals = NULL;
//	}
//	return true;
//}
//bool SMap::CreateMap(ID3D11Device* pDevice,
//	ID3D11DeviceContext* pContext, SMapDesc  desc)
//{
//	m_MapDesc = desc;
//	m_iNumRows = desc.iNumRows;
//	m_iNumCols = desc.iNumCols;
//	m_iNumCellCols = m_iNumCols - 1;
//	m_iNumCellRows = m_iNumRows - 1;
//	m_iNumVertices = m_iNumCols * m_iNumRows;
//	m_iNumFaces = m_iNumCellCols * m_iNumCellRows * 2;
//	m_fCellDistance = desc.fCellDistance;
//
//	Create(pDevice,
//		desc.szVS,
//		desc.szPS,
//		desc.szTexFile);
//	return true;
//}
//bool SMap::GetVertexNormal()
//{
//	InitFaceNormals();
//	GetNormalLookupTable();
//	CalcPerVertexNormalsFastLookup();
//	return true;
//}
//void SMap::CalcVertexColor(Vector3  vLightDir)
//{
//	for (int iRow = 0; iRow < m_iNumRows; iRow++)
//	{
//		for (int iCol = 0; iCol < m_iNumCols; iCol++)
//		{
//			int iVertexIndex = iRow * m_iNumCols + iCol;
//
//			float fDot =
//			-(vLightDir.Dot(m_VertexList[iVertexIndex].n));
//			m_VertexList[iVertexIndex].c *= fDot;
//			m_VertexList[iVertexIndex].c.w = 1.0f;
//		}
//	}
//}
//void SMap::InitFaceNormals()
//{
//	m_pFaceNormals = new Vector3[m_iNumFace];
//
//	for (int i = 0; i < m_iNumFace; i++)
//	{
//		m_pFaceNormals[i] = Vector3(0.0f, 0.0f, 0.0f);
//	}
//}
//void SMap::CalcFaceNormals()
//{
//	// Loop over how many faces there are
//	int j = 0;
//	for (int i = 0; i < m_iNumFace * 3; i += 3)
//	{
//		DWORD i0 = m_IndexList[i];
//		DWORD i1 = m_IndexList[i + 1];
//		DWORD i2 = m_IndexList[i + 2];
//		m_pFaceNormals[j] = ComputeFaceNormal(i0, i1, i2);
//		j++;
//	}
//}
//Vector3 SMap::ComputeFaceNormal(DWORD dwIndex0, DWORD dwIndex1, DWORD dwIndex2)
//{
//	Vector3 vNormal;
//	Vector3 v0 = m_VertexList[dwIndex1].p - m_VertexList[dwIndex0].p;
//	Vector3 v1 = m_VertexList[dwIndex2].p - m_VertexList[dwIndex0].p;
//
//	vNormal = v0.Cross(v1);
//	vNormal.Normalize();
//	Matrix matScale;
//
//	return vNormal;
//}
//void SMap::GetNormalLookupTable()
//{
//	if (m_pNormalLookupTable != NULL)
//	{
//		free(m_pNormalLookupTable);
//		m_pNormalLookupTable = NULL;
//	}
//
//	int buffersize = m_iNumRows * m_iNumCols * 6;
//
//	m_pNormalLookupTable = (int *)malloc(sizeof(void *) * buffersize);
//	for (int i = 0; i < buffersize; i++)
//		m_pNormalLookupTable[i] = -1;
//
//	for (int i = 0; i < m_iNumFace; i++)
//	{
//		for (int j = 0; j < 3; j++)
//		{
//			for (int k = 0; k < 6; k++)
//			{
//				int vertex = m_IndexList[i * 3 + j];
//				if (m_pNormalLookupTable[vertex * 6 + k] == -1)
//				{
//					m_pNormalLookupTable[vertex * 6 + k] = i;
//					break;
//				}
//			}
//		}
//	}
//}
//void SMap::CalcPerVertexNormalsFastLookup()
//{
//	CalcFaceNormals();
//
//	int j = 0;
//	for (int i = 0; i < m_iNumVertices; i++)
//	{
//		Vector3 avgNormal;
//		avgNormal = Vector3(0.0f, 0.0f, 0.0f);
//
//		for (j = 0; j < 6; j++)
//		{
//			int triIndex;
//			triIndex = m_pNormalLookupTable[i * 6 + j];
//
//			if (triIndex != -1)
//			{
//				avgNormal += m_pFaceNormals[triIndex];
//			}
//			else
//				break;
//		}
//
//		//_ASSERT(j > 0);
//		avgNormal.x /= (float)j;
//		avgNormal.y /= (float)j;
//		avgNormal.z /= (float)j;
//		avgNormal.Normalize();
//
//		m_VertexList[i].n.x = avgNormal.x;
//		m_VertexList[i].n.y = avgNormal.y;
//		m_VertexList[i].n.z = avgNormal.z;
//
//	}
//
//	if (m_bStaticLight) CalcVertexColor(m_vLightDir);
//}
//SMap::SMap()
//{
//	m_pFaceNormals = nullptr;
//}
//SMap::~SMap()
//{
//
//}