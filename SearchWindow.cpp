#include "SearchWindow.h"

BOOL WINAPI StruEnumProc( HWND hwnd, SearchWindow::result_stru* stru )
{
    char loc_buf[128];
    stru->GET( hwnd, loc_buf, 127 );
    if( strstr( loc_buf, stru->text ) ) {
        stru->hRet = hwnd;
        return FALSE;
    }
    return TRUE;
}

HWND SearchWindow::FindWindowTitleContains( char* text )
{
    SearchWindow::result_stru res = { text, (UINT (__stdcall *)(HWND,LPSTR,UINT))GetWindowTextA, 0 };
    EnumWindows( (WNDENUMPROC)StruEnumProc, (LPARAM)&res );
    return res.hRet;
}

HWND SearchWindow::FindWindowClassContains( char* text )
{
    SearchWindow::result_stru res = { text, RealGetWindowClassA, 0 };
    EnumWindows( (WNDENUMPROC)StruEnumProc, (LPARAM)&res );
    return res.hRet;
}