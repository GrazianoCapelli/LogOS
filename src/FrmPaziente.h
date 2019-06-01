#ifndef FRMPAZIENTE_H
#define FRMPAZIENTE_H
#include "wxcrafter.h"


class FrmPaziente : public FramePaziente
{
public:
	FrmPaziente(wxWindow* parent);
	virtual ~FrmPaziente();
	wxWindow* Parent;

	void LoadReports();

protected:
    virtual void OnListCtrlReportItemSelected(wxListEvent& event);
    virtual void OnNuovoEsercizioComeSelezione(wxCommandEvent& event);
    virtual void OnNuovoEsercizioComePrecedente(wxCommandEvent& event);
	virtual void OnListCtrlReportOpenReport(wxListEvent& event);
	virtual void OnNuovoEsercizio(wxCommandEvent& event);
	virtual void OnChiudiPaziente(wxCommandEvent& event);
};
#endif // FRMPAZIENTE_H
