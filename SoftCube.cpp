//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("MainUnit.cpp", MainForm);
USEFORM("NewOrdUnit.cpp", NewOrdForm);
USEFORM("OrdEditUnit.cpp", OrdEditForm);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->Title = "SoftCube by Pit-aka-Mishka";
		Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->CreateForm(__classid(TNewOrdForm), &NewOrdForm);
		Application->CreateForm(__classid(TOrdEditForm), &OrdEditForm);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
