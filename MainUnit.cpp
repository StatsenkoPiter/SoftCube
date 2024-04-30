//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainUnit.h"
#include "NewOrdUnit.h"
#include "OrdEditUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//----------------------- Инифиализация программы ---------------------------
// до визуализации
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
// ---- Чтение настроек из конфигурационного файла ----
TIniFile *CfgFile;
CfgFile = new TIniFile(ExtractFilePath(Application->ExeName)+"Config.ini");
// Чтение пути к БД
WideString  s;
s=CfgFile->ReadString("GENERAL","DBPath","");
MainADOConnection->ConnectionString=
"Provider=Microsoft.Jet.OLEDB.4.0;Password="";User ID=Admin;Data Source="+s+
";Mode=Share Deny None;Persist Security Info=True;Jet OLEDB:System database="";\
Jet OLEDB:Registry Path="";Jet OLEDB:Database Password=123;\
Jet OLEDB:Engine Type=5;Jet OLEDB:Database Locking Mode=1;\
Jet OLEDB:Global Partial Bulk Ops=2;Jet OLEDB:Global Bulk Transactions=1;\
Jet OLEDB:New Database Password="";Jet OLEDB:Create System Database=False;\
Jet OLEDB:Encrypt Database=False;Jet OLEDB:Don't Copy Locale on Compact=False;\
Jet OLEDB:Compact Without Replica Repair=False;Jet OLEDB:SFP=False";
// Чтение визуальных настроек
MainMenu->Items->Items[2]->Items[0]->Checked =
CfgFile->ReadBool("VIEW","ShowAllOrd",false);
CfgFile->Free();
//---- открытие нужных таблиц ----
MainADOConnection->Connected=true;
OrdersTab->Open();
StatusTab->Open();
OrdersTab->Sort="OrdNum";
}
// после визуализации
void __fastcall TMainForm::FormActivate(TObject *Sender)
{
MainDBGrid->Tag=0; //нужно для функции автовыравнивания столбцов
MainDBGrid->SetFocus();
WideChar k=13;
SearchEditKeyPress(Sender, k);
}
//--------------------- Выравнивание ширины столбцов -------------------------
void __fastcall TMainForm::FormResize(TObject *Sender)
{
FixMainGridWidth();
}
void __fastcall TMainForm::FixMainGridWidth()
{
int i,tw,dw;
tw=MainDBGrid->Columns->Count;
for (i = 0; i < MainDBGrid->Columns->Count; i++)
	tw=tw+MainDBGrid->Columns->Items[i]->Width;
dw=(MainDBGrid->ClientWidth-tw)/MainDBGrid->Columns->Count;
for (i = 0; i < MainDBGrid->Columns->Count; i++)
	MainDBGrid->Columns->Items[i]->Width+=dw;
MainDBGrid->Columns->Items[MainDBGrid->Tag]->Width+=
MainDBGrid->ClientWidth-(tw+dw*MainDBGrid->Columns->Count);
MainDBGrid->Tag++;
if (MainDBGrid->Tag == MainDBGrid->Columns->Count) MainDBGrid->Tag=0;
}
//------------------ Сортировка данных в столбцах ---------------------------
void __fastcall TMainForm::MainDBGridTitleClick(TColumn *Column)
{
String s;
s=Column->FieldName;
if (s=="DevStatusStr") s="DevStatus";
if (OrdersTab->Sort==s)
	OrdersTab->Sort= s+" DESC";
else
	OrdersTab->Sort=s;
}
// -------------------------- Новый заказ -----------------------------------
void __fastcall TMainForm::NewOrdButtonClick(TObject *Sender)
{
NewOrdForm->CleanStart=true;
NewOrdForm->ShowModal();
}
//---------------------- Подробности по заказу ------------------------------
void __fastcall TMainForm::MainDBGridDblClick(TObject *Sender)
{
MainStatusBar->SimpleText=IntToStr(MainDBGrid->SelectedField->AsInteger);
OrdEditForm->OrigOrdNum=MainDBGrid->SelectedField->AsInteger;
OrdEditForm->ShowModal();
}
//--------------- Цвет строк в соответствии со статусом ---------------------
void __fastcall TMainForm::MainDBGridDrawColumnCell(TObject *Sender,
const TRect &Rect, int DataCol, TColumn *Column, TGridDrawState State)
{
if (!Column->Field->DataSet->IsEmpty())
	{
	int i;
	i=Column->Field->DataSet->FieldValues["DevStatus"];
	switch (i)
		{
		case 0:  MainDBGrid->Canvas->Font->Color=0x000000FF; break;
		case 1:  MainDBGrid->Canvas->Font->Color=0x00FF00FF; break;
		case 2:  MainDBGrid->Canvas->Font->Color=0x000080FF; break;
		case 3:  MainDBGrid->Canvas->Font->Color=0x00000080; break;
		case 4:  MainDBGrid->Canvas->Font->Color=0x00408000; break;
		case 5:  MainDBGrid->Canvas->Font->Color=0x00FF9900; break;
		case 6:  MainDBGrid->Canvas->Font->Color=0x00FF0080; break;
		case 7:  MainDBGrid->Canvas->Font->Color=0x00FF0000; break;
		case 8:  MainDBGrid->Canvas->Font->Color=0x00408000; break;
		case 9:  MainDBGrid->Canvas->Font->Color=0x00FF0080; break;
		case 10: MainDBGrid->Canvas->Font->Color=0x00FF0000; break;
		}
	if (State.Contains(Grids::gdSelected))
		MainDBGrid->Canvas->Brush->Color=0x00DDDDDD;
	}
MainDBGrid->DefaultDrawColumnCell(Rect, DataCol, Column, State);
}

//---------------------- Дополнение номера заказа --------------------------
void __fastcall TMainForm::OrdersTabOrdNumGetText(TField *Sender,
UnicodeString &Text, bool DisplayText)
{
Text=OrdersTabOrdNum->Value;
if (OrdersTabItsWar->Value) Text=Text+"-Г";
}

//----------------------------- ФИЛЬТРАЦИЯ ---------------------------------
void __fastcall TMainForm::SearchEditKeyPress(TObject *Sender,
System::WideChar &Key)
{
if (Key == 13)
	{
	Key=0;
	if (SearchEdit->Text=="")
		{
		OrdersTab->Filtered=false;
		if(!MainMenu->Items->Items[2]->Items[0]->Checked)
			{
			OrdersTab->Filter="DevStatus < 8";
			OrdersTab->Filtered=true;
			}
		}
	else
		{
		bool d = true;
		int i;
		for (i=1; i<=SearchEdit->Text.Length(); i++)
			if (SearchEdit->Text[i]<48 || SearchEdit->Text[i]>57)
				{d=false; break;}
		if (d)  // ищется число или строка
			{
			OrdersTab->Filtered=false;
			OrdersTab->Filter="OrdNum ="+SearchEdit->Text;
			OrdersTab->Filtered=true;
			}
		else
			{
			OrdersTab->Filtered=false;
			OrdersTab->Filter=
			"(OwnName LIKE '%"+SearchEdit->Text+
			"%') OR (DevModel LIKE '%"+SearchEdit->Text+"%')";
			OrdersTab->Filtered=true;
			}
		}
	}
}
void __fastcall TMainForm::N6Click(TObject *Sender)
{
MainMenu->Items->Items[2]->Items[0]->Checked=
!MainMenu->Items->Items[2]->Items[0]->Checked;
WideChar k=13;
SearchEditKeyPress(Sender, k);
}
//----------------------- Финализация программы -----------------------------
void __fastcall TMainForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
//---- Запись настроей в конфигурационный файл ----
TIniFile *CfgFile;
CfgFile = new TIniFile(ExtractFilePath(Application->ExeName)+"Config.ini");
//сохранение визуальных настроек
CfgFile->WriteBool("VIEW","ShowAllOrd",
MainMenu->Items->Items[2]->Items[0]->Checked);
CfgFile->Free();
StatusTab->Close();
OrdersTab->Close();
MainADOConnection->Connected=false;
}

