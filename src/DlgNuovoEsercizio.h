/**
 * DlgNuovoEsercizio.h
 * Created by G.Capelli on 26/04/2014
 * This file is part of LogOS (https://github.com/GrazianoCapelli/LogOS)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

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
