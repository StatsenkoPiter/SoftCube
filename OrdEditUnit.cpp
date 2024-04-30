//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "OrdEditUnit.h"
#include "MainUnit.h"
#include "NewOrdUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "frxClass"
#pragma link "frxPreview"
#pragma link "frxRich"
#pragma link "frxClass"
#pragma resource "*.dfm"
TOrdEditForm *OrdEditForm;
//---------------------------------------------------------------------------
__fastcall TOrdEditForm::TOrdEditForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------- ������������� -------------------------------
void __fastcall TOrdEditForm::FormActivate(TObject *Sender)
{
// �������������� ��������� ���������� ����������
ChMainData=ChWorkData=false;
MainDataOK=OwnNameOK=OwnTelOK=DevModelOK=DevIDOK=DevDefectOK=DevRemOK=true;
// �������������� ����������� ������
OwnNameEdit->Font->Color=clWindowText;
OwnTelEdit->Font->Color=clWindowText;
DevIDEdit->Font->Color=clWindowText;
DevModelEdit->Font->Color=clWindowText;
DevDefectEdit->Font->Color=clWindowText;
DevRemEdit->Font->Color=clWindowText;
// ������ ������ ������ �� ����
bool NoWar;
TempQuery->SQL->Text="SELECT * FROM OrdersTab WHERE OrdNum="+IntToStr(OrigOrdNum);
TempQuery->Open();
OrigDevModel=	TempQuery->Fields->FieldByName("DevModel")->AsString;
OrigDevID=		TempQuery->Fields->FieldByName("DevID")->AsString;
OrigDevDefect=	TempQuery->Fields->FieldByName("DevDefect")->AsString;
OrigDevRem=		TempQuery->Fields->FieldByName("DevRem")->AsString;
OrigDevStatus=	TempQuery->Fields->FieldByName("DevStatus")->AsInteger;
OrigItsWar=		TempQuery->Fields->FieldByName("ItsWar")->AsBoolean;
OrigDevResult=	TempQuery->Fields->FieldByName("DevResult")->AsString;
OrigItsNotif=	TempQuery->Fields->FieldByName("ItsNotif")->AsBoolean;
OrigOwnName=	TempQuery->Fields->FieldByName("OwnName")->AsString;
OrigOwnTel=		TempQuery->Fields->FieldByName("OwnTel")->AsString;
OrigMaxPrice=	TempQuery->Fields->FieldByName("MaxPrice")->AsInteger;
OrigWorkPrice=	TempQuery->Fields->FieldByName("WorkPrice")->AsInteger;
CurDateIn=		TempQuery->Fields->FieldByName("DateIn")->AsDateTime;
CurDateOut=		TempQuery->Fields->FieldByName("DateOut")->AsDateTime;
OrigWar=		!TempQuery->Fields->FieldByName("DateWar")->IsNull;
if (OrigWar)
	OrigDateWar=TempQuery->Fields->FieldByName("DateWar")->AsDateTime;
else
	OrigDateWar=Date();
TempQuery->Close();
// ���������� ������
OwnNameEdit->Text=OrigOwnName;
OwnTelEdit->Text=OrigOwnTel;
DevModelEdit->Text=OrigDevModel;
DevIDEdit->Text=OrigDevID;
DevDefectEdit->Text=OrigDevDefect;
DevRemEdit->Text=OrigDevRem;
if (OrigWorkPrice>0)
	WorkPriceEdit->Text=IntToStr(OrigWorkPrice);
else
	WorkPriceEdit->Text="";
DevResultEdit->Text=OrigDevResult;
DateWarEdit->Date=OrigDateWar;
if (OrigWar)
	DateWarEdit->MinDate=CurDateIn;
else
	DateWarEdit->MinDate=OrigDateWar;
WarCheckBox->Checked=OrigWar;
// ����������� ��������� � ������� �����������
CurOrdNum=OrigOrdNum;
CurDevStatus=OrigDevStatus;
CurMaxPrice=OrigMaxPrice;
CurItsWar=OrigItsWar;
StatusChange();
DataChange();
// ����� �� ������ ����� ������ ����
if (GroupBox2->Enabled) DevResultEdit->SetFocus();
}

//----------------------- ���������� ������� ������ -------------------------
void __fastcall TOrdEditForm::StatusChange() //���������� ���������(�������)
{
// ������������ ���������
int x,y;
TRect rc;
TSize sz1, sz2;
String s1, s2;
s1="����� � "+IntToStr(CurOrdNum)+" �� "+DateToStr(CurDateIn);
if (CurItsWar) s1+=" (�����������)";
TempQuery->SQL->Text="SELECT StatusLong FROM StatusTab WHERE StatusKey="+
IntToStr(CurDevStatus);
TempQuery->Open();
s2=TempQuery->Fields->Fields[0]->AsString;
if (CurDevStatus>7) s2=s2+" "+DateToStr(CurDateOut);
TempQuery->Close();
switch (CurDevStatus)
	{
	case 0: TitleImage->Canvas->Font->Color=0x000000FF; break;
	case 1: TitleImage->Canvas->Font->Color=0x00FF00FF; break;
	case 2: TitleImage->Canvas->Font->Color=0x000080FF; break;
	case 3: TitleImage->Canvas->Font->Color=0x00000080; break;
	case 4: TitleImage->Canvas->Font->Color=0x00408000; break;
	case 5: TitleImage->Canvas->Font->Color=0x00FF9900; break;
	case 6: TitleImage->Canvas->Font->Color=0x00FF0080; break;
	case 7: TitleImage->Canvas->Font->Color=0x00FF0000; break;
	case 8: TitleImage->Canvas->Font->Color=0x00408000; break;
	case 9: TitleImage->Canvas->Font->Color=0x00FF0080; break;
	case 10: TitleImage->Canvas->Font->Color=0x00FF0000; break;
	}
rc.Left=0; rc.Right=TitleImage->Width;
rc.Top=0;  rc.Bottom=TitleImage->Height;
TitleImage->Canvas->Brush->Color=0x00DDDDDD;
TitleImage->Canvas->FillRect(rc);
TitleImage->Canvas->Font->Size=16; sz1=TitleImage->Canvas->TextExtent(s1);
TitleImage->Canvas->Font->Size=10; sz2=TitleImage->Canvas->TextExtent(s2);
x=(TitleImage->Width-sz1.Width)/2;
y=(TitleImage->Height-sz1.Height-sz2.Height-4)/2;
TitleImage->Canvas->Font->Size=16; TitleImage->Canvas->TextOutW(x,y,s1);
x=(TitleImage->Width-sz2.Width)/2;
y=y+sz1.Height+4;
TitleImage->Canvas->Font->Size=10; TitleImage->Canvas->TextOutW(x,y,s2);
}

//------------------------���������� ������ ������---------------------------
void __fastcall TOrdEditForm::DataChange()
{
ChWorkData=(DevResultEdit->Text!=OrigDevResult || CurDevStatus!=OrigDevStatus
			|| DateWarEdit->Date!=OrigDateWar || WarCheckBox->Checked!=OrigWar);
PrintButton->Enabled=!(ChWorkData || ChMainData);
DateWarEdit->Enabled=WarCheckBox->Checked;
while (true)
{
if (CurDevStatus==0)   //�����������
	{
	GroupBox1->Enabled=true;
	GroupBox2->Enabled=true;
	PrintMenu->Items->Items[1]->Enabled=false;
	AgreeButton->Enabled=false;
	ReadyButton->Enabled=false;
	ImpassButton->Enabled=(DevResultEdit->Text!="" && WorkPriceEdit->Text=="");
	NotNeedButton->Enabled=(DevResultEdit->Text=="" && WorkPriceEdit->Text=="");
	GiveButton->Enabled=false;
	GetButton->Enabled=false;
	GetWarButton->Enabled=false;

	WarCheckBox->Visible=false;
	DateWarEdit->Visible=false;

	if (DevResultEdit->Text!="" && WorkPriceEdit->Text!="")
		{
		CurDevStatus=3;
		StatusChange();
		continue;
		}
	break;
	}

if (CurDevStatus==1) // ������������
	{
    GroupBox1->Enabled=true;
	GroupBox2->Enabled=true;
	PrintMenu->Items->Items[1]->Enabled=false;
	AgreeButton->Enabled=true;
	ReadyButton->Enabled=false;
	ImpassButton->Enabled=false;
	NotNeedButton->Enabled=false;
	GiveButton->Enabled=false;
    GetButton->Enabled=false;
	GetWarButton->Enabled=false;

	WarCheckBox->Visible=true;
	DateWarEdit->Visible=true;

	if (DevResultEdit->Text=="" || WorkPriceEdit->Text=="")
		{
		CurDevStatus=0;
		StatusChange();
		continue;
		}
	else
		if(StrToInt(WorkPriceEdit->Text)<=CurMaxPrice)
			{
			CurDevStatus=3;
			StatusChange();
			continue;
			}
	break;
	}


if (CurDevStatus==3) // ���� ������
	{
    GroupBox1->Enabled=true;
	GroupBox2->Enabled=true;
	PrintMenu->Items->Items[1]->Enabled=false;
	AgreeButton->Enabled=false;
	ReadyButton->Enabled=true;
	ImpassButton->Enabled=false;
	NotNeedButton->Enabled=false;
	GiveButton->Enabled=false;
    GetButton->Enabled=false;
	GetWarButton->Enabled=false;

	WarCheckBox->Visible=true;
	DateWarEdit->Visible=true;

	if (DevResultEdit->Text=="" || WorkPriceEdit->Text=="")
		{
		CurDevStatus=0;
		StatusChange();
		continue;
		}
	else
		if(StrToInt(WorkPriceEdit->Text)>CurMaxPrice)
			{
			CurDevStatus=1;
			StatusChange();
			continue;
			}
	break;
	}

if (CurDevStatus==4) // �����
	{
    GroupBox1->Enabled=true;
	GroupBox2->Enabled=true;
	PrintMenu->Items->Items[1]->Enabled=false;
	AgreeButton->Enabled=false;
	ReadyButton->Enabled=false;
	ImpassButton->Enabled=false;
	NotNeedButton->Enabled=false;
	GiveButton->Enabled=true;
    GetButton->Enabled=false;
	GetWarButton->Enabled=false;

	WarCheckBox->Visible=true;
	DateWarEdit->Visible=true;

	if (DevResultEdit->Text=="" || WorkPriceEdit->Text=="")
		{
		CurDevStatus=0;
		StatusChange();
		continue;
		}
    else
		if(StrToInt(WorkPriceEdit->Text)>CurMaxPrice)
			{
			CurDevStatus=1;
			StatusChange();
			continue;
			}
	break;
	}

if (CurDevStatus==6) // �����
	{
    GroupBox1->Enabled=true;
	GroupBox2->Enabled=true;
	PrintMenu->Items->Items[1]->Enabled=false;
	AgreeButton->Enabled=false;
	ReadyButton->Enabled=false;
	ImpassButton->Enabled=false;
	NotNeedButton->Enabled=false;
	GiveButton->Enabled=true;
    GetButton->Enabled=false;
	GetWarButton->Enabled=false;

	WarCheckBox->Visible=false;
	DateWarEdit->Visible=false;

	if (DevResultEdit->Text!="")
		{
		CurDevStatus=0;
		StatusChange();
		continue;
		}
	break;
	}

if (CurDevStatus==7) // �������
	{
    GroupBox1->Enabled=true;
	GroupBox2->Enabled=true;
	PrintMenu->Items->Items[1]->Enabled=false;
	AgreeButton->Enabled=false;
	ReadyButton->Enabled=false;
	ImpassButton->Enabled=false;
	NotNeedButton->Enabled=false;
	GiveButton->Enabled=true;
	GetButton->Enabled=false;
	GetWarButton->Enabled=false;

	WarCheckBox->Visible=false;
	DateWarEdit->Visible=false;

	if (DevResultEdit->Text=="")
		{
		CurDevStatus=0;
		StatusChange();
		continue;
		}
	break;
	}

if (CurDevStatus==8) // �����:�����
	{
	GroupBox1->Enabled=false;
	GroupBox2->Enabled=false;
	PrintMenu->Items->Items[1]->Enabled=true;
	AgreeButton->Enabled=false;
	ReadyButton->Enabled=false;
	ImpassButton->Enabled=false;
	NotNeedButton->Enabled=false;
	GiveButton->Enabled=false;
	GetButton->Enabled=true;
	GetWarButton->Enabled=true;

	WarCheckBox->Visible=false;
	DateWarEdit->Visible=false;

	break;
	}

if (CurDevStatus==9) // �����:�����
	{
    GroupBox1->Enabled=false;
	GroupBox2->Enabled=false;
	PrintMenu->Items->Items[1]->Enabled=true;
	AgreeButton->Enabled=false;
	ReadyButton->Enabled=false;
	ImpassButton->Enabled=false;
	NotNeedButton->Enabled=false;
	GiveButton->Enabled=false;
    GetButton->Enabled=true;
	GetWarButton->Enabled=true;

	WarCheckBox->Visible=false;
	DateWarEdit->Visible=false;

	break;
	}

if (CurDevStatus==10) // �����:�������
	{
    GroupBox1->Enabled=false;
	GroupBox2->Enabled=false;
	PrintMenu->Items->Items[1]->Enabled=true;
    AgreeButton->Enabled=false;
	ReadyButton->Enabled=false;
	ImpassButton->Enabled=false;
	NotNeedButton->Enabled=false;
	GiveButton->Enabled=false;
    GetButton->Enabled=true;
	GetWarButton->Enabled=true;

	WarCheckBox->Visible=false;
	DateWarEdit->Visible=false;

	break;
	}

if (CurDevStatus==2)  // ���� ������
	{
	break;
	}
if (CurDevStatus==5) // �������
	{
	break;
	}
}

}

//----------------------- ������ ���������� � ������ ------------------------
void __fastcall TOrdEditForm::N1Click(TObject *Sender)
{
// ���������� ����� � ������
NewOrdForm->NewOrdReport->ReportOptions->Name="����� � "+IntToStr(CurOrdNum)+
" - ��������� � ������ � ������";
NewOrdForm->NewOrdReport->Script->Clear();
NewOrdForm->NewOrdReport->Script->Variables["Title"]=
"����� � "+IntToStr(OrigOrdNum)+" �� "+DateToStr(CurDateIn);
NewOrdForm->NewOrdReport->Script->Variables["OwnName"]=
	NewOrdForm->OwnNamePrintFormat(OrigOwnName) ;
NewOrdForm->NewOrdReport->Script->Variables["OwnTel"]=OrigOwnTel;
NewOrdForm->NewOrdReport->Script->Variables["DevModel"]=OrigDevModel;
NewOrdForm->NewOrdReport->Script->Variables["DevID"]=OrigDevID;
NewOrdForm->NewOrdReport->Script->Variables["DevDefect"]=OrigDevDefect;
NewOrdForm->NewOrdReport->Script->Variables["DevRem"]=OrigDevRem;
NewOrdForm->NewOrdReport->ShowReport(true);
}
//-------------------- ������ ���������� � ������ ---------------------------

void __fastcall TOrdEditForm::N2Click(TObject *Sender)
{
switch (CurDevStatus)
{
case 8: // �����: �����
	{
	ReadyReport->ReportOptions->Name="����� � "+IntToStr(CurOrdNum)+
	" - ��������� � �������";
	ReadyReport->Script->Clear();
	ReadyReport->Script->Variables["Title"]=
	"����� � "+IntToStr(CurOrdNum)+" �� "+DateToStr(CurDateIn);
	ReadyReport->Script->Variables["OwnName"]=
	NewOrdForm->OwnNamePrintFormat(OwnNameEdit->Text);
	ReadyReport->Script->Variables["OwnTel"]=		OwnTelEdit->Text;
	ReadyReport->Script->Variables["DevModel"]=		DevModelEdit->Text;
	ReadyReport->Script->Variables["DevID"]=		DevIDEdit->Text;
	ReadyReport->Script->Variables["DevDefect"]=	DevDefectEdit->Text;
	ReadyReport->Script->Variables["DevRem"]=		DevRemEdit->Text;
	ReadyReport->Script->Variables["DevResult"]=	DevResultEdit->Text;
	ReadyReport->Script->Variables["WorkPrice"]=	WorkPriceEdit->Text+" ���.";
	ReadyReport->Script->Variables["DateOut"]=		CurDateOut;
	ReadyReport->Script->Variables["DateWar"]=		DateWarEdit->Date;
	ReadyReport->ShowReport(true);
	break;
	}
case 9: // ����� �������
	{
	NotNeedReport->ReportOptions->Name="����� � "+IntToStr(CurOrdNum)+
	" - ��������� �� ������ ���������";
	NotNeedReport->Script->Clear();
	NotNeedReport->Script->Variables["Title"]=
	"����� � "+IntToStr(CurOrdNum)+" �� "+DateToStr(CurDateIn);
	NotNeedReport->Script->Variables["OwnName"]=
	NewOrdForm->OwnNamePrintFormat(OwnNameEdit->Text);
	NotNeedReport->Script->Variables["OwnTel"]=		OwnTelEdit->Text;
	NotNeedReport->Script->Variables["DevModel"]=	DevModelEdit->Text;
	NotNeedReport->Script->Variables["DevID"]=		DevIDEdit->Text;
	NotNeedReport->Script->Variables["DevDefect"]=	DevDefectEdit->Text;
	NotNeedReport->Script->Variables["DevRem"]=		DevRemEdit->Text;
	NotNeedReport->Script->Variables["DateOut"]=	CurDateOut;
	NotNeedReport->ShowReport(true);
	break;
	}
case 10: // ����� ��
	{
	ImpassReport->ReportOptions->Name="����� � "+IntToStr(CurOrdNum)+
	" - ��������� �� ������ �����������";
	ImpassReport->Script->Clear();
	ImpassReport->Script->Variables["Title"]=
	"����� � "+IntToStr(CurOrdNum)+" �� "+DateToStr(CurDateIn);
	ImpassReport->Script->Variables["OwnName"]=
	NewOrdForm->OwnNamePrintFormat(OwnNameEdit->Text);
	ImpassReport->Script->Variables["OwnTel"]=		OwnTelEdit->Text;
	ImpassReport->Script->Variables["DevModel"]=	DevModelEdit->Text;
	ImpassReport->Script->Variables["DevID"]=		DevIDEdit->Text;
	ImpassReport->Script->Variables["DevDefect"]=	DevDefectEdit->Text;
	ImpassReport->Script->Variables["DevRem"]=		DevRemEdit->Text;
	ImpassReport->Script->Variables["DevResult"]=	DevResultEdit->Text;
	ImpassReport->Script->Variables["DateOut"]=		CurDateOut;
	ImpassReport->ShowReport(true);
	break;
	}
}
}

//--------------------- ���������� ���� ������� -----------------------------
void __fastcall TOrdEditForm::WorkPriceEditKeyPress(TObject *Sender,
System::WideChar &Key)
{
// ������ ����� � ����������� �������
if ((Key>31)&&(Key<48||Key>57) || Key==13 || DevResultEdit->Text=="") Key=0;
}

//-------------------- ���������� �������� ������ ---------------------------
void __fastcall TOrdEditForm::DevResultEditChange(TObject *Sender)
{
if (DevResultEdit->Text=="") WorkPriceEdit->Text="";
DataChange();
}

//---------------------- ��������� ���� ������ ------------------------------
void __fastcall TOrdEditForm::WorkPriceEditChange(TObject *Sender)
{
DataChange();
}


//***************************** ������ **************************************
//------------------------ ������ ������ ����� ------------------------------
void __fastcall TOrdEditForm::ReadyButtonClick(TObject *Sender)
{
CurDevStatus=4;
StatusChange();
DataChange();
}
//------------------------ ������ ������ �� ����� ---------------------------
void __fastcall TOrdEditForm::NotNeedButtonClick(TObject *Sender)
{
DevResultEdit->Clear(); WorkPriceEdit->Clear();
CurDevStatus=6;
StatusChange();
DataChange();
}
//------------------------ ������ ������ ���������� -------------------------
void __fastcall TOrdEditForm::ImpassButtonClick(TObject *Sender)
{
CurDevStatus=7;
StatusChange();
DataChange();
}
//------------------------ ������ ���������� --------------------------------
void __fastcall TOrdEditForm::AgreeButtonClick(TObject *Sender)
{
CurMaxPrice=StrToInt(WorkPriceEdit->Text);
CurDevStatus=3;
StatusChange();
DataChange();
}
//---------------------------- ������� �������� -----------------------------
void __fastcall TOrdEditForm::WarCheckBoxClick(TObject *Sender)
{
DataChange();
}
// ---------------------- ��������� ���� �������� ---------------------------
void __fastcall TOrdEditForm::DateWarEditChange(TObject *Sender)
{
DataChange();
}


// ------------------------- ������ ������ ----------------------------------
void __fastcall TOrdEditForm::GiveButtonClick(TObject *Sender)
{
if(MainDataOK) // ��������� �� ������
	{
	// ������������� �� ��������� � ������
	int i=0;
	if (ChMainData || ChWorkData)
		{
		i=Application->MessageBox
		(L"��������� ��������� � ������ �����?",
		L"�������������", MB_OKCANCEL + MB_ICONWARNING);
		if (i==2)
			return;
		else
			SaveOrder();
		}
	if (i==0)
		if (Application->MessageBox
		(L"������ ������ �����?", L"�������������",
		MB_OKCANCEL + MB_ICONQUESTION)==IDCANCEL) return;
	// ******************* ������ ������ ********************************
	// ��������� ������� � ���� ������
	CurDateOut=Date();
	i=CurDevStatus;
	switch(i)
		{
		case 4: CurDevStatus=8; break;
		case 6: CurDevStatus=9; break;
		case 7: CurDevStatus=10; break;
		}
	TempQuery->SQL->Text=
	"UPDATE OrdersTab SET DevStatus=:p1, ItsWar=:p2, DateOut=:p3, DateWar=:p4 \
	WHERE OrdNum="+IntToStr(CurOrdNum);
	TempQuery->Parameters->ParseSQL(TempQuery->SQL->Text,true);
	TempQuery->Parameters->ParamByName("p1")->Value= CurDevStatus;
	TempQuery->Parameters->ParamByName("p2")->Value= false;
	TempQuery->Parameters->ParamByName("p3")->Value= CurDateOut;
	TempQuery->Parameters->ParamByName("p4")->Value= DateWarEdit->Date;
	TempQuery->ExecSQL();
	TempQuery->Close();
	// ���������� � ����� ������
	N2Click(Sender);
	// �������� �����
	OrdEditForm->Close();
	}
else
	Application->MessageBox
	(L"� �������� ������ ������ ���� ������.\n������ ������ ����������.",
	L"������ � ������", MB_OK + MB_ICONERROR);
}
//------------------------ ������ ������� ------------------------------------
void __fastcall TOrdEditForm::GetButtonClick(TObject *Sender)
{
NewOrdForm->OwnNameEdit->Text=OwnNameEdit->Text;
NewOrdForm->OwnTelEdit->Text=OwnTelEdit->Text;
NewOrdForm->DevModelEdit->Text=DevModelEdit->Text;
NewOrdForm->DevIDEdit->Text=DevIDEdit->Text;
NewOrdForm->DevDefectEdit->Text=DevDefectEdit->Text;
NewOrdForm->MaxPriceEdit->Text=IntToStr(CurMaxPrice);
NewOrdForm->DevRemEdit->Text=DevRemEdit->Text;
OrdEditForm->Close();
NewOrdForm->CleanStart=false;
NewOrdForm->ShowModal();
}

//------------------------ ������ �������� -----------------------------------
void __fastcall TOrdEditForm::GetWarButtonClick(TObject *Sender)
{
if	(Application->MessageBox(
	L"������� ������� ����� �� ��������?",
	L"��������", MB_OKCANCEL + MB_ICONWARNING)==IDOK)
	{
	TempQuery->SQL->Text=
	("UPDATE OrdersTab SET DevStatus=:p1, ItsWar=:p2 \
	WHERE OrdNum="+IntToStr(CurOrdNum));
	TempQuery->Parameters->ParseSQL(TempQuery->SQL->Text,true);
	TempQuery->Parameters->ParamByName("p1")->Value= 0;
	TempQuery->Parameters->ParamByName("p2")->Value= true;
	TempQuery->ExecSQL();
	TempQuery->Close();
	OrdEditForm->Close();
	}
}

//--------------------- ������ ������� ������ � ���� -------------------------
void __fastcall TOrdEditForm::SaveOrder()
{
TempQuery->SQL->Text=
"UPDATE OrdersTab SET \
DevModel=:p1, DevID=:p2, DevDefect=:p3, DevRem=:p4, \
DevStatus=:p5, DevResult=:p6, OwnName=:p7, OwnTel=:p8, \
MaxPrice=:p9, WorkPrice=:p10, DateWar=:p11 \
WHERE OrdNum="+IntToStr(CurOrdNum);
TempQuery->Parameters->ParseSQL(TempQuery->SQL->Text,true);
TempQuery->Parameters->ParamByName("p1")->Value= DevModelEdit->Text;
TempQuery->Parameters->ParamByName("p2")->Value= DevIDEdit->Text;
TempQuery->Parameters->ParamByName("p3")->Value= DevDefectEdit->Text;
TempQuery->Parameters->ParamByName("p4")->Value= DevRemEdit->Text;
TempQuery->Parameters->ParamByName("p5")->Value= CurDevStatus;
TempQuery->Parameters->ParamByName("p6")->Value= DevResultEdit->Text;
TempQuery->Parameters->ParamByName("p7")->Value= OwnNameEdit->Text;
TempQuery->Parameters->ParamByName("p8")->Value= OwnTelEdit->Text;
TempQuery->Parameters->ParamByName("p9")->Value= CurMaxPrice;
if (WorkPriceEdit->Text == "")
	TempQuery->Parameters->ParamByName("p10")->Value=0;
else
	TempQuery->Parameters->ParamByName("p10")->Value=WorkPriceEdit->Text;
TempQuery->Parameters->ParamByName("p11")->Value=DateWarEdit->Date;
TempQuery->ExecSQL();
TempQuery->Close();
if (!WarCheckBox->Checked || CurDevStatus>4) // ������� ���� ��������
	{
	TempQuery->SQL->Text="SELECT * FROM OrdersTab WHERE OrdNum="+
	IntToStr(CurOrdNum);
	TempQuery->Open();
	TempQuery->Edit();
	TempQuery->Fields->FieldByName("DateWar")->Clear();
	TempQuery->Post();
	TempQuery->Close();
	}
}

//--------------------- ������ �� �������� ����� ----------------------------
void __fastcall TOrdEditForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
if (CurDevStatus>7)  //��� ������������ ��� ��������
	{
    MainForm->OrdersTab->Active=false;
	MainForm->OrdersTab->Active=true;
	return;
	}
if (ChMainData || ChWorkData)
	if (MainDataOK)
		{
		int i;
		i = Application->MessageBox
		(L"������ ������ ���� �������.\n��������� ��������� � ������� ������?",
			L"������������� ���������", MB_YESNOCANCEL + MB_ICONWARNING);
		if(i==6) // yes
			{
			SaveOrder();
			//ChMainData=ChWorkData=false;
			MainForm->OrdersTab->Active=false;
			MainForm->OrdersTab->Active=true;
			}
		if(i==2) CanClose=false; // cancel
		}
	else
		{
		if (Application->MessageBox
		(L"� �������� ������ ������ ���� ������.\n����� ��� ���������� ������?",
		L"������ � ������", MB_OKCANCEL + MB_ICONERROR)==IDCANCEL) CanClose=false;
		}

}
//---------------------------------------------------------------------------



//------------------ �������� ������������ �������� ������ -------------------
void __fastcall TOrdEditForm::AnyEditExit(TObject *Sender)
{
String s;
int i;
bool ok;
s=((TEdit* )Sender)->Text;
i=((TEdit* )Sender)->Tag;
switch (i)
	{
	case 0:	ok = OwnNameOK = NewOrdForm->OwnNameFormat(s); break;
	case 1:	ok = OwnTelOK = NewOrdForm->OwnTelFormat(s); break;
	case 2:	ok = DevIDOK = NewOrdForm->DevIDFormat(s); break;
	case 3:	ok = DevModelOK = NewOrdForm->DevModelFormat(s); break;
	case 4:	ok = DevDefectOK = NewOrdForm->DevDefectFormat(s); break;
	case 5:	ok = DevRemOK = true; break;
	}
((TEdit* )Sender)->Text=s;
if (!ok) ((TEdit* )Sender)->Font->Color=clRed;
ChMainData=(OwnNameEdit->Text!=OrigOwnName)||(OwnTelEdit->Text!=OrigOwnTel)||
		(DevIDEdit->Text!=OrigDevID)||(DevModelEdit->Text!=OrigDevModel)||
		(DevDefectEdit->Text!=OrigDevDefect)||(DevRemEdit->Text!=OrigDevRem);
MainDataOK =
OwnNameOK && OwnTelOK && DevModelOK && DevIDOK && DevDefectOK && DevRemOK;
PrintButton->Enabled=!(ChWorkData || ChMainData);
}
//------------------ ������� ����� ������ �� �������� -----------------------
void __fastcall TOrdEditForm::AnyEditKeyDown(TObject *Sender, WORD &Key,
TShiftState Shift)
{
int i;
i=((TEdit* )Sender)->Tag;
if (Key==38)
	switch(i)
		{
		case 1: OwnNameEdit->SetFocus(); break;
		case 2: OwnTelEdit->SetFocus(); break;
		case 3: DevIDEdit->SetFocus(); break;
		case 4: DevModelEdit->SetFocus(); break;
		case 5: DevDefectEdit->SetFocus(); break;
		}
if (Key==40)
	switch(i)
		{
		case 0: OwnTelEdit->SetFocus(); break;
		case 1: DevIDEdit->SetFocus(); break;
		case 2: DevModelEdit->SetFocus(); break;
		case 3: DevDefectEdit->SetFocus(); break;
		case 4: DevRemEdit->SetFocus(); break;
		}
}
//--------------------- ������� ����� ������ �� ENTER ------------------------
void __fastcall TOrdEditForm::AnyEditKeyPress(TObject *Sender,
System::WideChar &Key)

{
int i;
i=((TEdit* )Sender)->Tag;
if (Key==13)
	{
	Key=0;
	switch(i)
		{
		case 0: OwnTelEdit->SetFocus(); break;
		case 1: DevIDEdit->SetFocus(); break;
		case 2: DevModelEdit->SetFocus(); break;
		case 3: DevDefectEdit->SetFocus(); break;
		case 4: DevRemEdit->SetFocus(); break;
		}
	}
}
//-------- �������������� ������������ ����� � ������ �������������� --------
void __fastcall TOrdEditForm::AnyEditEnter(TObject *Sender)
{
int i;
i=((TEdit* )Sender)->Tag;
switch (i)
	{
	case 0: OwnNameEdit->Font->Color=clWindowText; break;
	case 1: OwnTelEdit->Font->Color=clWindowText;  break;
	case 2: DevIDEdit->Font->Color=clWindowText; break;
	case 3: DevModelEdit->Font->Color=clWindowText; break;
	case 4: DevDefectEdit->Font->Color=clWindowText; break;
	case 5: DevRemEdit->Font->Color=clWindowText; break;
	}
}

//---------------------------------------------------------------------------






