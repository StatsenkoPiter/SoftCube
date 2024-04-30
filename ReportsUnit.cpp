//---------------------------------------------------------------------------

#include <vcl.h>

#pragma hdrstop

#include "ReportsUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "frxClass"
#pragma link "frxPreview"
#pragma link "frxRich"
#pragma resource "*.dfm"
TNewOrdReportForm *NewOrdReportForm;
//---------------------------------------------------------------------------
__fastcall TNewOrdReportForm::TNewOrdReportForm(TComponent* Owner)
	: TForm(Owner)
{
}

//---------------------------------------------------------------------------

void __fastcall TNewOrdReportForm::FormActivate(TObject *Sender)
{
Report->ShowReport(true);
}
//---------------------------------------------------------------------------

