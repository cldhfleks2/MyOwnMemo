#include "pch.h"
#include "Find.h"
#include "resource.h"

BEGIN_MESSAGE_MAP(Find, CDialog)

ON_COMMAND(IDC_EDIT, &Find::OnEdit)
ON_COMMAND(IDC_UP, &Find::OnUp)
ON_COMMAND(IDC_DOWN, &Find::OnDown)
ON_COMMAND(IDC_NEXT, &Find::OnNext)
ON_COMMAND(IDC_EXIT, &Find::OnExit)
ON_COMMAND(IDC_UPDOWN, &Find::OnUpdown)
ON_WM_DESTROY()
ON_WM_LBUTTONUP()
END_MESSAGE_MAP()




void Find::OnEdit()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void Find::OnUp()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void Find::OnDown()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void Find::OnNext()
{
	//검색하는 부분


}


void Find::OnExit()
{
	

	OnDestroy();
}


void Find::OnUpdown()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void Find::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NEXT, nextbtn);
	DDX_Control(pDX, IDC_EXIT, exitbtn);
}


BOOL Find::OnInitDialog()
{
	CDialog::OnInitDialog();
	my.Attach(GetDlgItem(IDD_FIND)->m_hWnd); //클래스와 컨트롤을 연결



	return TRUE;  
}


void Find::OnDestroy()
{
	CDialog::OnDestroy();

	my.Detach(); //클래스와 컨트롤의 연결해제

	
}

