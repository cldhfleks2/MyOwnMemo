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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}


void Find::OnUp()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}


void Find::OnDown()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}


void Find::OnNext()
{
	//�˻��ϴ� �κ�


}


void Find::OnExit()
{
	

	OnDestroy();
}


void Find::OnUpdown()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void Find::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NEXT, nextbtn);
	DDX_Control(pDX, IDC_EXIT, exitbtn);
}


BOOL Find::OnInitDialog()
{
	CDialog::OnInitDialog();
	my.Attach(GetDlgItem(IDD_FIND)->m_hWnd); //Ŭ������ ��Ʈ���� ����



	return TRUE;  
}


void Find::OnDestroy()
{
	CDialog::OnDestroy();

	my.Detach(); //Ŭ������ ��Ʈ���� ��������

	
}

