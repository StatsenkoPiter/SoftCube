//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainUnit.h"
#include "NewOrdUnit.h"
#include "ReportsUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "frxClass"
#pragma link "frxPreview"
#pragma link "frxRich"
#pragma link "frxClass"
#pragma resource "*.dfm"
TNewOrdForm *NewOrdForm;


//------------------------------- Инициализация -----------------------------
void __fastcall TNewOrdForm::FormActivate(TObject *Sender)
{
TempQuery->SQL->Text="SELECT MAX(OrdNum) FROM OrdersTab";
TempQuery->Open();
NewOrdNum=TempQuery->Fields->Fields[0]->AsInteger+1;
TempQuery->Close();
NewDateIn=Date();
// Формирование заголовка
int x,y;
TRect rc;
TSize sz;
String s;
rc.Left=0; rc.Right=TitleImage->Width;
rc.Top=0;  rc.Bottom=TitleImage->Height;
TitleImage->Canvas->Brush->Color=0x00DDDDDD;
s="Заказ № "+IntToStr(NewOrdNum)+" от "+DateToStr(NewDateIn);
TitleImage->Canvas->Font->Color=0x000000FF;
TitleImage->Canvas->Font->Size=16;
sz=TitleImage->Canvas->TextExtent(s);
x=(TitleImage->Width-sz.Width)/2;
y=(TitleImage->Height-sz.Height)/2;
TitleImage->Canvas->FillRect(rc);
TitleImage->Canvas->TextOutW(x,y,s);
// Очистка вводимых данных
if (CleanStart)
	{
	OwnNameEdit->Clear();   OwnTelEdit->Clear();
	DevModelEdit->Clear();  DevIDEdit->Clear();
	DevDefectEdit->Clear(); DevRemEdit->Clear();
	MaxPriceEdit->Text="500";
	// Установка состояния кнопок
	OwnNameOK = OwnTelOK = DevModelOK = DevIDOK = DevDefectOK = false;
	OKButton->Enabled=false;
	}
else
	{
	OwnNameOK = OwnTelOK = DevModelOK = DevIDOK = DevDefectOK = true;
	OKButton->Enabled=true;
	}
MaxPriceOK = DevRemOK=true;
OwnNameEdit->SetFocus();
}
//---------------------------------------------------------------------------
__fastcall TNewOrdForm::TNewOrdForm(TComponent* Owner)
	: TForm(Owner)
{
}


//---------------------------------------------------------------------------
void __fastcall TNewOrdForm::OKButtonClick(TObject *Sender)
{
// Создание новой записи
if (Application->MessageBox(L"Будет создан новый заказ, продолжить?",
	L"Вопрос", MB_YESNO + MB_ICONQUESTION) == IDYES)
	{
	//передается через параметры потому что формат даты зависит от сервера
	TempQuery->SQL->Text=
	("INSERT INTO OrdersTab \
	(OrdNum,DevModel,DevID,DevDefect,DevRem,DevStatus,\
	OwnName,OwnTel,MaxPrice,DateIn) \
	VALUES (:p1,:p2,:p3,:p4,:p5,:p6,:p7,:p8,:p9,:p10)");
	TempQuery->Parameters->ParseSQL(TempQuery->SQL->Text,true);
	TempQuery->Parameters->ParamByName("p1")->Value=NewOrdNum;
	TempQuery->Parameters->ParamByName("p2")->Value=DevModelEdit->Text;
	TempQuery->Parameters->ParamByName("p3")->Value=DevIDEdit->Text;
	TempQuery->Parameters->ParamByName("p4")->Value=DevDefectEdit->Text;
	TempQuery->Parameters->ParamByName("p5")->Value=DevRemEdit->Text;
	TempQuery->Parameters->ParamByName("p6")->Value=0;
	TempQuery->Parameters->ParamByName("p7")->Value=OwnNameEdit->Text;
	TempQuery->Parameters->ParamByName("p8")->Value=OwnTelEdit->Text;
	TempQuery->Parameters->ParamByName("p9")->Value=MaxPriceEdit->Text;
	TempQuery->Parameters->ParamByName("p10")->Value=NewDateIn;
	TempQuery->ExecSQL();
	TempQuery->Close();
	MainForm->OrdersTab->Active=false;
	MainForm->OrdersTab->Active=true;
	// заполнение полей в отчете
	NewOrdReport->Script->Clear();
	NewOrdReport->ReportOptions->Name="Заказ № "+IntToStr(NewOrdNum)+
	" - Квитанция о приеме в ремонт";
	NewOrdReport->Script->Variables["Title"]=
	"Заказ № "+IntToStr(NewOrdNum)+" от "+DateToStr(NewDateIn);
	NewOrdReport->Script->Variables["OwnName"]=
	OwnNamePrintFormat(OwnNameEdit->Text);
	NewOrdReport->Script->Variables["OwnTel"]=OwnTelEdit->Text;
	NewOrdReport->Script->Variables["DevModel"]=DevModelEdit->Text;
	NewOrdReport->Script->Variables["DevID"]=DevIDEdit->Text;
	NewOrdReport->Script->Variables["DevDefect"]=DevDefectEdit->Text;
	NewOrdReport->Script->Variables["DevRem"]=DevRemEdit->Text;
	NewOrdReport->ShowReport(true);
	WideChar k=13;
	MainForm->SearchEditKeyPress(Sender, k);
	NewOrdForm->Close();
	}
}

//---------------------- Переход между полями по Enter-----------------------
void __fastcall TNewOrdForm::AnyEditKeyPress(TObject *Sender,
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
		case 1: DevModelEdit->SetFocus(); break;
		case 2: DevIDEdit->SetFocus(); break;
		case 3: DevDefectEdit->SetFocus(); break;
		case 4: MaxPriceEdit->SetFocus(); break;
		case 5: DevRemEdit->SetFocus(); break;
		case 6:
			{
			if(OKButton->Enabled)
				OKButton->SetFocus();
			else
				OwnNameEdit->SetFocus();
			break;}
		}
	}
}

//------------------ Переход между полями по стрелкам -----------------------
void __fastcall TNewOrdForm::AnyEditKeyDown(TObject *Sender, WORD &Key,
TShiftState Shift)
{
int i;
i=((TEdit* )Sender)->Tag;
if (Key==38)
	switch(i)
		{
		case 1: OwnNameEdit->SetFocus(); break;
		case 2: OwnTelEdit->SetFocus(); break;
		case 3: DevModelEdit->SetFocus(); break;
		case 4: DevIDEdit->SetFocus(); break;
		case 5: DevDefectEdit->SetFocus(); break;
		case 6: MaxPriceEdit->SetFocus(); break;
		}
if (Key==40)
	switch(i)
		{
		case 0: OwnTelEdit->SetFocus(); break;
		case 1: DevModelEdit->SetFocus(); break;
		case 2: DevIDEdit->SetFocus(); break;
		case 3: DevDefectEdit->SetFocus(); break;
		case 4: MaxPriceEdit->SetFocus(); break;
		case 5: DevRemEdit->SetFocus(); break;
		}
}

//-------- Восстановление стандартного цвета в начале редактирования ---------
void __fastcall TNewOrdForm::AnyEditEnter(TObject *Sender)
{
int i;
i=((TEdit* )Sender)->Tag;
switch (i)
	{
	case 0: OwnNameEdit->Font->Color=clWindowText; break;
	case 1: OwnTelEdit->Font->Color=clWindowText;  break;
	case 2: DevModelEdit->Font->Color=clWindowText; break;
	case 3: DevIDEdit->Font->Color=clWindowText; break;
	case 4: DevDefectEdit->Font->Color=clWindowText; break;
	case 5: MaxPriceEdit->Font->Color=clWindowText; break;
	case 6: DevRemEdit->Font->Color=clWindowText; break;
	}
}

//------------------- Проверка правильности данных ---------------------------
void __fastcall TNewOrdForm::AnyEditExit(TObject *Sender)
{
String s;
int i;
bool ok;
s=((TEdit* )Sender)->Text;
i=((TEdit* )Sender)->Tag;
switch (i)
	{
	case 0: ok = OwnNameOK = OwnNameFormat(s); break;
	case 1: ok = OwnTelOK = OwnTelFormat(s); break;
	case 2: ok = DevModelOK = DevModelFormat(s); break;
	case 3: ok = DevIDOK = DevIDFormat(s);break;
	case 4: ok = DevDefectOK = DevDefectFormat(s); break;
	case 5: ok = MaxPriceOK = MaxPriceFormat(s); break;
	case 6: ok = DevRemOK = true; break;
	}
((TEdit* )Sender)->Text=s;
if (!ok) ((TEdit* )Sender)->Font->Color=clRed;
OKButton->Enabled =
OwnNameOK && OwnTelOK && DevModelOK && DevIDOK &&
DevDefectOK && MaxPriceOK && DevRemOK;
}

//---------------------- Форматирование ФИО --------------------------------
bool __fastcall TNewOrdForm::OwnNameFormat(String &st)
{
int i,fp,fl,ip,op; //первый символ фамили, ее длиа, позиция имени и отчества
String s,t;
s=st.Trim();
if (s[1]=='!' && s.Length()>1) //неформатируемое ФИО
	{
	st=s;
	return true;
	}
s=s.UpperCase();
fl=s.Length();
fp=ip=op=0;
//поиск первого символа фамилии
for (i = 1; i<=s.Length(); i++)
	{
	if (s[i]>1039 && s[i]<1072)   //т.к. UNICODE
		{fp=i; break;}
	}
//поиск длины фамилии
while (i<=s.Length())
	{
	if (s[i]<1040 || s[i]>1071)
		{fl=i-fp; break;}
	i++;
	}
//поиск первого симолв имени
while (i<=s.Length())
	{
	if (s[i]>1039 && s[i]<1072)
		{ip=i; break;}
	i++;
	}
while (i<=s.Length())
	{
	if (s[i]<1040 || s[i]>1071)
		break;
	i++;
	}
//поиск первого символа отчества
while (i<=s.Length())
	{
	if (s[i]>1039 && s[i]<1072)
		{op=i; break;}
	i++;
	}
// Сборка ФИО
if  (fp>0)                          //найдена фамилия
	{
	t=s.SubString(fp,fl);
	i=2;
	while (i<=t.Length())
		{
		t[i]=t[i]+32;
		i++;
		}
	if (op>0)                       //найдено имя и отчество
		{
		t=t+" ";
		t=t+s.SubString(ip,1)+".";
		t=t+s.SubString(op,1)+".";
		}
	st=t;
	return true;
	}
else
	{
	return false;
	}
}
// Подготовка неформатируемого ФИО для печати
String __fastcall TNewOrdForm::OwnNamePrintFormat(String st)
{
if (st[1]=='!')
	return st.SubString(2,st.Length()-1);
else
    return st;
}

//---------------------- Форматирование телефона ----------------------------
bool __fastcall TNewOrdForm::OwnTelFormat(String &st)
{
int i;
String s;
st=st.Trim();
if (st=="") return true;
for (i = 1; i<=st.Length(); i++)
	if (st[i]>47 && st[i]<58) s=s+st[i];
if (s.Length()<10 || s.Length()>11) return false;
if (s.Length()==10)
	s="8"+s;
else
	if (s[1] != '8') return false;
s.Insert("(",2); s.Insert(")",6); s.Insert("-",10); s.Insert("-",13);
st=s;
return true;
}

//--------------------- Форматирование модели -------------------------------
bool __fastcall TNewOrdForm::DevModelFormat(String &st)
{
String s,tp,md;  //тип и модель устройства
int i;
s=st.Trim();
i=s.Pos(" ");
if (s>"")
	{
	if (i>0)   //найдена марка и модель
		{
		//форморование типа
		tp=s.SubString(1,i);
		tp=tp.Trim();
		if (tp.UpperCase()=="ТЕЛ") tp="Телефон";
		if (tp.UpperCase()=="СИС") tp="Системный блок";
		if (tp.UpperCase()=="НБ")  tp="Ноутбук";
		if (tp.UpperCase()=="ПЛ")  tp="Планшет";
		if (tp.UpperCase()=="ПРИ") tp="Принтер";
		if (tp.UpperCase()=="КАР") tp="Картридж";
		if (tp.UpperCase()=="БП")  tp="Блок питания";
		//форморование модели
		md=s.SubString(i+1,s.Length()-i);
		md=md.UpperCase();
		md=md.Trim();
		s=tp+" "+md;
		}
	st=s;    //найдена только марка
	return true;
	}
else
	return false;
}

//-------------------- Форматирование серийника -----------------------------
bool __fastcall TNewOrdForm::DevIDFormat(String &st)
{
int i;
bool l=false; //есть ли буквы и русские буквы
st=st.Trim();
if (st=="") return true;
for (i=1; i <= st.Length(); i++)
	{
	if (st[i]>=1040 && st[i]<=1103) return false;  //есть русские буквы
	if (st[i]<48 || st[i]>57) l=true;
	}
if (!l && (i!=16)) return false;   //если только цыфры - их д.б. 15
st=st.UpperCase();
return true;
}

//---------------------- Форматирование неисправности -----------------------
bool __fastcall TNewOrdForm::DevDefectFormat(String &st)
{
st=st.Trim();
if (st=="") return false;
return true;
}

//-------------------- Форматирование согласованной цены --------------------
bool __fastcall TNewOrdForm::MaxPriceFormat(String &st)
{
String s;
int i;
for (i=1; i<=st.Length(); i++)	if (st[i]>47 && st[i]<58) s+=st[i];
if (s=="") return false;
if (StrToInt(s)<100) return false;
st=s; return true;
}
//---------------------------------------------------------------------------

