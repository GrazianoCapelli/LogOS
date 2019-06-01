#ifndef DLGNUOVOESERCIZIO_H
#define DLGNUOVOESERCIZIO_H
#include "wxcrafter.h"
#include <wx/timer.h>


class DlgNuovoEsercizio : public DialogNuovoEsercizio
{
public:
	DlgNuovoEsercizio(wxWindow* parent);
	void UpdateItemListUnfiltered();
	virtual ~DlgNuovoEsercizio();

	void OnCheckAvviaTimer(wxTimerEvent& event);
	wxTimer CheckAvviaTimer;
	int NumItemsDesiderati;
	double ValueEsposizione;

protected:
    virtual void OnChecklistboxlisteToggled(wxCommandEvent& event);
	virtual void OnVisualizzaReportClicked(wxCommandEvent& event);
	virtual void OnTempoEsposizioneUpdated(wxCommandEvent& event);
	virtual void OnNumItemChanged(wxSpinEvent& event);
	virtual void OnAvviaClicked(wxCommandEvent& event);
	virtual void doOnChoiceColoriChanged();
	virtual void OnChoiceColoriChanged(wxCommandEvent& event);
	virtual void doOnChoiceMinuscoloChanged();
	virtual void OnChoiceMinuscoloChanged(wxCommandEvent& event);
	virtual void doOnFontDimensionChanged();
	virtual void OnFontDimensionChanged(wxSpinEvent& event);
	virtual void OnTextCtrlFilter2Updated(wxCommandEvent& event);
	virtual void OnTextCtrlFilter3Updated(wxCommandEvent& event);
	virtual void OnTextCtrlFilter1Updated(wxCommandEvent& event);
	virtual void doOncheckBoxListeSelected();
	virtual void OncheckBoxListeSelected(wxCommandEvent& event);
	virtual void OnchoiceFiltro2changed(wxCommandEvent& event);
	virtual void OnchoiceFiltro3changed(wxCommandEvent& event);
	virtual void OnchoiceFiltro1changed(wxCommandEvent& event);
	virtual void doPopulateCheckListBoxListe();
	virtual void PopulateCheckListBoxListe(wxCommandEvent& event);
	virtual void PopolaTextboxItemsCentrale();
	virtual void OnAnnullaEsercizio(wxCommandEvent& event);
};
#endif // DLGNUOVOESERCIZIO_H
