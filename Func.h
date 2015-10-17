#include "SearchWindow.h"

class FuncDialog{
public:
	bool FuncDialog::SearchDialog();
	void FuncDialog::SendMsg(char *msg);
	void FuncDialog::ExitDialog();

	FuncDialog() {
		hWnd = NULL; EdithWnd = NULL;
	}

	~FuncDialog() {
		delete hWnd;
		delete EdithWnd;
		hWnd = NULL; EdithWnd = NULL;
	}

private:
	HWND hWnd;
	HWND EdithWnd;


};