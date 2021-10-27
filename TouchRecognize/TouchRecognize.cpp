
// TouchRecognize.cpp:
//

#include "stdafx.h"
#include "TouchRecognize.h"
#include "TouchRecognizeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTouchRecognizeApp

BEGIN_MESSAGE_MAP(CTouchRecognizeApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CTouchRecognizeApp 생성
CTouchRecognizeApp::CTouchRecognizeApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}

// 유일한 CTouchRecognizeApp 개체입니다.
CTouchRecognizeApp theApp;

// CTouchRecognizeApp 초기화
BOOL CTouchRecognizeApp::InitInstance()
{
	CWinApp::InitInstance();

	CTouchRecognizeDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	return FALSE;
}

