//---------------------------------------------------------------------------

#ifndef ReportsUnitH
#define ReportsUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "frxClass.hpp"
#include "frxPreview.hpp"
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TNewOrdReportForm : public TForm
{
__published:	// IDE-managed Components
	TfrxReport *Report;
	TButton *PrintButton;
	TButton *ExportButton;
	void __fastcall FormActivate(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TNewOrdReportForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TNewOrdReportForm *NewOrdReportForm;
//---------------------------------------------------------------------------
#endif
