#include "pch.h"
#include "framework.h"
#include "MEMO.h"
#include <windows.h>
#include <commctrl.h>
#include <commdlg.h>
#if defined _M_IX86
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#pragma comment(lib,"comctl32.lib")
#define BUFSIZE 256

//식별자들
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL WINAPI findDlgProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
void save(HWND hWnd);
void save_as(HWND hWnd);
void open(HWND hWnd);
void saveDlgBox(HWND hWnd);

HWND Edit;
HINSTANCE Global_hInstance;
TCHAR FILEPATH[500] = L"제목 없음 - 낙서장";
int str_CHANGE = 0;
int CANCEL = 0;
//const TCHAR* dragStr = TEXT("Clipboard Test"); //클립보드내용

//윈도우에서 발생한 메시지를 처리하는 함수
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	//처리하고싶은 내용들을 작성하는 부분
	RECT rt;
	////클립보드 기능구현을 위한 변수들
	//HGLOBAL hmem; //대용량 메모리 동적할당하는 변수 . 윈도우용 메모리 할당 변수
	//TCHAR* clipPtr;
	
	//새창 띄우는 작업을 위한 변수


	switch (uMsg) {
	case WM_CREATE: //윈도우가 처음 생성될때 한번만 전달되는 메시지.
		GetClientRect(hWnd, &rt);
		//텍스트를 입력할 Edit윈도우 생성부분
		//메인 윈도우와 같은크기로 생성한다.
		Edit = CreateWindow(L"edit", NULL, WS_CHILD |
			WS_VSCROLL | WS_VISIBLE | ES_MULTILINE, 
			rt.left, rt.top, rt.right, rt.bottom, 
			hWnd, NULL, Global_hInstance, NULL);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
	//종료메시지를 받지않고 윈도우자체가 파괴된경우 (X 눌렀을때)
	//자신의 응용프로그램에 VM_QUIT메시지를 보내 종료시킴
	case WM_SIZE:
		GetClientRect(hWnd, &rt); //메인윈도우크기가 변경될경우 그값을 얻어옴
		//Edit윈도우크기를 메인윈도우크기와 동일하도록
		MoveWindow(Edit, rt.left, rt.top, rt.right, rt.bottom, TRUE);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_FILE_MENU1: //새로만들기
			saveDlgBox(hWnd);
			if (CANCEL != 1) {
				DestroyWindow(Edit);
				SendMessage(hWnd, WM_CREATE, 0, 0);
				SetWindowText(hWnd, L"제목 없음 - 낙서장");
			}
			else { //취소버튼을 누른경우
				CANCEL = 0;
			}
			break;
		case ID_FILE_MENU2: //새창
			//CreateProcess(0, "MEMO.exe", 0, 0, FALSE, 0, 0, 0, &si, &pi);
			break;
		case ID_FILE_MENU3: //열기
			saveDlgBox(hWnd);
			if (CANCEL != 1) {
				open(hWnd);
			}
			else { //취소버튼을 누른경우
				CANCEL = 0;
			}
			break;
		case ID_FILE_MENU4: //저장
			save(hWnd);
			break;
		case ID_FILE_MENU5: //다른이름으로 저장
			save_as(hWnd);
			break;
		case ID_FILE_MENU6: //끝내기
			saveDlgBox(hWnd);
			if (CANCEL != 1) {
				PostQuitMessage(0);
			}
			else { //취소버튼을 누른경우
				CANCEL = 0; 
			}
			break;
		case ID_EDIT_MENU1: //실행취소
			SendMessage(Edit, WM_UNDO, 0, 0);
			break;

		case ID_EDIT_MENU2: //잘라내기
			SendMessage(Edit, WM_CUT, 0, 0);
			break;

		case ID_EDIT_MENU3: //복사하기 (클립보드 활용)
			SendMessage(Edit, WM_COPY, 0, 0);
			//아래지운 코드를 위의 코드한줄로 대체가능
			//hmem = GlobalAlloc(GHND, lstrlen(dragStr) * 2 + 1); //유니코드문자열이므로 메모리 2배할당
			//clipPtr = (TCHAR*)GlobalLock(hmem); //타 프로그램이 메모리를 건드리지못하게 잠금
			//memcpy(clipPtr, dragStr, lstrlen(dragStr) * 2 + 1); 
			//GlobalUnlock(hmem); //사용끝났으니 잠금해제
			//if (OpenClipboard(hWnd)) {//클립보드를 연다.
			//	EmptyClipboard(); //클립보드를 비움
			//	SetClipboardData(CF_TEXT, hmem); //현재 내용을 복사
			//	CloseClipboard();
			//}
			//else {
			//	GlobalFree(hmem); //오류날시, 바로 메모리해제
			//}
			//break;
		case ID_EDIT_MENU4: //붙여넣기 (클립보드 활용)
			SendMessage(Edit, WM_PASTE, 0, 0);
			//아래지운 코드를 위의 코드한줄로 대체가능
			//if (IsClipboardFormatAvailable(CF_TEXT)) { //클립보드내용이 텍스트일때
			//	OpenClipboard(hWnd); //클립보드를 연다.
			//	hmem = GetClipboardData(CF_TEXT); //클립보드에서 텍스트를 가져옴
			//	clipPtr = (TCHAR*)GlobalLock(hmem); //이전처럼 메모리 잠금
			//	//현재 에디터에 저장된 유니코드를 불러옴
			//	LRESULT write_len = SendMessage(Edit, WM_GETTEXTLENGTH, 0, 0);
			//	LPTSTR unicode_str = (TCHAR*)malloc(sizeof(TCHAR) * (write_len + 1));
			//	GetWindowText(Edit, unicode_str, write_len + 1);
			//	LPTSTR res = unicode_str + *clipPtr; //현재 에디터의 문자열 + 클립보드내용
			//	SetWindowText(Edit, res); //텍스트변경
			//	GlobalUnlock(hmem); //메모리 잠금해제
			//	CloseClipboard();
			//}
			//break;
		case ID_EDIT_MENU5: //삭제
			SendMessage(Edit, WM_CLEAR, 0, 0);
			break;


		case ID_EDIT_MENU6: //찾기
			//다이얼로그창을 만들자.
			//현재 에디터의 문자열을 불러와서 거기서 검색,
			//찾은 인덱스들을 vector에 저장
			//찾는 방향에 따라서
			//모든 vector를 순회하며 하나씩 보여줌
			//보여줄때 	SendMessage(Edit, EM_SETSEL, 위치, 위치 + 길이); 사용한다.

			//그냥 findDlgProc 쓰면 오류
			//만약 BOOL이 아닌 bool형리턴이었다면 매개변수로 INT_PTR이 필요하므로
			//(DLGPROC)& 으로 주소연산자를 이용하여 INT_PTR로 강제 형변환시켜야함
			DialogBox(Global_hInstance, MAKEINTRESOURCE(IDD_FIND), hWnd, findDlgProc);


			break;

		case ID_EDIT_MENU7: //바꾸기
			break;

		case ID_EDIT_MENU8: //모두선택
			SendMessage(Edit, EM_SETSEL, 0, -1); //전체범위 선택
			break;


		}
		switch (HIWORD(wParam)) {
		case EN_CHANGE: //편집컨트롤의 텍스트변경시 발생하는 메세지.
			str_CHANGE = 1; //문자열 변경이이루어짐을 기록
			break;
		}
		break;
	case WM_CLOSE:
		saveDlgBox(hWnd);
		if (CANCEL != 1) {
			PostQuitMessage(0);
		}
		else {
			CANCEL = 0;
		}
		return 0;
	}
	//이외에 처리하지지않은 기본 메세지들을 대신 처리해주는 함수
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//SendMessage : 윈도우창에 메세지를 보냄
//SendDlgItemMessage : 윈도우창의 컨트롤에 메세지를 보냄
BOOL WINAPI findDlgProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {
	case WM_INITDIALOG:
		break;
	}

	return FALSE; //DefWindowProc와 비슷한 기능
}

void save_as(HWND hWnd) {
	OPENFILENAME Save; //파일 열기/저장 대화상자에 사용될 구조체
	//name : 파일명 최대길이 255
	//title : 최대길이 255 + " - 낙서장"의 6자 더함
	TCHAR name[256] = L"*.txt", title[261]; 
	//file : 새로운파일(경로명 포함)을 만들기위한 핸들
	//filename : 위의 파일에서 경로명을 제외한 파일명만을 가지는 핸들
	HANDLE file, filename;
	//메모장의 edit윈도우에 작성된 내용의 길이
	//LRESULT : 이를 얻기위해 쓰인 SendMessage의 반환값타입
	LRESULT write_len;
	LPTSTR unicode_str; //edit윈도우에 작성된 유니코드를 저장하는 변수
	char* multibyte_str; //유니코드문자열을 멀티바이트로 변환후 저장하는 변수
	WIN32_FIND_DATA WFD; //WIN32_FIND_DATA 구조체..
	int multibyte_len; //유니코드 문자열을 멀티바이트로 변환시 필요한 멀티바이트문자열 길이
	//구조체를 초기화안할시 쓰레기값이 들어가므로, 초기화
	memset(&Save, 0, sizeof(Save));
	Save.lStructSize = sizeof(Save); //구조체의 크기지정
	Save.hwndOwner = hWnd; //낙서장의 핸들값을 지정하여 공통대화상자를 소유하게댐
	//공통대화상자에 쓰일 필터들. 각각 \0으로 구분
	Save.lpstrFilter = L"텍스트 문서(*.txt)\0*.txt\0모든 파일(*.*)\0*.*";
	Save.lpstrFile = name; //파일이름과 경로를 저장할 배열을 전달
	Save.nMaxFile = sizeof(name); //해당 배열의 크기
	Save.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT; //사용할 옵션지정
	Save.lpstrDefExt = L"*.txt"; //기본확장자 지정

	if (GetSaveFileName(&Save) != 0) { //정상인지 체크
		wsprintf(FILEPATH, L"%s", Save.lpstrFile); //파일경로변수에 값넣기
		//파일을 만들고, 해당파일의 핸들을 file로 지정.
		file = CreateFile(Save.lpstrFile,
			GENERIC_READ | GENERIC_WRITE, NULL, NULL,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		//Edit윈도우에 WM_GETTEXTLENGTH메시지를 보내고 결괏값을 변수에저장
		write_len = SendMessage(Edit, WM_GETTEXTLENGTH, 0, 0);
		//unicode_str배열을 write_len에 맞게 동적할당 그후 포인터를받음
		unicode_str = (TCHAR*)malloc(sizeof(TCHAR) * (write_len + 1));
		multibyte_str = (CHAR*)malloc(sizeof(TCHAR) * (write_len + 1));
		//배열들을 할당후 0으로 초기화 
		memset(unicode_str, 0, sizeof(TCHAR) * (write_len + 1));
		memset(multibyte_str, 0, sizeof(TCHAR) * (write_len + 1));

		//Edit윈도우의 모든 문자열을 가져옴
		GetWindowText(Edit, unicode_str, write_len + 1);

		//유니코드문자열을 멀티바이트 문자열로 바꿀시 길이를 받음.
		multibyte_len = WideCharToMultiByte(CP_UTF8, WC_NO_BEST_FIT_CHARS, unicode_str,
			lstrlen(unicode_str), NULL, NULL, NULL, NULL);
		//해당 길이를 이용하여 변환
		WideCharToMultiByte(CP_UTF8, WC_NO_BEST_FIT_CHARS, unicode_str,
			lstrlen(unicode_str), multibyte_str, multibyte_len, NULL, NULL);
		//생성됬던파일(핸들이용)에 멀티바이트문자열을 쓰기
		WriteFile(file, multibyte_str, strlen(multibyte_str), (LPDWORD)&multibyte_len, NULL);

		//핸들을 초기화 작업(파일명관련핸들)
		filename = FindFirstFile(Save.lpstrFile, &WFD);
		//낙서장 타이틀지정전에 파일명길이에맞게초기화작업
		memset(title, 0, sizeof(TCHAR) * (lstrlen(WFD.cFileName) + 1));
		//낙서장 타이틀 변수에 값넣기
		wsprintf(title, L"%s - 낙서장", WFD.cFileName);
		//낙서장 타이틀 변경
		SetWindowText(hWnd, title);

		//동적할당된 배열들 메모리 해제
		free(unicode_str);
		free(multibyte_str);
		//핸들 전부 닫기
		FindClose(filename);
		CloseHandle(file);

		//성공적으로 저장이끝났음을 알림. 이부분을통해 내용이변경되었음을
		//사용자에게 다시알려 저장할것인가를 물을 수 있음
		str_CHANGE = 0;
	}
	else {
		//사용자가 공용대화상자에서 저장버튼이아닌 취소버튼을 눌렀을때 처리.
		CANCEL = 1;
	}
}

void save(HWND hWnd) {
	TCHAR title[261]; //최대파일명은 255, 거기에 " - 낙서장" 6자합친길이
	HANDLE file; 
	LRESULT write_len;
	LPTSTR unicode_str;
	char* multibyte_str;
	int multibyte_len;

	GetWindowText(hWnd, title, 261);
	if (lstrcmp(title, L"제목 없음 - 낙서장") == 0) { //처음 저장할시
		save_as(hWnd);
	}
	else {
		file = CreateFile(FILEPATH, GENERIC_READ | GENERIC_WRITE, 
			NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		write_len = SendMessage(Edit, WM_GETTEXTLENGTH, 0, 0);
		multibyte_len = sizeof(TCHAR) * (write_len + 1);
		unicode_str = (TCHAR*)malloc(sizeof(TCHAR) * (write_len + 1));
		multibyte_str = (CHAR*)malloc(sizeof(TCHAR) * (write_len + 1));
		memset(unicode_str, 0, sizeof(TCHAR) * (write_len + 1));
		memset(multibyte_str, 0, sizeof(TCHAR) * (write_len + 1));

		GetWindowText(Edit, unicode_str, write_len + 1);

		multibyte_len = WideCharToMultiByte(CP_UTF8, WC_NO_BEST_FIT_CHARS, unicode_str,
			lstrlen(unicode_str), NULL, NULL, NULL, NULL);
		WideCharToMultiByte(CP_UTF8, WC_NO_BEST_FIT_CHARS, unicode_str, lstrlen(unicode_str), multibyte_str, multibyte_len, NULL, NULL);
		WriteFile(file, multibyte_str, strlen(multibyte_str), (LPDWORD)&multibyte_len, NULL);

		free(unicode_str);
		free(multibyte_str);
		CloseHandle(file);

		str_CHANGE = 0;
	}
}

void open(HWND hWnd) {
	OPENFILENAME Open;
	TCHAR name[256] = L"", title[261];
	HANDLE file, filename;
	LPTSTR unicode_str;
	char* multibyte_str;
	WIN32_FIND_DATA WFD;
	int filesize, unicode_len;
	DWORD size; //ReadFile함수에 쓰일 크기변수.

	memset(&Open, 0, sizeof(Open));
	Open.lStructSize = sizeof(Open);
	Open.hwndOwner = hWnd;
	Open.lpstrFilter = L"텍스트 문서(*.txt)\0*.txt\0모든 파일(*.*)\0*.*";
	Open.lpstrFile = name;
	Open.nMaxFile = sizeof(name);
	Open.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;
	Open.lpstrDefExt = L"*.txt";
	if (GetOpenFileName(&Open) != 0) {
		wsprintf(FILEPATH, L"%s", Open.lpstrFile);
		file = CreateFile(Open.lpstrFile, GENERIC_READ | GENERIC_WRITE, 
			NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		filesize = GetFileSize(file, NULL);
		multibyte_str = (CHAR*)malloc(sizeof(TCHAR) * (filesize + 1));
		unicode_str = (TCHAR*)malloc(sizeof(TCHAR) * (filesize + 1));

		memset(multibyte_str, 0, sizeof(TCHAR) * (filesize + 1));
		memset(unicode_str, 0, sizeof(TCHAR) * (filesize + 1));
		ReadFile(file, multibyte_str, filesize, &size, NULL); //파일을 읽음
		//읽은 멀티바이트 문자열을 유니코드문자열로 바꾸기위함
		unicode_len = MultiByteToWideChar(CP_UTF8, MB_PRECOMPOSED, multibyte_str, strlen(multibyte_str), NULL, NULL);
		MultiByteToWideChar(CP_UTF8, MB_PRECOMPOSED, multibyte_str, strlen(multibyte_str), unicode_str, unicode_len);

		SetWindowText(Edit, unicode_str);
		filename = FindFirstFile(Open.lpstrFile, &WFD);
		memset(title, 0, sizeof(TCHAR) * (lstrlen(WFD.cFileName) + 1));
		wsprintf(title, L"%s - 낙서장", WFD.cFileName);
		SetWindowText(hWnd, title);

		free(multibyte_str);
		free(unicode_str);
		FindClose(filename);
		CloseHandle(file);

		str_CHANGE = 0;
	}
}

void saveDlgBox(HWND hWnd) {
	TASKDIALOGCONFIG TDBOX; //이번엔 새로운구조체를 사용
	//두 버튼을 배열로 선언
	const TASKDIALOG_BUTTON TDBUTTON[] = { {IDOK, L"저장"}, {IDNO, L"저장 안함"} };
	LRESULT editstr_len; //문자열의 길이
	LPTSTR MessageStr; //메세지 박스에 표시할 문자열을 저장할 변수
	int result = 0, multibyte_len = 0;
	memset(&TDBOX, 0, sizeof(TDBOX)); //구조체 정상작동을위한 초기화
	TDBOX.cbSize = sizeof(TDBOX);
	TDBOX.hwndParent = hWnd; //부모핸들을 메인윈도우로..
	TDBOX.hInstance = Global_hInstance; //WINAPI인자인 hInstance로 지정
	TDBOX.dwCommonButtons = TDCBF_CANCEL_BUTTON; //취소버튼을 추가하기위함
	TDBOX.pszWindowTitle = L"낙서장"; //메세지박스의 타이틀
	TDBOX.pButtons = TDBUTTON; //선언한 버튼들을 지정
	TDBOX.cButtons = ARRAYSIZE(TDBUTTON); //2 라는 값과 같음

	if (lstrcmp(FILEPATH, L"제목 없음 - 낙서장") == 0) {
		//Edit윈도우로부터 문자열의 길이를 받아옴
		editstr_len = SendMessage(Edit, WM_GETTEXTLENGTH, 0, 0); 
		if (editstr_len > 0) { //문자가 하나로있으면 아래코드 실행
			//메세지 박스 내용 지정
			TDBOX.pszMainInstruction = L"작업 내용을 제목 없음으로 저장 하시겠습니까?";
			//메세지 박스 호출
			TaskDialogIndirect(&TDBOX, &result, NULL, NULL);
			//메세지 박스에서 눌린 버튼처리
			switch (result) {
			case IDOK:
				save(hWnd);
				break;
			case IDNO:
				CANCEL = 0;
				break;
			case IDCANCEL:
				CANCEL = 1;
				break;
			}
		}
		else {
			CANCEL = 0; //Edit윈도우에 아무것도 적히지않은 경우
		}
	}
	else { //현재 낙서장의 제목타이틀이 제목 없음이 아닐경우
		if (str_CHANGE == 1) {  //문자열이 변경된 경우
			multibyte_len = lstrlen(FILEPATH);
			MessageStr = (TCHAR*)malloc(sizeof(multibyte_len + 19));
			memset(MessageStr, 0, sizeof(TCHAR) * (multibyte_len + 19));
			wsprintf(MessageStr, L"변경 내용을 %s에 저장 하시겠습니까?", FILEPATH);
			TDBOX.pszMainInstruction = MessageStr;

			TaskDialogIndirect(&TDBOX, &result, NULL, NULL);
			switch (result) {
			case IDOK:
				save(hWnd);
				break;
			case IDNO:
				CANCEL = 0; 
				break;
			case IDCANCEL:
				CANCEL = 1; 
				break;
			}
			free(MessageStr);
		}
	}

}

//메인윈도우 클래스 등록
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow) {

	Global_hInstance = hInstance; //핸들을 전역변수로 설정

	WNDCLASS wc;
	wchar_t my_class_name[] = L"GraffitiPad";
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
	HWND hWnd = CreateWindow(my_class_name, L"제목 없음 - 낙서장",
		//NULL NULL hInstance NULL 의 의미는
		//부모윈도우핸들, 윈도우에서 사용할 메뉴의핸들, 현재윈도우핸들, 각윈도우의고유의파라미터
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
