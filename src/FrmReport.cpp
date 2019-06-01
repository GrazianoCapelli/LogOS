#include "FrmReport.h"


FrmReport::FrmReport(wxWindow* parent)
	: FrameReport(parent)
{
}

FrmReport::~FrmReport()
{
}

void FrmReport::LoadPage(const wxString& location)
{
	m_htmlWinReport->LoadPage(location);
}

void FrmReport::OnCloseClicked(wxCommandEvent& event)
{
	Destroy();
}
