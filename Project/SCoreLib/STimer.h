#pragma once
#include "SStd.h"
class CStopwatch
{
public:
	// Ÿ�̸��� �ֱ�(1�ʴ� ���� ��)�� ��ȯ
	CStopwatch() { QueryPerformanceFrequency(&m_liPerFreq); Start(); }
	// ���� ���� �ȿ��� �� �� ���� �Ͽ����� �˷��ִ� �Լ�
	void Start() { QueryPerformanceCounter(&m_liPerfStart); }

	__int64 Now()
	{
		LARGE_INTEGER liPerfNow;
		QueryPerformanceCounter(&liPerfNow);
		// ���ۺ��� ������� �ɸ� �ð�
		__int64 qwElapsedTime = (((liPerfNow.QuadPart - m_liPerfStart.QuadPart)));
		return qwElapsedTime;
	}
	void Output(const TCHAR* pData)
	{
#ifdef _DEBUG
		TCHAR strMessage[MAX_PATH] = { 0, };
		__int64 qwElapsedTime = Now();
		float Second = static_cast<float>(qwElapsedTime) / static_cast<float>(m_liPerFreq.QuadPart);
		_stprintf_s(strMessage, _T("<=====%s[%10.4f]=====>\n"), pData, Second);
		OutputDebugString(strMessage);
#endif
	}
private:
	LARGE_INTEGER m_liPerFreq;	// �ʴ� ���
	LARGE_INTEGER m_liPerfStart;; // ���� ���
};

class STimer : public SSingleton<STimer>
{
public:
	float	m_fGameTimer;
	float	m_fSecondPerFrame;
	int		m_iFPS;

	WCHAR	m_szBuffer[256] = { 0, };
	float	m_fBeforeTime;
public:
	bool	Reset();
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
public:
	STimer();
	virtual ~STimer();
};
#define g_Timer STimer::GetInstance()

