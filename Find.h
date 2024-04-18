#pragma once
#undef _WINDOWS_
#include "afxdialogex.h"

class Find :
    public CDialog
{
private:
    CEdit my;

public:
    DECLARE_MESSAGE_MAP()
    afx_msg void OnEdit();
    afx_msg void OnUp();
    afx_msg void OnDown();
    afx_msg void OnNext();
    afx_msg void OnExit();
    afx_msg void OnUpdown();
    void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();
    afx_msg void OnDestroy();
    CButton nextbtn;
    CButton exitbtn;
};

