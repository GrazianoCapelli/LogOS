#ifndef FRMREPORT_H
#define FRMREPORT_H
#include "wxcrafter.h"


class FrmReport : public FrameReport
{
public:
	FrmReport(wxWindow* parent);
	virtual ~FrmReport();

	void LoadPage(const wxString& location);
protected:
	virtual void OnCloseClicked(wxCommandEvent& event);
};
#endif // FRMREPORT_H
