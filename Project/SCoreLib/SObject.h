#pragma once
#include "SBitmapManager.h"
#include "SCollision.h"
#include "SDxObject.h"
typedef std::vector<RECT>  RECT_ARRAY;

enum SObjectType {
	BACKGROUND = 0,
	UICONTROL,
	USER,
	NPC,
};
enum SControlState {
	DEFAULT = 0,
	PUSH,
	SELECT,
	DISABLE,
};
enum SOverlapState {
	OVERLAP_NONE = 0,
	OVERLAP_BEGIN,
	OVERLAP_STAY,
	OVERLAP_END,
};
struct SObjAttribute
{
	int iObjType;
	wstring szName;
	wstring szParentName;
	wstring colorbitmap;
	wstring pushbitmap;
	wstring selectbitmap;
	wstring disbitmap;
	wstring maskbitmap;
	SPoint  pos;
	RECT   rtSrc;
	RECT   rtDesk;
	bool   bColorKey;
	DWORD  dwColor;
	int	   iVisible;
	int	   iEnable;
};
struct SSpriteInfo
{
	wstring		colorbitmap;
	wstring		maskbitmap;
	RECT_ARRAY	rtArray;
	wstring		szName;
	wstring		szParentName;
};
enum SCollisionType
{
	S_IGNORE = 0,		/// �����Ѵ�.
	S_OVERLAP,			/// ��ĥ �� �ִ�.
	S_BLOCKING			/// ��ø�� �� ���� ���ŷ �ȴ�.
};
enum SSelectState
{
	S_DEFAULT = 0,  /// ���콺�� ���� ���� ��( T_FOCUS���¿��� �ٸ� ���� T_ACTIVE ���� ���°� �Ǿ��� �� ��ȯ�ȴ�.)
	S_HOVER = 1,	/// ���콺�� ���� ���� ��	
	S_FOCUS = 2,	/// T_ACTIVE���� ���콺�� ���� ��ư�� �ٸ� ������ ������ ��( �Ǵ� ��, ����Ű ���� ���, ��Ÿ ���)	
	S_ACTIVE = 4,	/// ���콺 ���� ��ư�� ������ ���� ��(Ű ������ KEY_HOLD�� ����)	
	S_SELECTED = 8, /// T_ACTIVE���� ���콺�� ���� ��ư�� ������ ������ ��( ���Ŀ��� T_FOCUS�� �ȴ�.)
};
class SObject : public SDxObject
{
public:
	int			m_iIndex;			 /// ��� ������Ʈ�� �߱޵Ǵ� ������ �ε���	
	DWORD		m_dwSvrID;			 /// ������ ��� �� ������ �ε���
	int			m_iObjectType;	     /// SObjectType ������Ʈ Ÿ��
public:
	int			m_iCollisionObjectID;/// ������Ʈ �޴����� ��� �� �浹 �ε���
	int			m_iSelecSObjectID;	 /// ������Ʈ �޴����� ��ϵ� ���콺 ���� �ε���
	bool		m_bCollisionEnabled; /// �浹ó������ �Ǵ�(���콺 ������ ó���ȴ�.)
	int			m_iCollisionType;	 /// SCollisionType�� ���� ó���Ѵ�.
	DWORD		m_dwOverlapState;	 /// ������ ����
	DWORD		m_dwSelectState;	 /// ���콺 ���� ����
	int			m_iImageState;
public:
	wstring     m_szName;
	wstring		m_szParentName;
	SObject*	m_pParentObject;
	SObjAttribute m_Attribute;
	std::vector<SObject*>	m_pChildObjects;
public:
	//TBitmap*	m_pMaskBmp;
	//TBitmap*	m_pColorBmp;
	//std::vector<TBitmap*> m_StateBitmap;
	RECT		m_rtSrc;		/// ���� �̹��� ����
	RECT		m_rtDesk;		/// �ʱ� ȭ�� ��ο� ����
	RECT		m_rtDraw;		/// ���� ��ο� ����
	RECT		m_rtCollide;	/// ���� �浹 ����
	bool		m_bColorKey;	/// �÷�Ű ��� ����
	DWORD		m_dwColorKey;	/// �÷�Ű �÷� ��
	int			m_iSortValue;	/// Z�� ���ĵ�
public:
	SPoint		m_ptPos;
	float		m_fSpeed;
	SPoint		m_ptDirection;
	SPoint		m_ptPreDirection;
	bool		m_bDead;
	bool		m_bSelect;
	float		m_fLifeTime;
	float		m_fAttackTimer;
	float		m_fAlphaBlend;
	bool		m_bDrawDebugRect;
public:
	/// object Index, overlap State
	std::map<int, DWORD>	m_OverlapState;
	DWORD					Overlap(int iIndex);
	virtual void			HitOverlap(SObject* pDesk, DWORD dwState);
	virtual void			MouseOverlap(POINT ptMousepos, DWORD dwState);
public:
	virtual SObject* Clone();
	virtual bool  Reset();
	virtual bool  Init();
	virtual bool  PreFrame();
	virtual bool  Frame();
	virtual bool  PostFrame();
	virtual bool  PreRender(ID3D11DeviceContext*	pd3dContext);
	virtual bool  Render(ID3D11DeviceContext*	pd3dContext);
	virtual bool  PostRender(ID3D11DeviceContext*	pd3dContext);
	virtual bool  Release();
	virtual void  Update();
	virtual void  SetDir(float* p);
	virtual void  SetPos(float* d);
	virtual void  SetDir(SPoint p);
	virtual void  SetPos(SPoint p);
	virtual void  Set(SPoint p, RECT rtSrc);

	virtual void  SetPosTL(SPoint p);
	virtual void  SetSpeed(float fSpeed);
	virtual void  Set(RECT rtSrc, RECT rtDesk);
	virtual bool  Load(const TCHAR* color,
		const TCHAR* mask = nullptr,
		DWORD dwColor = RGB(255, 0, 255));
	virtual void  DrawColorKey();
public:
	virtual bool Damage() { return false; };
	virtual bool Dead() { return true; };
	virtual void Attack(SObject* pPlayer) {};
public:
	virtual void SetTransition(DWORD dwEevnt) {};
public:
	SObject();
	virtual ~SObject();
};

