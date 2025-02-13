#include "pch.h"
#include "TimeManager.h"
#include "Core.h"
#include "InputManager.h"
void TimeManager::Init()
{
	// ī��Ʈ�� �����ؼ� �����´�.
	::QueryPerformanceCounter(&m_llPrevCnt);
	
	// �ʴ� ī��Ʈ Ƚ��(1�ʴ� 1000��) ��ȯ
	::QueryPerformanceFrequency(&m_llFrequency);
}

void TimeManager::Update()
{
	::QueryPerformanceCounter(&m_llCurCnt);
	
	// deltatime(��ȭ�ð�) : �� �����ӿ� �ɸ� �ð� 
	m_unscaledDT = (float)(m_llCurCnt.QuadPart - m_llPrevCnt.QuadPart)
		/ (float)m_llFrequency.QuadPart;

	m_dT = m_unscaledDT * timeScale;

	m_llPrevCnt = m_llCurCnt;

	// FPS(Frame Per Second): 1�ʴ� �� ������ ����.
	m_framecnt++; // ������ üũ Ƚ���� ���
	m_frametime += m_dT; // �����ð��� ���
	if (m_frametime >= 1.f) // 1��
	{
		m_fps = (UINT)(m_framecnt / m_frametime);
		m_frametime = 0.f;
		m_framecnt = 0;
		
		static wchar_t buf[100] = {};
		swprintf_s(buf, L"FPS: %d",m_fps);
		::SetWindowText(GET_SINGLE(Core)->GetHwnd(), buf);
	}

	time += m_dT;
	m_unscaledTime += m_unscaledDT;
}
