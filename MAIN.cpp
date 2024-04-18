#include "framework.h"
#include "pch.h"
#include "MAIN.h"

//윈도우에서 발생한 메시지를 처리하는 함수
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	//처리하고싶은 내용들을 작성하는 부분
	//종료메시지를 받지않고 윈도우자체가 파괴된경우 (X 눌렀을때)
	//자신의 응용프로그램에 VM_QUIT메시지를 보내 종료시킴
	if (uMsg == WM_DESTROY)PostQuitMessage(0); //중요
	if (uMsg == WM_CLOSE) {
		int temp = MessageBox(hWnd, TEXT("프로그램을 종료하시겠습니까?"), TEXT("메모장"), MB_ICONQUESTION | MB_OKCANCEL);
		if (temp == IDCANCEL) return 0;

	}

	switch (uMsg) {
	case WM_CREATE: //윈도우가 처음 생성될때 한번만 전달되는 메시지.
		//초기화작업이나 1회성작업등을 추가. 여기서는 쓰지않았다.
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_FILE_MENU1:
			MessageBox(hWnd, TEXT("Menu 1"), TEXT("Menu1 Caption"), MB_OK);
			break;
		}
	}


	//만약내가 처리하지않은 기본 메시지들을 대신 처리해주는 함수
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//윈도우 클래스 등록
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow) {

	WNDCLASS wc;
	wchar_t my_class_name[] = L"아리랑";
	wc.cbClsExtra = NULL; //추가메모리 사용X
	wc.cbWndExtra = NULL; //추가메모리 사용,X
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); //배경을 흰색으로
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); //커서의 핸들값 저장
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //아이콘의 핸들값 저장
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = my_class_name;
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	//윈도우를 생성하는부분
	//hWnd : 윈도우 핸들
	HWND hWnd = CreateWindow(my_class_name, L"test",
		WS_OVERLAPPEDWINDOW, 100, 100, 400, 400, NULL, NULL,
		hInstance, NULL);
	//2번째인자 : 어떤형태로 띄울것인가(처음호출시 생략가능)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);


	//프로그램에 전달된 메시지를 번역, 실행하는부분
	//Win32 프로그램은 운영체제나 다른 프로그램상에
	//메시지를 주고받는 방식. 그래서 항상 메시지를 받도록
	//메시지 큐를 가지고있고 전달받은 메시지로 프로그램을 실행
	MSG msg; //메시지 구조체
	//평상시는 메시지에 0이아닌값을 받으나
	//VM_QUIT메시지를 받으면 0값으로, 반복문이 종료됨
	HACCEL hAccel;
	hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));

	while (GetMessage(&msg, NULL, 0, 0)) {
		//엑셀레이터테이블에 등록된 값이 받아지면은 자동으로
		//WndProc로 넘어가기때문에 if문을 추가해준 모습
		if (!TranslateAccelerator(hWnd, hAccel, &msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	//반복문의 종료는 프로그램의 종료이다.
	return msg.wParam;
}
