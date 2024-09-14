#pragma once
#include "baseWindow.h"

class TextArea :public BaseWindow<TextArea> {

public:
	virtual LPCWSTR ClassName() const;
	virtual LRESULT HandleMessage(UINT, WPARAM, LPARAM);
};