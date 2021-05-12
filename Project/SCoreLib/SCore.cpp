#include "SCore.h"
#include "SObjectManager.h"

HRESULT SCore::DeleteDXResource()
{
	g_dxWrite.DeleteDependentResource();
	return S_OK;
}
HRESULT SCore::CreateDXResource(UINT w, UINT h)
{
	IDXGISurface1* pBackBuffer = nullptr;
	m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface),
		(LPVOID*)&pBackBuffer);
	g_dxWrite.ResizeDevice(w, h, pBackBuffer);
	if (pBackBuffer) pBackBuffer->Release();
	return S_OK;
}
bool	SCore::PreInit()
{
	return true;
};
bool	SCore::Init()
{
	return true;
};
bool	SCore::PostInit()
{

	return true;
};
bool SCore::GameInit()
{
	PreInit();
	m_bGameRun = true;
	if (SDevice::Init() == false)
	{
		return false;
	}
	SetMode(m_bFullScreen);

	g_Timer.Init();
	g_Input.Init();
	g_SoundMgr.Init();

	IDXGISurface1* pBackBuffer = nullptr;
	m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface),
		(LPVOID*)&pBackBuffer);
	g_dxWrite.Set(m_hWnd,
		g_rtClient.right,
		g_rtClient.bottom, pBackBuffer);
	if (pBackBuffer) pBackBuffer->Release();

	m_Camera.CreateViewMatrix({ 0,0,-10 }, { 0,0,0 });
	//float fAspect = g_rtClient.right / (float)g_rtClient.bottom;
	m_Camera.CreateOrthographic(800, 600, 1, 1000);
	//m_Camera.CreateOrthographic(g_rtClient.right, g_rtClient.bottom,1, 100);
	//D3DXMatrixOrthoLH(&m_Projection[1], iRectWidth * 2, iRectHeight * 2, 0.0f, 1000.0f);
	//m_Camera.CreateProjMatrix(1, 1000, SBASIS_PI / 4.0f, fAspect);
	m_Camera.Init();
	m_pMainCamera = &m_Camera;

	//m_Skybox.Create(g_pd3dDevice, L"../../data/shader/skyVS.txt",
	//	L"../../data/shader/skyPS.txt", L"");

	//m_Plane.Create(g_pd3dDevice, L"../../data/shader/VS.txt",
	//	L"../../data/shader/PS.txt", L"../../data/tileA.jpg");

	//if (!m_LineShape.Create(g_pd3dDevice, L"../../data/shader/VS.txt",
	//	L"../../data/shader/PS.txt",
	//	L"../../data/tileA.jpg"))
	//{
	//	return false;
	//}
	g_TexMgr.Init();

	Init();
	PostInit();
	//ShowWindow(m_hWnd, SW_SHOWNORMAL);
	return true;
}
bool SCore::GameRelease()
{
	//m_LineShape.Release();
	//m_Skybox.Release();
	//m_Plane.Release();
	Release();
	g_Timer.Release();
	g_Input.Release();
	g_SoundMgr.Release();
	g_ObjectMgr.Release();
	g_dxWrite.Release();
	SDevice::Release();
	return true;
}
bool	SCore::GameFrame()
{
	PreFrame();
	g_Timer.Frame();
	g_Input.Frame();
	g_SoundMgr.Frame();
	//m_Skybox.Frame();
	//m_Plane.Frame();
	Frame();
	g_ObjectMgr.Frame();
	CameraFrame();
	PostFrame();
	return true;
}
void    SCore::CameraFrame()
{
	if (g_Input.GetKey('W') == KEY_HOLD)
	{
		m_pMainCamera->UpMovement(0.5f);
	}
	if (g_Input.GetKey('S') == KEY_HOLD)
	{
		m_pMainCamera->UpMovement(-0.5f);
	}
	if (g_Input.GetKey('A') == KEY_HOLD)
	{
		m_pMainCamera->RightMovement(-0.5f);
	}
	if (g_Input.GetKey('D') == KEY_HOLD)
	{
		m_pMainCamera->RightMovement(0.5f);
	}
	if (g_Input.GetKey(VK_UP) == KEY_HOLD)
	{
		m_pMainCamera->FrontMovement(1.0f);
	}
	if (g_Input.GetKey(VK_DOWN) == KEY_HOLD)
	{
		m_pMainCamera->FrontMovement(-1.0f);
	}
	if (g_Input.GetKey(VK_SPACE) == KEY_HOLD)
	{
		m_pMainCamera->m_fSpeed += g_fSecondPerFrame * 100.0f;
	}
	else
	{
		m_pMainCamera->m_fSpeed = 100.0f;
	}

	m_pMainCamera->Frame();
}
bool	SCore::PreRender()
{
	SDevice::PreRender();
	//g_pImmediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//m_Skybox.SetMatrix(NULL,
	//	&m_pMainCamera->m_matView,
	//	&m_pMainCamera->m_matProj);
	//m_Skybox.Render(g_pImmediateContext);
	//g_pImmediateContext->RSSetState(SDxState::g_pRSBackCullSolid);
	//g_pImmediateContext->PSSetSamplers(0, 1, &SDxState::g_pSSWrapLinear);
	//g_pImmediateContext->OMSetDepthStencilState(SDxState::g_pDSSDepthEnable, 0);

	//g_pImmediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//m_Plane.SetMatrix(NULL,
	//	&m_pMainCamera->m_matView,
	//	&m_pMainCamera->m_matProj);
	//m_Plane.Render(g_pImmediateContext);
	//g_pImmediateContext->RSSetState(SDxState::g_pRSBackCullSolid);
	//g_pImmediateContext->PSSetSamplers(0, 1, &SDxState::g_pSSWrapLinear);
	//g_pImmediateContext->OMSetDepthStencilState(SDxState::g_pDSSDepthEnable, 0);

	return true;
}
bool	SCore::PostRender()
{
	//m_LineShape.SetMatrix(NULL, &m_pMainCamera->m_matView,
	//	&m_pMainCamera->m_matProj);
	//m_LineShape.Draw(g_pImmediateContext,
	//	Vector3(0, 0, 0), Vector3(100, 0, 0), Vector4(1, 0, 0, 1));
	//m_LineShape.Draw(g_pImmediateContext,
	//	Vector3(0, 0, 0), Vector3(0, 100, 0), Vector4(0, 1, 0, 1));
	//m_LineShape.Draw(g_pImmediateContext,
	//	Vector3(0, 0, 0), Vector3(0, 0, 100), Vector4(0, 0, 1, 1));

	g_Timer.Render();
	g_Input.Render();
	//g_SoundMgr.Render();

	//g_dxWrite.Render();
	//g_dxWrite.Draw(0, 0, g_Timer.m_szBuffer);
	SDevice::PostRender();
	return true;
}
bool	SCore::GameRender()
{
	if (PreRender() == false) return false;
	if (Render() == false) return false;
	if (PostRender() == false) return false;
	return true;
}
bool	SCore::GameRun()
{
	if (GameFrame() == false) return false;
	if (GameRender() == false) return false;
	return true;
}
bool SCore::InitTool(HWND hWnd, HINSTANCE hInstance)
{
	HRESULT hr = S_OK;
	g_hWnd = m_hWnd = hWnd;
	g_hInstance = m_hInstance = hInstance;

	GetClientRect(m_hWnd, &m_rtClient);
	g_rtClient = m_rtClient;
	GetWindowRect(m_hWnd, &m_rtWindow);
	//CoInitializeEx �� COM ���̺귯���� ����ϴ� �� �����忡 ���� �� �� �̻� ȣ���ؾ�  �Ѵ�.

	hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	GameInit();
	return true;
}
bool SCore::ReleaseTool()
{
	GameRelease();
	CoUninitialize();
	return true;
}
bool SCore::Run()
{
	//HeapEnableTerminateOnCorruption �ɼ��� �����ϸ� �ջ�� ���� �̿��ϴ� ���� �ǿ뿡 ���� ���ø����̼��� ������ ���� �� �����Ƿ� �����ϰ� ����.
	//HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	HRESULT hr = S_OK;
	//CoInitializeEx �� COM ���̺귯���� ����ϴ� �� �����忡 ���� �� �� �̻� ȣ���ؾ�  �Ѵ�.
	hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	if (GameInit())
	{
		ShowWindow(m_hWnd, SW_SHOWNORMAL);
	}

	while (m_bGameRun)
	{
		if (MsgProcess() == false)
		{
			m_bGameRun = false;
		}
		else
		{
			if (GameRun() == false)
			{
				break;
			}
		}
	}
	GameRelease();
	CoUninitialize();
	return true;
}
bool SCore::ToolRun()
{
	if (GameFrame() == false) return false;
	if (GameRender() == false) return false;
	return true;
}
SCore::SCore()
{
	m_pMainCamera = nullptr;
}
SCore::~SCore()
{

}