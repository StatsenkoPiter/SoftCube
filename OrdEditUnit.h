//---------------------------------------------------------------------------

#ifndef OrdEditUnitH
#define OrdEditUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.DBGrids.hpp>
// #include "frxClass.hpp"
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include "frxClass.hpp"
//---------------------------------------------------------------------------
class TOrdEditForm : public TForm
{
__published:	// IDE-managed Components
	TImage *TitleImage;
	TADOQuery *TempQuery;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TEdit *OwnNameEdit;
	TEdit *OwnTelEdit;
	TEdit *DevModelEdit;
	TEdit *DevIDEdit;
	TEdit *DevDefectEdit;
	TEdit *DevRemEdit;
	TButton *PrintButton;
	TButton *ReadyButton;
	TButton *NotNeedButton;
	TButton *ImpassButton;
	TPopupMenu *PrintMenu;
	TMenuItem *N1;
	TMenuItem *N2;
	TButton *AgreeButton;
	TButton *GiveButton;
	TButton *GetButton;
	TButton *GetWarButton;
	TfrxReport *ReadyReport;
	TfrxReport *ImpassReport;
	TfrxReport *NotNeedReport;
	TGroupBox *GroupBox2;
	TLabel *Label7;
	TLabel *Label8;
	TEdit *DevResultEdit;
	TEdit *WorkPriceEdit;
	TDateTimePicker *DateWarEdit;
	TCheckBox *WarCheckBox;
	TSpeedButton *SpeedButton1;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall DataChange();
	void __fastcall StatusChange();
	void __fastcall N1Click(TObject *Sender);
	void __fastcall WorkPriceEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall DevResultEditChange(TObject *Sender);
	void __fastcall WorkPriceEditChange(TObject *Sender);
	void __fastcall ReadyButtonClick(TObject *Sender);
	void __fastcall NotNeedButtonClick(TObject *Sender);
	void __fastcall ImpassButtonClick(TObject *Sender);
	void __fastcall AgreeButtonClick(TObject *Sender);
 	void __fastcall AnyEditEnter(TObject *Sender);
	void __fastcall AnyEditExit(TObject *Sender);
	void __fastcall AnyEditKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall AnyEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall GiveButtonClick(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall GetButtonClick(TObject *Sender);
	void __fastcall GetWarButtonClick(TObject *Sender);
	void __fastcall DateWarEditChange(TObject *Sender);
	void __fastcall WarCheckBoxClick(TObject *Sender);


private:	// User declarations
public:		// User declarations
void __fastcall SaveOrder(); // Сохранение данных заказа в базу
			// Признаки правильности заполнения основных данных
bool    	OwnNameOK,OwnTelOK,DevIDOK,DevModelOK,DevDefectOK,DevRemOK;
bool        MainDataOK;          // признак правильности всех данных
bool        ChMainData, ChWorkData; // признак измененности данных
int 		OrigOrdNum, CurOrdNum;
String 		OrigDevModel;
String 		OrigDevID;
String 		OrigDevDefect;
String 		OrigDevRem;
bool 		OrigItsWar, CurItsWar;
int 		OrigDevStatus, CurDevStatus;
String 		OrigDevResult;
bool 		OrigItsNotif;
String 		OrigOwnName;
String 		OrigOwnTel;
int         OrigMaxPrice, CurMaxPrice;
int 		OrigWorkPrice;
TDateTime 	CurDateIn;
TDateTime 	CurDateOut;
TDateTime 	OrigDateWar;
bool        OrigWar;
__fastcall TOrdEditForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TOrdEditForm *OrdEditForm;
//---------------------------------------------------------------------------
#endif
