/**
 * DlgNuovoEsercizio.cpp
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

#include "FrmProiettore.h"
#include "DlgNuovoEsercizio.h"
#include <wx/stdpaths.h>
#include <wx/dir.h>
#include <wx/timer.h>
#include <wx/numformatter.h>
#include <wx/tokenzr.h>
#include "FrmReport.h"


// La funzione controlla la coerenza dei dati inseriti nella finestra di dialogo e attiva/disattiva il tasto "avvia"
void DlgNuovoEsercizio::OnCheckAvviaTimer(wxTimerEvent& event)
{
	// Controllo delle sillabe e settaggio della scelta delle unità di misura

	if ((MinNumSillabe == 0) && (m_choiceUMEsposizione->GetCount() == 2)) {		// Elimino l'opzione "sillabe/secondo"
		if ((m_choiceUMEsposizione->GetSelection() == 1)) {
			m_textCtrlTempoEsposizione->Clear();
			ValueEsposizione = 0;
		}
		m_choiceUMEsposizione->Clear();
		m_choiceUMEsposizione->Append("Millisecondi");
		m_choiceUMEsposizione->SetSelection(0);
	}
	if ((MinNumSillabe > 0) && (m_choiceUMEsposizione->GetCount() == 1)) {		// Ripristino l'opzione "Sillabe al secondo"
		m_choiceUMEsposizione->Clear();
		m_choiceUMEsposizione->Append("Millisecondi");
		m_choiceUMEsposizione->Append("Sillabe al secondo");

		if (ValueEsposizione == 0) {
			m_textCtrlTempoEsposizione->Clear();
			ValueEsposizione = 0;
			m_choiceUMEsposizione->SetSelection(1);
		} else {
			m_choiceUMEsposizione->SetSelection(0);
		}
	}
    
    if (m_choiceUMEsposizione->GetCount() > 1) m_choiceUMEsposizione->Enable();
    else m_choiceUMEsposizione->Enable(false);


	//bool ToBeEnabled = true;

	// Controllo della lista degli ITEM e della lunghezza dell'esercizio

	if (ItemListFiltered.size() == 0) {	// La lista degli item è vuota
		m_buttonAvvia->Enable(false);
		if (m_spinCtrlNumItems->GetMax() < 40) {
			m_spinCtrlNumItems->SetRange(5, 40);
			m_spinCtrlNumItems->SetValue(NumItemsDesiderati);
		}
		return;
	}
	if (ItemListFiltered.size() >= 5) {
		if (ItemListFiltered.size() < 40) {
			if (m_spinCtrlNumItems->GetValue() > (int)(ItemListFiltered.size())) {
				m_spinCtrlNumItems->SetValue(ItemListFiltered.size());
			} else {
				m_spinCtrlNumItems->SetValue(NumItemsDesiderati);
			}
			m_spinCtrlNumItems->SetRange(5, ItemListFiltered.size());
		} else {
			if (m_spinCtrlNumItems->GetMax() < 40) {
				m_spinCtrlNumItems->SetRange(5, 40);
				m_spinCtrlNumItems->SetValue(NumItemsDesiderati);
			}
		}
	} else {
		m_buttonAvvia->Enable(false);
		if (m_spinCtrlNumItems->GetMax() < 40) {
			m_spinCtrlNumItems->SetRange(5, 40);
			m_spinCtrlNumItems->SetValue(NumItemsDesiderati);
		}
		return;
	}

	// Controllo del tempo di esposizione

	if (ValueEsposizione) {

	} else {
		m_buttonAvvia->Enable(false);
		return;
	}

	m_buttonAvvia->Enable(true);
}


// La funzione aggiorna la lista degli item selezionati nella m_checkListBoxListe, e li carica nella lista item non filtrati.
// La funzione viene eseguita quando cambia la selezione delle liste nella sezione "tipologia di esercizio".
void DlgNuovoEsercizio::UpdateItemListUnfiltered()
{
	ItemListUnfiltered.clear();

	if (m_checkListBoxListe->GetCount() > 0) {	// Se la lista contiene elementi
		for (unsigned int i = 0; i < m_checkListBoxListe->GetCount(); ++i) {
			if (m_checkListBoxListe->IsChecked(i)) {	// Se l'elemento i-esimo ha il segno di spunta
				for (std::list<List>::iterator list_iter = ListOfLists.begin(); list_iter != ListOfLists.end(); ++list_iter) {
					if (m_checkListBoxListe->GetString(i) == list_iter->Name) {
						//std::list<Item>::iterator item_iter = list_iter->ItemList.begin();
						ItemListUnfiltered.insert(ItemListUnfiltered.end(), list_iter->ItemList.begin(), list_iter->ItemList.end());
					}
				}
			}
		}
	}

	/* ----------------- Codice di verifica temporaneo
	m_staticTextService->SetLabel(wxString::Format(_T("%d"), ItemListUnfiltered.size()) + " items selezionati");
	m_textTempUnf->Clear();
	for (std::list<Item>::iterator item_iter = ItemListUnfiltered.begin(); item_iter != ItemListUnfiltered.end(); ++item_iter) {
		m_textTempUnf->AppendText("  ");
		m_textTempUnf->AppendText(wxString::Format(_T("%d"),item_iter->NumSillabe));
		m_textTempUnf->AppendText("  ");
		m_textTempUnf->AppendText(item_iter->Value);
		m_textTempUnf->AppendText("\n");
	}
	*/
}

DlgNuovoEsercizio::DlgNuovoEsercizio(wxWindow* parent)
	: DialogNuovoEsercizio(parent)
{
	// Popola la droplist dei tipi di liste
	// Leggendo le sottocartelle della cartella Liste

	LoadLists();

	wxString path = wxStandardPaths::Get().GetExecutablePath();
    wxFileName::SplitPath(wxStandardPaths::Get().GetExecutablePath(),&path,NULL,NULL);
    //path.Truncate(path.size()-5);
    path.Append(DirChar);
	path.Append(_("Liste"));
    path.Append(DirChar);

	wxDir dir(path);
	if ( !dir.IsOpened() ) {
		// deal with the error here - wxDir would already log an error message
		// explaining the exact reason of the failure
		return;
	}
	//puts("Enumerating object files in current directory:");
	wxString filename;
	bool cont = dir.GetFirst(&filename, wxEmptyString, wxDIR_DEFAULT);
	while ( cont ) {
		m_choiceTipoScheda->Append(filename.c_str());
		//printf("%s\n", filename.c_str());
		cont = dir.GetNext(&filename);
	}
    
    // Stile TextCtrl item
    m_textCtrlAnteprima->SetValue(wxT("\nitem"));
    m_textCtrlAnteprima->SetBackgroundColour(wxColour(wxT("rgb(0,0,0)")));
    m_textCtrlAnteprima->SetForegroundColour(wxColour(wxT("rgb(255,255,255)")));
    //m_textCtrlAnteprima->Refresh();
    m_textCtrlAnteprima->SetDefaultStyle(wxTextAttr(wxColour(wxT("rgb(255,255,255)")), wxColour(wxT("rgb(0,0,0)"))));
    m_textCtrlAnteprima->SetStyle(0, m_textCtrlAnteprima->GetValue().length(), m_textCtrlAnteprima->GetDefaultStyle());
    //m_textCtrlAnteprima->Refresh();

	/* CODICE DI VERIFICA, TEMPORANEO
	//m_staticTextService->SetLabel(wxString::Format(_T("%d"), AvailableLists));

	for (std::list<List>::iterator list_iter = ListOfLists.begin(); list_iter != ListOfLists.end(); ++list_iter) {
		m_textTemp->AppendText(list_iter->Name);
		m_textTemp->AppendText("\n");
		for (std::list<Item>::iterator item_iter = list_iter->ItemList.begin(); item_iter != list_iter->ItemList.end(); ++item_iter) {
			m_textTemp->AppendText("  ");
			m_textTemp->AppendText(wxString::Format(_T("%d"),item_iter->NumSillabe));
			m_textTemp->AppendText("  ");
			m_textTemp->AppendText(item_iter->Value);
			m_textTemp->AppendText("\n");
		}
	}*/

	MinNumSillabe = 100;
	MaxNumSillabe = 0;
	NumItemsDesiderati = 20;
	ValueEsposizione = 0;

	// Avvia il timer per la verifica di attivazione pulsante "Avvia"

	CheckAvviaTimer.SetOwner(this);
	this->Connect(CheckAvviaTimer.GetId(),wxEVT_TIMER,wxTimerEventHandler( DlgNuovoEsercizio::OnCheckAvviaTimer ), NULL, this );
	CheckAvviaTimer.Start(200);
    
    m_staticTextService->Hide();
    m_staticTextService->SetToolTip("Verificare: ");
    wxString virgola = "";
	
	// Carica preimpostazioni (se specificate)
	
	if (Paziente->Base_per_nuovo_esercizio != NULL) {
		printf("CARICAMENTO PREIMPOSTAZIONI...\n");
		
		//---------------------------------------------------
		// TODO = Dimensione carattere !!!!
		//---------------------------------------------------
		
		// Text Case
		int tcase = m_choiceMinuscolo->FindString(Paziente->Base_per_nuovo_esercizio->TextCase, true);
		if (tcase != wxNOT_FOUND) {
			m_choiceMinuscolo->SetSelection(tcase);
			doOnChoiceMinuscoloChanged();
		} else {
            m_staticTextService->Show();
            m_staticTextService->SetToolTip(m_staticTextService->GetToolTipText() + virgola + "formattazione");
            virgola = ", ";
        }
		
		// Colori testo
		int tcol = m_choiceColori->FindString(Paziente->Base_per_nuovo_esercizio->TextColorscheme, true);
		if (tcol != wxNOT_FOUND) {
			m_choiceColori->SetSelection(tcol);
			doOnChoiceColoriChanged();
		} else {
            m_staticTextService->Show();
            m_staticTextService->SetToolTip(m_staticTextService->GetToolTipText() + virgola + "colori");
            virgola = ", ";
        }
		
		// Dimensione testo
		if (!Paziente->Base_per_nuovo_esercizio->TextSize.IsEmpty()) {
			m_spinCtrlDimensioni->SetValue(Paziente->Base_per_nuovo_esercizio->TextSize);
			doOnFontDimensionChanged();
		} else {
            m_staticTextService->Show();
            m_staticTextService->SetToolTip(m_staticTextService->GetToolTipText() + virgola + "dimensione testo");
            virgola = ", ";
        }
		
		// Mascheramento
		if (!Paziente->Base_per_nuovo_esercizio->Mask.IsEmpty()) {
			if (Paziente->Base_per_nuovo_esercizio->Mask == " ") m_checkBoxMascheramento->SetValue(false);
			if (Paziente->Base_per_nuovo_esercizio->Mask == "mascheramento") m_checkBoxMascheramento->SetValue(true);
		} else {
            m_staticTextService->Show();
            m_staticTextService->SetToolTip(m_staticTextService->GetToolTipText() + virgola + "mascheramento");
            virgola = ", ";
        }
		//m_checkBoxMascheramento->SetValue(Paziente->Base_per_nuovo_esercizio->Mask);
		
		// Preavviso
		if (!Paziente->Base_per_nuovo_esercizio->Forewarning.IsEmpty()) {
			if (Paziente->Base_per_nuovo_esercizio->Forewarning == " ") m_checkBoxSegnalePreavviso->SetValue(false);
			if (Paziente->Base_per_nuovo_esercizio->Forewarning == "preavviso") m_checkBoxSegnalePreavviso->SetValue(true);
		} else {
            m_staticTextService->Show();
            m_staticTextService->SetToolTip(m_staticTextService->GetToolTipText() + virgola + "preavviso");
            virgola = ", ";
        }
		//m_checkBoxSegnalePreavviso->SetValue(Paziente->Base_per_nuovo_esercizio->Forewarning);
		
		// Numero di items
		printf("- Numero di Items = ");
		printf(Paziente->Base_per_nuovo_esercizio->Numitems);
		printf("\n");
		m_spinCtrlNumItems->SetValue(Paziente->Base_per_nuovo_esercizio->Numitems);
		NumItemsDesiderati = m_spinCtrlNumItems->GetValue();
		
		// Esposizione
		int expum = m_choiceUMEsposizione->FindString(Paziente->Base_per_nuovo_esercizio->ExpUm, true);
		printf("- Esposizione = ");
		printf(Paziente->Base_per_nuovo_esercizio->ExpVal);
		printf(" ");
		printf(Paziente->Base_per_nuovo_esercizio->ExpUm);
		printf("\n");
		if (expum != wxNOT_FOUND) {
			m_choiceUMEsposizione->SetSelection(expum);
			m_textCtrlTempoEsposizione->SetValue(Paziente->Base_per_nuovo_esercizio->ExpVal);
		}  else {
            m_staticTextService->Show();
            m_staticTextService->SetToolTip(m_staticTextService->GetToolTipText() + virgola + "esposizione");
            virgola = ", ";
        }
		
		// Validazione
		printf("- Validazione = ");
		printf(Paziente->Base_per_nuovo_esercizio->Validation);
		printf("\n");
		int valid = m_choiceRisposta->FindString(Paziente->Base_per_nuovo_esercizio->Validation, true);
		if (valid != wxNOT_FOUND) {
			m_choiceRisposta->SetSelection(valid);
		} else {
            m_staticTextService->Show();
            m_staticTextService->SetToolTip(m_staticTextService->GetToolTipText() + virgola + "validazione item");
            virgola = ", ";
        }
		
		// Filtri
		printf("- Filtro 1 = ");
		int ftype1 = m_choiceFiltro1->FindString(Paziente->Base_per_nuovo_esercizio->FilterType1, true);
		
		if ((ftype1 != wxNOT_FOUND) && !Paziente->Base_per_nuovo_esercizio->Filter1.IsEmpty()) {
			// Tipo di scheda trovata!
			printf(Paziente->Base_per_nuovo_esercizio->FilterType1);
			printf(" ");
			printf(Paziente->Base_per_nuovo_esercizio->Filter1);
			
			m_choiceFiltro1->SetSelection(ftype1);
			m_textCtrlFiltro1->Enable();
			m_textCtrlFiltro1->SetValue(Paziente->Base_per_nuovo_esercizio->Filter1);
			
			FilterList1.ClearFilters();
			FilterList1.AddFilters(m_textCtrlFiltro1->GetValue().Lower());
			FilterList1.FilterType = m_choiceFiltro1->GetStringSelection();
		} else printf("Non attivo");
		printf("\n");
		
		printf("- Filtro 2 = ");
		int ftype2 = m_choiceFiltro2->FindString(Paziente->Base_per_nuovo_esercizio->FilterType2, true);
		
		if ((ftype2 != wxNOT_FOUND) && !Paziente->Base_per_nuovo_esercizio->Filter2.IsEmpty()) {
			// Tipo di scheda trovata!
			printf(Paziente->Base_per_nuovo_esercizio->FilterType2);
			printf(" ");
			printf(Paziente->Base_per_nuovo_esercizio->Filter2);
			
			m_choiceFiltro2->SetSelection(ftype2);
			m_textCtrlFiltro2->Enable();
			m_textCtrlFiltro2->SetValue(Paziente->Base_per_nuovo_esercizio->Filter2);
			
			FilterList2.ClearFilters();
			FilterList2.AddFilters(m_textCtrlFiltro2->GetValue().Lower());
			FilterList2.FilterType = m_choiceFiltro2->GetStringSelection();
		} else printf("Non attivo");
		printf("\n");
		
		printf("- Filtro 3 = ");
		int ftype3 = m_choiceFiltro3->FindString(Paziente->Base_per_nuovo_esercizio->FilterType3, true);
		
		if ((ftype3 != wxNOT_FOUND) && !Paziente->Base_per_nuovo_esercizio->Filter3.IsEmpty()) {
			// Tipo di scheda trovata!
			printf(Paziente->Base_per_nuovo_esercizio->FilterType3);
			printf(" ");
			printf(Paziente->Base_per_nuovo_esercizio->Filter3);
			
			m_choiceFiltro3->SetSelection(ftype3);
			m_textCtrlFiltro3->Enable();
			m_textCtrlFiltro3->SetValue(Paziente->Base_per_nuovo_esercizio->Filter3);
			
			FilterList3.ClearFilters();
			FilterList3.AddFilters(m_textCtrlFiltro3->GetValue().Lower());
			FilterList3.FilterType = m_choiceFiltro3->GetStringSelection();
		} else printf("Non attivo");
		printf("\n");
		MakeFilteredList();
		
		// Tipo di esercizio
		int extype = m_choiceTipoScheda->FindString(Paziente->Base_per_nuovo_esercizio->Type, true);
		printf("- Tipo di scheda = ");
		printf(Paziente->Base_per_nuovo_esercizio->Type);
		printf("\n");
		if (extype != wxNOT_FOUND) {
			// Tipo di scheda trovata!
			//printf("Tipo di scheda trovata!\n");
			m_choiceTipoScheda->SetSelection(extype);
			doPopulateCheckListBoxListe();
			
			// Ricerca liste selezionate
			if (!Paziente->Base_per_nuovo_esercizio->Typelist.IsEmpty()) {
				// La lista tipi non è vuota
				printf("\nListe:\n");
                bool ListSelectionNeedsVerification = false;
				wxStringTokenizer tokenizer(Paziente->Base_per_nuovo_esercizio->Typelist, "+");
				while ( tokenizer.HasMoreTokens() )
				{
					wxString token = tokenizer.GetNextToken().Trim().Trim(false);
					printf(token);
					printf("\n");
					// process token here
					int listnr = m_checkListBoxListe->FindString(token, true);
					if (listnr != wxNOT_FOUND) {
						// Seleziona (check) la lista corrispondente
						m_checkListBoxListe->Check(listnr, true);
					} else ListSelectionNeedsVerification = true;
				}
				doOncheckBoxListeSelected();
                if (ListSelectionNeedsVerification) {
                    m_staticTextService->Show();
                    m_staticTextService->SetToolTip(m_staticTextService->GetToolTipText() + virgola + "selezione liste");
                    virgola = ", ";
                }
			}
		} else {
            m_staticTextService->Show();
            m_staticTextService->SetToolTip(m_staticTextService->GetToolTipText() + virgola + "tipologia di allenamento, selezione liste");
            virgola = ", ";
        }
	}
}


DlgNuovoEsercizio::~DlgNuovoEsercizio()
{
}


void DlgNuovoEsercizio::OnAnnullaEsercizio(wxCommandEvent& event)
{
	UnloadLists();
	FilterList1.ClearFilters();
	FilterList2.ClearFilters();
	FilterList3.ClearFilters();
	ItemListUnfiltered.clear();
	ItemListFiltered.clear();
	Destroy();
}

void DlgNuovoEsercizio::PopolaTextboxItemsCentrale()
{
	//m_textTempFlt->Clear();
	//for (std::list<Item>::iterator filter_iter = ItemListFiltered.begin(); filter_iter != ItemListFiltered.end(); ++filter_iter) {
	//	m_textTempFlt->AppendText(" " + filter_iter->Value + "\n");
	//}
	
	wxString ElencoItems;
	for (std::list<Item>::iterator filter_iter = ItemListFiltered.begin(); filter_iter != ItemListFiltered.end(); ++filter_iter) {
		ElencoItems.append(" " + filter_iter->Value + "\n");
	}
	m_textTempFlt->Clear();
	m_textTempFlt->AppendText(ElencoItems);
	m_textTempFlt->ShowPosition(0);
}

void DlgNuovoEsercizio::doPopulateCheckListBoxListe()
{
	// Svuota eventuali items già presenti nella lista

	m_checkListBoxListe->Clear();

	// Popola la checklist dei vari sottotipi di liste
	// Leggendo i files nelle sottocartelle della cartella selezionata

	wxString path = wxStandardPaths::Get().GetExecutablePath();
    wxFileName::SplitPath(wxStandardPaths::Get().GetExecutablePath(),&path,NULL,NULL);
    //path.Truncate(path.size()-5);
    path.Append(DirChar);
	path.Append(_("Liste"));
    path.Append(DirChar);
	path.Append(m_choiceTipoScheda->GetString(m_choiceTipoScheda->GetCurrentSelection()));

	wxDir dir(path);
	if ( !dir.IsOpened() ) {
		// deal with the error here - wxDir would already log an error message
		// explaining the exact reason of the failure
		return;
	}
	//puts("Enumerating object files in current directory:");
	wxString filename;
	bool cont = dir.GetFirst(&filename, wxEmptyString,wxDIR_FILES);
	while ( cont ) {
		m_checkListBoxListe->Append(filename.c_str());
		//printf("%s\n", filename.c_str());
		cont = dir.GetNext(&filename);
	}

	UpdateItemListUnfiltered();
	MakeFilteredList();

	// CODICE DI CONTROLLO - DA RIMUOVERE
	PopolaTextboxItemsCentrale();
}

void DlgNuovoEsercizio::PopulateCheckListBoxListe(wxCommandEvent& event)
{
	doPopulateCheckListBoxListe();
}


void DlgNuovoEsercizio::OnchoiceFiltro1changed(wxCommandEvent& event)
{
	if (m_choiceFiltro1->GetCurrentSelection() != 0) {
		m_textCtrlFiltro1->Enable();
	} else {
		m_textCtrlFiltro1->Clear();
		m_textCtrlFiltro1->Disable();
	}

	FilterList1.ClearFilters();
	FilterList1.AddFilters(m_textCtrlFiltro1->GetValue().Lower());
	FilterList1.FilterType = m_choiceFiltro1->GetStringSelection();

	MakeFilteredList();

	// CODICE DI CONTROLLO - DA RIMUOVERE
	PopolaTextboxItemsCentrale();
}


void DlgNuovoEsercizio::OnchoiceFiltro2changed(wxCommandEvent& event)
{
	if (m_choiceFiltro2->GetCurrentSelection() != 0) {
		m_textCtrlFiltro2->Enable();
	} else {
		m_textCtrlFiltro2->Clear();
		m_textCtrlFiltro2->Disable();
	}

	FilterList2.ClearFilters();
	FilterList2.AddFilters(m_textCtrlFiltro2->GetValue().Lower());
	FilterList2.FilterType = m_choiceFiltro2->GetStringSelection();

	MakeFilteredList();

	// CODICE DI CONTROLLO - DA RIMUOVERE
	PopolaTextboxItemsCentrale();
}


void DlgNuovoEsercizio::OnchoiceFiltro3changed(wxCommandEvent& event)
{
	if (m_choiceFiltro3->GetCurrentSelection() != 0) {
		m_textCtrlFiltro3->Enable();
	} else {
		m_textCtrlFiltro3->Clear();
		m_textCtrlFiltro3->Disable();
	}

	FilterList3.ClearFilters();
	FilterList3.AddFilters(m_textCtrlFiltro3->GetValue().Lower());
	FilterList3.FilterType = m_choiceFiltro3->GetStringSelection();

	MakeFilteredList();

	// CODICE DI CONTROLLO - DA RIMUOVERE
	PopolaTextboxItemsCentrale();
}


void DlgNuovoEsercizio::doOncheckBoxListeSelected()
{
	UpdateItemListUnfiltered();
	MakeFilteredList();

	// CODICE DI CONTROLLO - DA RIMUOVERE
	PopolaTextboxItemsCentrale();
}


void DlgNuovoEsercizio::OnTextCtrlFilter1Updated(wxCommandEvent& event)
{
	FilterList1.ClearFilters();
	FilterList1.AddFilters(m_textCtrlFiltro1->GetValue().Lower());
	MakeFilteredList();

	// CODICE DI CONTROLLO - DA RIMUOVERE
	PopolaTextboxItemsCentrale();
}


void DlgNuovoEsercizio::OnTextCtrlFilter2Updated(wxCommandEvent& event)
{
	FilterList2.ClearFilters();
	FilterList2.AddFilters(m_textCtrlFiltro2->GetValue().Lower());
	MakeFilteredList();

	// CODICE DI CONTROLLO - DA RIMUOVERE
	PopolaTextboxItemsCentrale();
}


void DlgNuovoEsercizio::OnTextCtrlFilter3Updated(wxCommandEvent& event)
{
	FilterList3.ClearFilters();
	FilterList3.AddFilters(m_textCtrlFiltro3->GetValue().Lower());
	MakeFilteredList();

	// CODICE DI CONTROLLO - DA RIMUOVERE
	PopolaTextboxItemsCentrale();
}

void DlgNuovoEsercizio::doOnFontDimensionChanged()
{
	//m_textCtrlAnteprima->SetFont(m_textCtrlAnteprimaFont);
    //m_textCtrlAnteprima->SetStyle(0, m_textCtrlAnteprima->GetValue().length(), m_textCtrlAnteprima->GetDefaultStyle());
    
    wxFont m_textCtrlAnteprimaFont(m_spinCtrlDimensioni->GetValue(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Tahoma"));
    wxColour m_txColour(m_choiceColori->GetSelection() == 0 ? wxColour(wxT("rgb(255,255,255)")) : wxColour(wxT("rgb(0,0,0)")));
    wxColour m_bkColour(m_choiceColori->GetSelection() == 1 ? wxColour(wxT("rgb(255,255,255)")) : wxColour(wxT("rgb(0,0,0)")));
    
    m_textCtrlAnteprima->SetBackgroundColour(m_bkColour);
    m_textCtrlAnteprima->SetForegroundColour(m_txColour);
        
    wxTextAttr m_textCtrlAnteprimaAttr(m_txColour, m_bkColour, m_textCtrlAnteprimaFont, wxTEXT_ALIGNMENT_CENTRE);
    m_textCtrlAnteprima->SetStyle(0, m_textCtrlAnteprima->GetValue().length(), m_textCtrlAnteprimaAttr);
    m_textCtrlAnteprima->SetDefaultStyle(m_textCtrlAnteprimaAttr);
    
}

void DlgNuovoEsercizio::OnFontDimensionChanged(wxSpinEvent& event)
{
	doOnFontDimensionChanged();
}

void DlgNuovoEsercizio::doOnChoiceMinuscoloChanged()
{
	if (m_choiceMinuscolo->GetSelection() == 0)
		m_textCtrlAnteprima->SetValue(m_textCtrlAnteprima->GetValue().MakeLower());
	if (m_choiceMinuscolo->GetSelection() == 1)
		m_textCtrlAnteprima->SetValue(m_textCtrlAnteprima->GetValue().MakeUpper());
        
    if (m_choiceColori->GetSelection() == 0) { // Bianco su sfondo Nero
		m_textCtrlAnteprima->SetBackgroundColour(wxColour(wxT("rgb(0,0,0)")));
		m_textCtrlAnteprima->SetForegroundColour(wxColour(wxT("rgb(255,255,255)")));
        m_textCtrlAnteprima->SetDefaultStyle(wxTextAttr(wxColour(wxT("rgb(255,255,255)")), wxColour(wxT("rgb(0,0,0)"))));
        m_textCtrlAnteprima->SetStyle(0, m_textCtrlAnteprima->GetValue().length(), m_textCtrlAnteprima->GetDefaultStyle());
        
	}
	if (m_choiceColori->GetSelection() == 1) { // Nero su sfondo Bianco
		m_textCtrlAnteprima->SetBackgroundColour(wxColour(wxT("rgb(255,255,255)")));
		m_textCtrlAnteprima->SetForegroundColour(wxColour(wxT("rgb(0,0,0)")));
        m_textCtrlAnteprima->SetDefaultStyle(wxTextAttr(wxColour(wxT("rgb(0,0,0)")), wxColour(wxT("rgb(255,255,255)"))));
        m_textCtrlAnteprima->SetStyle(0, m_textCtrlAnteprima->GetValue().length(), m_textCtrlAnteprima->GetDefaultStyle());
	}
}

void DlgNuovoEsercizio::OnChoiceMinuscoloChanged(wxCommandEvent& event)
{
	doOnChoiceMinuscoloChanged();
}

void DlgNuovoEsercizio::doOnChoiceColoriChanged()
{
	if (m_choiceColori->GetSelection() == 0) { // Bianco su sfondo Nero
		m_textCtrlAnteprima->SetBackgroundColour(wxColour(wxT("rgb(0,0,0)")));
		m_textCtrlAnteprima->SetForegroundColour(wxColour(wxT("rgb(255,255,255)")));
        m_textCtrlAnteprima->SetDefaultStyle(wxTextAttr(wxColour(wxT("rgb(255,255,255)")), wxColour(wxT("rgb(0,0,0)"))));
        m_textCtrlAnteprima->SetStyle(0, m_textCtrlAnteprima->GetValue().length(), m_textCtrlAnteprima->GetDefaultStyle());
        
	}
	if (m_choiceColori->GetSelection() == 1) { // Nero su sfondo Bianco
		m_textCtrlAnteprima->SetBackgroundColour(wxColour(wxT("rgb(255,255,255)")));
		m_textCtrlAnteprima->SetForegroundColour(wxColour(wxT("rgb(0,0,0)")));
        m_textCtrlAnteprima->SetDefaultStyle(wxTextAttr(wxColour(wxT("rgb(0,0,0)")), wxColour(wxT("rgb(255,255,255)"))));
        m_textCtrlAnteprima->SetStyle(0, m_textCtrlAnteprima->GetValue().length(), m_textCtrlAnteprima->GetDefaultStyle());
	}
}

void DlgNuovoEsercizio::OnChoiceColoriChanged(wxCommandEvent& event)
{
	doOnChoiceColoriChanged();
}


void DlgNuovoEsercizio::OnAvviaClicked(wxCommandEvent& event)
{
	Proj_Text_Size = m_spinCtrlDimensioni->GetValue();
	Proj_Preavviso = m_checkBoxSegnalePreavviso->IsChecked();
	Proj_Mascheramento = m_checkBoxMascheramento->IsChecked();
	Proj_Text_Maiuscolo = m_choiceMinuscolo->GetSelection();
	Proj_Text_Colori = m_choiceColori->GetSelection();
	Proj_Esposizione = ValueEsposizione;
	Proj_EsposizioneUM = m_choiceUMEsposizione->GetSelection();
	Proj_VerificaRisposta = m_choiceRisposta->GetSelection();

	InitProjector(m_spinCtrlNumItems->GetValue());


	FrmProiettore *DPROJ = new FrmProiettore(this);

	DPROJ->Report_types = m_choiceTipoScheda->GetString(m_choiceTipoScheda->GetSelection());
	DPROJ->Report_expval = m_textCtrlTempoEsposizione->GetValue();
	DPROJ->Report_expum = m_choiceUMEsposizione->GetString(m_choiceUMEsposizione->GetSelection());
	DPROJ->Report_verificationtype = m_choiceRisposta->GetString(m_choiceRisposta->GetSelection());
    
    // Filtri
    DPROJ->Report_filtertype1 = m_choiceFiltro1->GetString(m_choiceFiltro1->GetCurrentSelection());
    DPROJ->Report_filtertype2 = m_choiceFiltro2->GetString(m_choiceFiltro2->GetCurrentSelection());
    DPROJ->Report_filtertype3 = m_choiceFiltro3->GetString(m_choiceFiltro3->GetCurrentSelection());
    DPROJ->Report_filtertext1 = m_textCtrlFiltro1->GetValue().Lower().Trim().Trim(false);
    DPROJ->Report_filtertext2 = m_textCtrlFiltro2->GetValue().Lower().Trim().Trim(false);
    DPROJ->Report_filtertext3 = m_textCtrlFiltro3->GetValue().Lower().Trim().Trim(false);
	
	// Proiettore
	DPROJ->Report_TextColorscheme = m_choiceColori->GetString(m_choiceColori->GetCurrentSelection());
	DPROJ->Report_TextCase = m_choiceMinuscolo->GetString(m_choiceMinuscolo->GetCurrentSelection());


	if (m_checkListBoxListe->GetCount() > 0) {	// Se la lista contiene elementi
		for (unsigned int i = 0; i < m_checkListBoxListe->GetCount(); ++i) {
			if (m_checkListBoxListe->IsChecked(i)) {	// Se l'elemento i-esimo ha il segno di spunta
				DPROJ->Report_typelist.push_back(m_checkListBoxListe->GetString(i));
			}
		}
	}

    DPROJ->SetParent(this);
	DPROJ->ShowFullScreen(true);
    DPROJ->Show();

	m_buttonAnnullaEsercizio->SetLabel("Termina");
	m_buttonAnnullaEsercizio->SetToolTip("Ritorna alla cartella paziente");
    m_staticTextService->Hide();
}


void DlgNuovoEsercizio::OnNumItemChanged(wxSpinEvent& event)
{
	NumItemsDesiderati = m_spinCtrlNumItems->GetValue();
	//m_staticTextService->SetLabel(wxString::Format(_T("%d"),NumItemsDesiderati));
}


void DlgNuovoEsercizio::OnTempoEsposizioneUpdated(wxCommandEvent& event)
{
	if (m_textCtrlTempoEsposizione->GetValue().Trim().Trim(false) != "") {

		// Conversione del separatore decimale a seconda della localizzazione corrente

		char DS = wxNumberFormatter::GetDecimalSeparator();
		wxString strTExp = m_textCtrlTempoEsposizione->GetValue().Trim().Trim(false);

		if (DS == '.') strTExp.Replace(",", ".", true);
		if (DS == ',') strTExp.Replace(".", ",", true);

		double myvalue;
		if(!strTExp.ToDouble(&myvalue)) {
			ValueEsposizione = 0;
			m_textCtrlTempoEsposizione->SetForegroundColour(wxColour(wxT("rgb(255,0,0)")));
		} else {
			ValueEsposizione = myvalue;
			m_textCtrlTempoEsposizione->SetForegroundColour(m_textCtrlTempoEsposizione->GetDefaultAttributes().colFg);
		}
	} else {
		m_textCtrlTempoEsposizione->SetForegroundColour(m_textCtrlTempoEsposizione->GetDefaultAttributes().colFg);
		ValueEsposizione = 0;
	}
	//m_staticTextService->SetLabel(wxString::Format(_T("%f"), ValueEsposizione));
}


void DlgNuovoEsercizio::OnVisualizzaReportClicked(wxCommandEvent& event)
{
	if (!Paziente->ReportList.empty())
	{
		std::list<Report>::iterator Report_iter = Paziente->ReportList.end();
		Report_iter--;
		
		//for (std::list<Report>::iterator Rep_iter = Paziente->ReportList.begin(); (Rep_iter != Paziente->ReportList.end()); Rep_iter++) {
		
		FrmReport *DREP = new FrmReport(this);
		DREP->Show();
		DREP->LoadPage(Report_iter->NameFile);
	}
}


//bool istoggled = false;

void DlgNuovoEsercizio::OnChecklistboxlisteToggled(wxCommandEvent& event)
{
	printf("OnChecklistboxlisteToggled\n");
	
    // Setta il flag "toggled se è necessario (solo se OncheckBoxListeSelected sarà lanciato)
    //if (m_checkListBoxListe->GetSelection() != wxNOT_FOUND) istoggled = true;
    //else {
    //    istoggled = false;
        printf("(doOncheckBoxListeSelected)\n");
        doOncheckBoxListeSelected();
    //}
}

void DlgNuovoEsercizio::OncheckBoxListeSelected(wxCommandEvent& event)
{
    // Se viene selezionato l'item ma non la casella di spunta, esegue il toggle lo stesso
	printf("OncheckBoxListeSelected\n");
	//if (m_checkListBoxListe->GetSelection() != wxNOT_FOUND && !istoggled) {
	//	bool newstate = !m_checkListBoxListe->IsChecked(m_checkListBoxListe->GetSelection());
	//	m_checkListBoxListe->Check(m_checkListBoxListe->GetSelection(), newstate);
	//	printf("(doOncheckBoxListeSelected)\n");
	//	doOncheckBoxListeSelected();
	//
	//}
	m_checkListBoxListe->SetSelection(wxNOT_FOUND);
	//istoggled = false;
}
