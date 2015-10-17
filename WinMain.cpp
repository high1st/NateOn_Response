#include "Func.h"
#include "resource.h"
//----------------------------------------------------------------------------------------
HWND hWnd;
LRESULT CALLBACK DlgProc(HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam);


char *GetText(HWND hWnd);
HWND hTextBox; char *Content;
/*↓ 쓰레드 변수 ↓*/
DWORD WINAPI ThreadProc(void);
DWORD dwThreadID; HANDLE hThread;
bool isStop = false;
//----------------------------------------------------------------------------------------

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine, int nCmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1),
	          hWnd, reinterpret_cast<DLGPROC>(DlgProc));

	return FALSE;
}

//----------------------------------------------------------------------------------------

LRESULT CALLBACK DlgProc(HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch(Msg)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		switch(wParam)
		{
		case 2: // ControlBox X 버튼 (이거 상수 선언이 어디에 되어있는지 몰라서 그냥 그대로씀)
			EndDialog(hWndDlg, 0);
			return TRUE;

		case IDC_BUTTON1:
			MessageBoxA(hWndDlg, "자동 응답을 시작합니다.", "알림", MB_OK | MB_ICONINFORMATION);
			EnableWindow(GetDlgItem(hWndDlg, IDC_BUTTON1), FALSE);
			EnableWindow(GetDlgItem(hWndDlg, IDC_BUTTON2), TRUE);
			hTextBox = GetDlgItem(hWndDlg, IDC_EDIT1);

			Content = GetText(hTextBox);// IDC_EDIT 내용 가져오기
			hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProc, NULL, 0, &dwThreadID); // 쓰레드 생성
			isStop = false;
			break;
		
		case IDC_BUTTON2:
			MessageBoxA(hWndDlg, "자동 응답을 중지합니다.", "알림", MB_OK | MB_ICONINFORMATION);
			EnableWindow(GetDlgItem(hWndDlg, IDC_BUTTON1), TRUE);
			EnableWindow(GetDlgItem(hWndDlg, IDC_BUTTON2), FALSE);
			GetExitCodeThread(hThread, &dwThreadID);
			bool test = CloseHandle(hThread);
			isStop = true;
			break;

		}

		break;
	}

	return FALSE;
}

char *GetText(HWND hWnd){
	int len = GetWindowTextLength(hWnd);
	if(len > 0){
		int i; char *buf;
		buf = (char*)GlobalAlloc(GPTR, 256);
		GetWindowTextA(hWnd, buf, 256);
		return buf;
	}

	return "ERR_CALL_GETTEXT()";

}

DWORD WINAPI ThreadProc(void){
	FuncDialog *fd = new FuncDialog();
	while(1){
		Sleep(1000);
		if(fd->SearchDialog()){
			fd->SendMsg(Content);
			fd->ExitDialog();
		}

		if(isStop) ExitThread(0);
	}

}