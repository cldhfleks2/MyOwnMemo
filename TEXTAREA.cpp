#include "TextArea.h"

LPCWSTR TextArea::ClassName() const
{
	return L"Text";
}

LRESULT TextArea::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_CLOSE) {
		PostQuitMessage(0);
		return 0;
	}
	else if (uMsg == WM_DESTROY) {
		DestroyWindow(hWnd);
		return 0;
	}


	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}