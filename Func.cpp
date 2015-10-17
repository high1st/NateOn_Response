#include "Func.h"


SearchWindow *sw = new SearchWindow();

bool FuncDialog::SearchDialog(){

	FuncDialog::hWnd = sw->FindWindowTitleContains("´Ô ¸Þ½ÃÁö");

	if(hWnd)
		return true;
	else
		return false;
}

void FuncDialog::SendMsg(char *msg){

	FuncDialog::EdithWnd = ::FindWindowExA(hWnd, NULL, "RICHEDIT50W", NULL);
	FuncDialog::EdithWnd = ::FindWindowExA(hWnd,  EdithWnd, "RICHEDIT50W", NULL);
	::SendMessageA(FuncDialog::EdithWnd, WM_SETTEXT, 0, (LPARAM)msg);
	::SendMessage(FuncDialog::EdithWnd, WM_KEYDOWN, VK_RETURN, 0);
	::SendMessage(FuncDialog::EdithWnd, WM_KEYUP,  VK_RETURN, 0);
}

void FuncDialog::ExitDialog(){
	::SendMessageA(FuncDialog::hWnd, WM_CLOSE, 0, 0);
}