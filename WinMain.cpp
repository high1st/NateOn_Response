#include "Func.h"
#include "resource.h"
//----------------------------------------------------------------------------------------
HWND hWnd;
LRESULT CALLBACK DlgProc(HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam);


char *GetText(HWND hWnd);
HWND hTextBox; char *Content;
/*�� ������ ���� ��*/
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
		case 2: // ControlBox X ��ư (�̰� ��� ������ ��� �Ǿ��ִ��� ���� �׳� �״�ξ�)
			EndDialog(hWndDlg, 0);
			return TRUE;

		case IDC_BUTTON1:
			MessageBoxA(hWndDlg, "�ڵ� ������ �����մϴ�.", "�˸�", MB_OK | MB_ICONINFORMATION);
			EnableWindow(GetDlgItem(hWndDlg, IDC_BUTTON1), FALSE);
			EnableWindow(GetDlgItem(hWndDlg, IDC_BUTTON2), TRUE);
			hTextBox = GetDlgItem(hWndDlg, IDC_EDIT1);

			Content = GetText(hTextBox);// IDC_EDIT ���� ��������
			hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProc, NULL, 0, &dwThreadID); // ������ ����
			isStop = false;
			break;
		
		case IDC_BUTTON2:
			MessageBoxA(hWndDlg, "�ڵ� ������ �����մϴ�.", "�˸�", MB_OK | MB_ICONINFORMATION);
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