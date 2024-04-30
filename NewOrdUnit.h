//---------------------------------------------------------------------------

#ifndef NewOrdUnitH
#define NewOrdUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>
// #include "frxClass.hpp"
#include <Vcl.ExtCtrls.hpp>
#include "frxClass.hpp"
//---------------------------------------------------------------------------
class TNewOrdForm : public TForm
{
__published:	// IDE-managed Components
	TADOQuery *TempQuery;
	TButton *OKButton;
	TEdit *OwnNameEdit;
	TEdit *OwnTelEdit;
	TEdit *DevModelEdit;
	TEdit *DevIDEdit;
	TEdit *DevDefectEdit;
	TEdit *MaxPriceEdit;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TImage *TitleImage;
	TfrxReport *NewOrdReport;
	TEdit *DevRemEdit;
	TLabel *Label1;
	void __fastcall OKButtonClick(TObject *Sender);
	void __fastcall AnyEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall AnyEditExit(TObject *Sender);
	void __fastcall AnyEditEnter(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall AnyEditKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// User declarations
public:		// User declarations
	bool __fastcall OwnNameFormat(String &st);
	bool __fastcall OwnTelFormat(String &st);
	bool __fastcall DevModelFormat(String &st);
	bool __fastcall DevIDFormat(String &st);
	bool __fastcall DevDefectFormat(String &st);
	bool __fastcall MaxPriceFormat(String &st);
    String __fastcall OwnNamePrintFormat(String st);   //правильное тображение при печати
	bool OwnNameOK;  //признаки правильного запонени€
	bool OwnTelOK;
	bool DevModelOK;
	bool DevIDOK;
	bool DevDefectOK;
	bool MaxPriceOK;
	bool DevRemOK;
	int NewOrdNum;          // Ќомер нового заказа
	TDateTime NewDateIn;    // ƒата нового заказа
	bool CleanStart;        // „истый запуск или со старыми данными
	__fastcall TNewOrdForm(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TNewOrdForm *NewOrdForm;
//---------------------------------------------------------------------------
#endif
