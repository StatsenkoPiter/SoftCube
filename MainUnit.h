//---------------------------------------------------------------------------

#ifndef MainUnitH
#define MainUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
	TStatusBar *MainStatusBar;
	TMainMenu *MainMenu;
	TADOConnection *MainADOConnection;
	TADOTable *OrdersTab;
	TDataSource *OrdersTabDS;
	TADOTable *StatusTab;
	TPageControl *MainPageControl;
	TTabSheet *TabSheet1;
	TTabSheet *Торговля;
	TDBGrid *MainDBGrid;
	TButton *NewOrdButton;
	TEdit *SearchEdit;
	TSmallintField *OrdersTabOrdNum;
	TWideStringField *OrdersTabDevModel;
	TWideStringField *OrdersTabDevID;
	TWideStringField *OrdersTabDevDefect;
	TWideStringField *OrdersTabDevRem;
	TWordField *OrdersTabDevStatus;
	TBooleanField *OrdersTabItsWar;
	TWideMemoField *OrdersTabDevResult;
	TBooleanField *OrdersTabItsNotif;
	TWideStringField *OrdersTabOwnName;
	TWideStringField *OrdersTabOwnTel;
	TSmallintField *OrdersTabMaxPrice;
	TSmallintField *OrdersTabWorkPrice;
	TDateTimeField *OrdersTabDateIn;
	TDateTimeField *OrdersTabDateOut;
	TDateTimeField *OrdersTabDateWar;
	TStringField *OrdersTabDevStatusStr;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *N4;
	TMenuItem *N5;
	TMenuItem *N6;
	void __fastcall NewOrdButtonClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall MainDBGridDrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
          TColumn *Column, TGridDrawState State);
	void __fastcall OrdersTabOrdNumGetText(TField *Sender, UnicodeString &Text, bool DisplayText);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall SearchEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall MainDBGridDblClick(TObject *Sender);
	void __fastcall N6Click(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall MainDBGridTitleClick(TColumn *Column);
	private:			// User declarations

	public:				// User declarations
    void __fastcall FixMainGridWidth();
	__fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
