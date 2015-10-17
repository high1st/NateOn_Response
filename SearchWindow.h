#include <Windows.h>

class SearchWindow{
public:
	struct result_stru {
		char* text;
		UINT (__stdcall*GET)(HWND,LPSTR,UINT);
		HWND hRet;
	};

	HWND SearchWindow::FindWindowClassContains( char* text );
	HWND SearchWindow::FindWindowTitleContains( char* text );
	
private:

};

