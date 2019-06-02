/**
 * FrmProiettore.cpp
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
#include "FrmPaziente.h"
#include "Emoticons.cpp"
#include <wx/wfstream.h>
#include <wx/txtstrm.h>
#include <wx/numformatter.h>


void FrmProiettore::MakeReport()
{
	wxString namefile = Paziente->CartellaDiLavoro + DirChar + BeginEx.Format("Tachistoscopio_%Y%m%d_%H%M%S") + ".html";
	
	wxFileOutputStream OutStr( namefile );
	wxTextOutputStream FRep(OutStr, wxEOL_DOS);
	
	FRep << "<!DOCTYPE html>" << endl;
	FRep << "<html>" << endl;
	FRep << "<body style=\"font-family: arial, helvetica, sans-serif;\">" << endl;
	FRep << endl;
	FRep << "<h1><!-- typeex -->Tachistoscopio<!-- /typeex --></h1>" << endl;
	FRep << "<h3>" << endl;
	FRep << "<font color=\"gray\"><u>Report esercizio</u></font>" << endl;
	FRep << "</h3>" << endl;
	FRep << endl;
	FRep << "<table>" << endl;
	FRep << "<tr>" << endl;
	FRep << "  <td width=\"120\"><font color=\"gray\">Paziente:</font></td>" << endl;
	FRep << "  <td><!-- patientsurname -->" << Paziente->Cognome << "<!-- /patientsurname --> <!-- patientname -->" << Paziente->Nome << "<!-- /patientname --> (<!-- birth -->";
	FRep << Paziente->DataDiNascita << "<!-- /birth -->)</td>" << endl;
	FRep << "</tr>" << endl;
	FRep << "<tr>" << endl;
	FRep << "  <td><font color=\"gray\">Data:</font></td>" << endl;
	FRep << "  <td><!-- date -->" << BeginEx.Format("%d/%m/%Y") << "<!-- /date --></td>" << endl;
	FRep << "</tr>" << endl;
	FRep << "<tr>" << endl;
	FRep << "  <td><font color=\"gray\">Ora:</font></td>" << endl;
	FRep << "  <td><!-- hour -->" << BeginEx.Format("%H:%M") << "<!-- /hour --></td>" << endl;
	FRep << "</tr>" << endl;
	FRep << "<tr height=\"20\">" << endl;
	FRep << "  <td></td>" << endl;
	FRep << "</tr>" << endl;
	FRep << "<tr>" << endl;
	FRep << "  <td width=\"120\"><font color=\"gray\">Tipologia:</font></td>" << endl;
	FRep << "  <td><!-- types -->" << Report_types << "<!-- /types -->: <!-- typelist -->";
	
	wxString plus = "";
	for (std::list<wxString>::iterator iter = Report_typelist.begin(); iter != Report_typelist.end(); ++iter)
	{
		FRep << plus << *iter;
		plus = " + ";
	}
	
	FRep << "<!-- /typelist --></td>" << endl;
	FRep << "</tr>" << endl;
    
    
    // Eventuali Filtri
    bool filter1 = !Report_filtertype1.IsEmpty() && !Report_filtertext1.IsEmpty();
    bool filter2 = !Report_filtertype2.IsEmpty() && !Report_filtertext2.IsEmpty();
    bool filter3 = !Report_filtertype3.IsEmpty() && !Report_filtertext3.IsEmpty();
    if (filter1 || filter2 || filter3) {
        FRep << "<tr>" << endl;
        FRep << "  <td><font color=\"gray\">Filtri:</font></td>" << endl;
        FRep << "  <td>";
        if (filter1) {  // Filtro 1
            FRep << "<!-- filter_type1 -->" << Report_filtertype1 << "<!-- /filter_type1 -->: <!-- filter_text1 -->" << Report_filtertext1 << "<!-- /filter_text1 -->";
            if (filter2 || filter3) {
                FRep << "</td>" << endl << "</tr>" << endl << "<tr>" << endl << "  <td></td>" << endl << "  <td>";
            }
        }
        if (filter2) {  // Filtro 2
            FRep << "<!-- filter_type2 -->" << Report_filtertype2 << "<!-- /filter_type2 -->: <!-- filter_text2 -->" << Report_filtertext2 << "<!-- /filter_text2 -->";
            if (filter3) {
                FRep << "</td>" << endl << "</tr>" << endl << "<tr>" << endl << "  <td></td>" << endl << "  <td>";
            }
        }
        if (filter3) {  // Filtro 3
            FRep << "<!-- filter_type3 -->" << Report_filtertype3 << "<!-- /filter_type3 -->: <!-- filter_text3 -->" << Report_filtertext3 << "<!-- /filter_text3 -->";
        }
        FRep << "</td>" << endl;
        FRep << "</tr>" << endl;
    }
	
	FRep << "<tr height=\"20\">" << endl;
	FRep << "  <td></td>" << endl;
	FRep << "</tr>" << endl;
	
	// Proiettore
	FRep << "<tr>" << endl;
	FRep << "  <td><font color=\"gray\">Proiettore:</font></td>" << endl;
	FRep << "  <td>Carattere <!-- textsize -->" << Proj_Text_Size << "<!-- /textsize -->, ";
	FRep << "<!-- textcase -->" << Report_TextCase << "<!-- /textcase -->, ";
	FRep << "<!-- colorscheme -->" << Report_TextColorscheme << "<!-- /colorscheme -->";
	FRep << "</td>" << endl;
	FRep << "</tr>" << endl;
	
    // Esposizione
	FRep << "<tr>" << endl;
	char DS = wxNumberFormatter::GetDecimalSeparator();
	wxString strTExp = Report_expum;
	if (DS == '.') strTExp.Replace(",", ".", true);
	if (DS == ',') strTExp.Replace(".", ",", true);
	FRep << "  <td><font color=\"gray\">Esposizione:</font></td>" << endl;
	FRep << "  <td><!-- expval -->" << Report_expval << "<!-- /expval --> <!-- expum -->" << strTExp << "<!-- /expum -->";
	
	// Preavviso e Mascheramento
	if (Proj_Mascheramento && Proj_Preavviso) {
		FRep << ", con <!-- forewarning -->preavviso<!-- /forewarning --> e <!-- mask -->mascheramento<!-- /mask -->";
	} else {
		if (Proj_Preavviso) FRep << ", con <!-- forewarning -->preavviso<!-- /forewarning --><!-- mask --> <!-- /mask -->";
		if (Proj_Mascheramento) FRep << ", con <!-- mask -->mascheramento<!-- /mask --><!-- forewarning --> <!-- /forewarning -->";
		if (!Proj_Mascheramento && !Proj_Preavviso) FRep << "<!-- mask --> <!-- /mask --><!-- forewarning --> <!-- /forewarning -->";
	}
	FRep << "</td>" << endl;
	FRep << "</tr>" << endl;
	
	// Validazione
	FRep << "<tr>" << endl;
	FRep << "  <td><font color=\"gray\">Validazione:</font></td>" << endl;
	FRep << "  <td><!-- validation -->" << Report_verificationtype << "<!-- /validation -->";
	FRep << "</td>" << endl;
	FRep << "</tr>" << endl;
	
	// Esito
	FRep << "<tr>" << endl;
	FRep << "  <td><font color=\"gray\">Esito:</font></td>" << endl;
	int Percentuale = (int)(100 * RisposteCorrette / (RisposteCorrette + RisposteSbagliate));
	if (Percentuale >= 70) {
		FRep << "  <td><font color=\"green\"><!-- result -->" << Percentuale << "<!-- /result -->%</font></td>" << endl;
	} else {
		FRep << "  <td><font color=\"red\"><!-- result -->" << Percentuale << "<!-- /result -->%</font></td>" << endl;
	}
	
	FRep << "</tr>" << endl;
	FRep << "</table>" << endl;
	FRep << endl;
	FRep << "<br>" << endl;
	FRep << endl << endl;
	
	FRep << "<h3>" << endl;
	FRep << "<font color=\"gray\"><u>Dettagli</u></font>" << endl;
	FRep << "</h3>" << endl;
	FRep << "<i><!-- numitems -->" << (int)ProjectionList.size() << "<!-- /numitems --> items:</i> <br><br>" << endl;
	FRep << endl;
	FRep << "<table>" << endl;
	
	bool finished = true;
	int i = 1 ;
	for (std::list<ProjectionItem>::iterator piter = ProjectionList.begin(); piter != ProjectionList.end(); ++piter, i++)
	{
		if (piter->Projected) {
			FRep << "<tr>" << endl;
			FRep << "  <td><font color=\"gray\">" << wxString::Format(wxT("%02i"), i) << "</font></td>" << endl;
			FRep << "  <td width=\"30\"></td>" << endl;
			FRep << "  <td><!-- item" << wxString::Format(wxT("%i"), i) << " -->" << piter->Value << "<!-- /item" << wxString::Format(wxT("%i"), i) << " --></td>" << endl;
			FRep << "  <td width=\"30\"></td>" << endl;
			if (piter->CorrectAnswer) {
				FRep << "  <td><font color=\"green\"><!-- aitem" << wxString::Format(wxT("%i"), i) << " -->" << piter->Answer << "<!-- /aitem" << wxString::Format(wxT("%i"), i) << " --></font></td>" << endl;
			} else {
				FRep << "  <td><font color=\"red\"><!-- aitem" << wxString::Format(wxT("%i"), i) << " -->" << piter->Answer << "<!-- /aitem" << wxString::Format(wxT("%i"), i) << " --></font></td>" << endl;			
			}
			FRep << "  <td width=\"30\"></td>" << endl;
			FRep << "  <td style=\"display:none;\"><font color=\"white\"><!-- sill" << wxString::Format(wxT("%i"), i) << " -->" << wxString::Format(wxT("%i"), piter->NumSillabe) << "<!-- /sill" << wxString::Format(wxT("%i"), i) << " --></font></td>" << endl;
			FRep << "</tr>" << endl;
		} else {
			finished = false;
		}
	}
	FRep << "</table>" << endl << endl;
	
	if (!finished) {
		FRep << "<i><br><br><!-- interrupted -->Esercizio interrotto<!-- /interrupted --></i>" << endl;
	}
	
	FRep << "</body>" << endl;
	FRep << "</html>";
	
	
	FRep.Flush();
	
	Paziente->LoadReportList();
	
	DlgNuovoEsercizio *parent = wxDynamicCast(this->GetParent(), DlgNuovoEsercizio);
	if(parent) {
		FrmPaziente *grandpa = wxDynamicCast(parent->GetParent(), FrmPaziente);
		if (grandpa) grandpa->LoadReports();
	}
}



void FrmProiettore::OnYawnTimer(wxTimerEvent& event)				// Timer x cambio faccina dopo 30 secondi di inattività;
{
	/*if (YawnCounter == 0) {
		m_staticBitmapEmoticon->SetBitmap(Emoticon_Gotcha);
		YawnTimer.Start(3000, true);
		YawnCounter++ ;
		return;
	}
	if (YawnCounter == 1) {
		m_staticBitmapEmoticon->SetBitmap(Emoticon_Smile);
		YawnTimer.Start(500, true);
		YawnCounter++ ;
		return;
	}*/
	if (YawnCounter == 0) {
		m_staticBitmapEmoticon->SetBitmap(Emoticon_Gotcha);
		YawnCounter = 0 ;
		return;
	}
}


void FrmProiettore::SettextCtrlItemCheckStyle() {
    if (Proj_Text_Colori == 0) { // Bianco su sfondo Nero
            BGColour = wxColour(wxT("rgb(0,0,0)"));
            FGColour = wxColour(wxT("rgb(255,255,255)"));
        }
        if (Proj_Text_Colori == 1) { // Nero su sfondo Bianco
            BGColour = wxColour(wxT("rgb(255,255,255)"));
            FGColour = wxColour(wxT("rgb(0,0,0)"));
        }
        wxFont m_textCtrlTextItemFont(Proj_Text_Size, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Tahoma"));
        wxTextAttr m_textCtrlAnteprimaAttr(FGColour, BGColour, m_textCtrlTextItemFont, wxTEXT_ALIGNMENT_CENTRE);
        m_textCtrlItemCheck->SetFont(m_textCtrlTextItemFont);
        m_textCtrlItemCheck->SetStyle(0, m_textCtrlItemCheck->GetValue().length(), m_textCtrlAnteprimaAttr);
        m_textCtrlItemCheck->SetDefaultStyle(m_textCtrlAnteprimaAttr);
}



void FrmProiettore::OnProjectorTimer(wxTimerEvent& event)
{
	wxString strmask('#',CurrentSlide->Value.length());
	
	switch (TimerCounter) {
		case (0):																// Imposto preavviso;
			m_staticTextItem->SetForegroundColour(BGColour);
			m_panelItemCheck->SetBackgroundColour(BGColour);
			m_textCtrlItemCheck->Hide();
			m_staticTextItem->SetLabel(Preavviso);
			m_staticTextItem->Refresh();
			m_staticTextItem->GetParent()->Layout();
			m_staticBitmapEmoticon->Hide();
			m_staticTextMessage->Hide();
			TimerCounter++;
			ProjectorTimer.Start(450, true);
			break;
		case (1):																// Lampeggia preavviso;
		case (2):
			if (TimerCounter % 2) m_staticTextItem->SetForegroundColour(BGColour);	// Dispari = Nascondo
			else m_staticTextItem->SetForegroundColour(FGColour);					// Pari = Mostro
			m_staticTextItem->Refresh();
			m_staticTextItem->GetParent()->Layout();
			TimerCounter++;
			ProjectorTimer.Start(100, true);
			break;
		case (3):																// Nascondo il preavviso, attesa tra preavviso e item;
			if (!Proj_Preavviso) {											// Se non è previsto il preavviso parto da qui!!
				m_panelItemCheck->SetBackgroundColour(BGColour);
				m_textCtrlItemCheck->Hide();
				m_staticBitmapEmoticon->Hide();
				m_staticTextMessage->Hide();
			}
			m_staticTextItem->SetForegroundColour(BGColour);
			m_staticTextItem->SetLabel(CurrentSlide->Value);
			m_staticTextItem->Refresh();
			m_staticTextItem->GetParent()->Layout();
			TimerCounter++;
			if (!Proj_Preavviso) ProjectorTimer.Start(550, true);
			else ProjectorTimer.Start(100, true);
			break;
		case (4):																	// Mostro l'item;
			m_staticTextItem->SetForegroundColour(FGColour);
			m_staticTextItem->Refresh();
			m_staticTextItem->GetParent()->Layout();
			TimerCounter++;
			ProjectorTimer.Start(CurrentSlide->exposureTime, true);
			break;
		case (5):																	// Comportamento proiettore con mascheramento attivato;
																					// Nascondo l'item;
			m_staticTextItem->SetForegroundColour(BGColour);
			m_staticTextItem->Refresh();
            m_staticTextItem->GetParent()->Layout();
			TimerCounter = TimerCounter + 1 + MASCHERAMENTO;
			ProjectorTimer.Start(100, true);
			break;
		case (6):																	// Mostro caratteri di mascheramento;
			m_staticTextItem->SetForegroundColour(BGColour);
			m_staticTextItem->SetLabel(strmask);
			m_staticTextItem->SetForegroundColour(FGColour);
			m_staticTextItem->Refresh();
            m_staticTextItem->GetParent()->Layout();
			TimerCounter++;
			ProjectorTimer.Start(200, true);
			break;
		case (7):																	// Nascondo il mascheramento;
			m_staticTextItem->SetForegroundColour(BGColour);
			m_staticTextItem->Refresh();
            m_staticTextItem->GetParent()->Layout();
			TimerCounter++;
			ProjectorTimer.Start(250, true);
			m_staticTextItem->SetLabel(CurrentSlide->Value); // Reimposto la stringa al valore proiettato;
			m_staticTextItem->GetParent()->Layout();
			break;
		case (8):																	// Verifica;
			if (Proj_VerificaRisposta == 0) {			// Reinserimento
				SettextCtrlItemCheckStyle();
				m_textCtrlItemCheck->SetValue("");
				m_textCtrlItemCheck->Show();
				m_textCtrlItemCheck->SetFocus();
			} else {									// Pulsanti Sì / No
				m_staticTextHint->Show();
				m_staticTextHint->SetToolTip(CurrentSlide->Value);
				m_buttonYes->Show();
				m_buttonNo->Show();
				m_buttonYes->GetParent()->Layout();
			}
			TimerCounter = PREAVVISO;
			CurrentSlide->Projected = true;
			SlidesProjected++;
			m_gaugeAvanzamento->SetValue(m_gaugeAvanzamento->GetValue() + 1);
			m_staticTextInfo->SetLabel(wxString::Format(_T("%d"), (SlidesProjected)) + " di " + wxString::Format(_T("%d"), (int)(ProjectionList.size())));
			break;
	}
}


FrmProiettore::FrmProiettore(wxWindow* parent)
	: FrameProiettore(parent)
{
	BeginEx = wxDateTime::Now();
	
	
	PREAVVISO = Proj_Preavviso ? 0 : 3;				// Salto il preavviso se non impostato
	MASCHERAMENTO = Proj_Mascheramento ? 0 : 1;		// Salto il mascheramento se non impostato

	YawnCounter = 0;
	TimerCounter = PREAVVISO;

	SlidesProjected = 0;
	Preavviso = "+";
	RisposteCorrette = 0;
	RisposteSbagliate = 0;

	// Iterator alla lista di slide
	CurrentSlide = ProjectionList.begin();

	// Timer
	ProjectorTimer.SetOwner(this);
	this->Connect(ProjectorTimer.GetId(),wxEVT_TIMER,wxTimerEventHandler( FrmProiettore::OnProjectorTimer ), NULL, this );
	YawnTimer.SetOwner(this);
	this->Connect(YawnTimer.GetId(),wxEVT_TIMER,wxTimerEventHandler( FrmProiettore::OnYawnTimer ), NULL, this );

	// --------------------- Impostazioni Proiettore -----------------------------

	DColour = wxColour(wxT("rgb(68,102,170)"));		// Colore di testi e bordi colorati
	if (Proj_Text_Colori == 0) { // Bianco su sfondo Nero
		BGColour = wxColour(wxT("rgb(0,0,0)"));
		FGColour = wxColour(wxT("rgb(255,255,255)"));
	}
	if (Proj_Text_Colori == 1) { // Nero su sfondo Bianco
		BGColour = wxColour(wxT("rgb(255,255,255)"));
		FGColour = wxColour(wxT("rgb(0,0,0)"));
	}

	m_gaugeAvanzamento->SetRange(ProjectionList.size());

	m_panelProjector->SetBackgroundColour(BGColour);
	m_panelProjector->SetForegroundColour(FGColour);
	m_textCtrlItemCheck->SetBackgroundColour(BGColour);
	m_textCtrlItemCheck->SetForegroundColour(FGColour);
	m_panelItemCheck->SetBackgroundColour(BGColour);
	m_textCtrlItemCheck->Hide();

	m_staticTextItem->SetForegroundColour(FGColour);
	m_staticTextItem->SetBackgroundColour(BGColour);
	//m_staticTextItem->SetExtraStyle(wxST_ELLIPSIZE_MIDDLE);

	wxFont m_textCtrlTextItemFont(Proj_Text_Size, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Tahoma"));
	m_staticTextItem->SetFont(m_textCtrlTextItemFont);

	m_staticTextInfo->SetLabel(wxString::Format(_T("%d"), (SlidesProjected)) + " di " + wxString::Format(_T("%d"), (int)(ProjectionList.size())));

	// Stile casella di inserimento
    SettextCtrlItemCheckStyle();
	
	m_staticTextHint->Show(false);
	m_buttonYes->Show(false);
	m_buttonNo->Show(false);
	m_buttonYes->GetParent()->Layout();



	// ---------------------------------------------------------------------------

    {
        wxLogNull AD;
        Emoticon_Stars = wxBITMAP_PNG_FROM_DATA(Emoticon_Stars);
        Emoticon_Wow = wxBITMAP_PNG_FROM_DATA(Emoticon_Wow);
        Emoticon_Idea = wxBITMAP_PNG_FROM_DATA(Emoticon_Idea);
        Emoticon_Cool = wxBITMAP_PNG_FROM_DATA(Emoticon_Cool);
        Emoticon_Smile = wxBITMAP_PNG_FROM_DATA(Emoticon_Smile);
        Emoticon_Hey = wxBITMAP_PNG_FROM_DATA(Emoticon_Hey);
        Emoticon_Gotcha = wxBITMAP_PNG_FROM_DATA(Emoticon_Gotcha);
        Emoticon_Ouch = wxBITMAP_PNG_FROM_DATA(Emoticon_Ouch);
        Emoticon_Damn = wxBITMAP_PNG_FROM_DATA(Emoticon_Damn);
        
        Emoticon_Yawn = wxBITMAP_PNG_FROM_DATA(Emoticon_Yawn);
        Emoticon_Wops = wxBITMAP_PNG_FROM_DATA(Emoticon_Wops);
    }

	m_staticBitmapEmoticon->SetBitmap(Emoticon_Smile);

	m_buttonAvanti->SetFocus();
}

FrmProiettore::~FrmProiettore()
{
}


void FrmProiettore::OnButtonVisualizzaReportSetFocus(wxFocusEvent& event)
{
	if (m_buttonAvanti->IsEnabled()) m_buttonAvanti->SetFocus();
	else m_textCtrlItemCheck->SetFocus();
}


void FrmProiettore::VerificaCompletata() {
	m_staticTextHint->Show(false);
	m_buttonYes->Show(false);
	m_buttonNo->Show(false);
	m_buttonYes->GetParent()->Layout();

	if ((CurrentSlide->Answer != "") || (Proj_VerificaRisposta)) {
		m_buttonAvanti->DeletePendingEvents();
		m_buttonAvanti->Enable();
		m_buttonTermina->SetFocus();

		CurrentSlide->CorrectAnswer = (CurrentSlide->Value == CurrentSlide->Answer);

		m_staticTextMessage->Show();

		if (CurrentSlide->CorrectAnswer) {		// Se la risposta è corretta
			//m_panelItemCheck->SetBackgroundColour(BGColour);
			m_textCtrlItemCheck->Hide();
			RisposteCorrette++;

			if ((RisposteCorrette + RisposteSbagliate) == (int)(ProjectionList.size())) EsercizioFinito();
			else {
				m_staticBitmapEmoticon->SetBitmap(Emoticon_Smile);
				m_staticBitmapEmoticon->Show();
				YawnTimer.Start(20000, true);
			}

		} else {								// Se la risposta è sbagliata
			m_staticTextItem->SetForegroundColour(FGColour);
			m_staticTextItem->Refresh();
            m_staticTextItem->GetParent()->Layout();

			m_staticBitmapEmoticon->SetBitmap(Emoticon_Ouch);
			m_staticBitmapEmoticon->Show();
			RisposteSbagliate++;
		}

		if (CurrentSlide != ProjectionList.end()) CurrentSlide++;		// Avanzamento alla slide successiva;
	}
}

void FrmProiettore::OnTextCtrlItemCheckTextEnter(wxCommandEvent& event)
{
	CurrentSlide->Answer = m_textCtrlItemCheck->GetValue().Trim().Trim(false);
	VerificaCompletata();
}


void FrmProiettore::OnYesClicked(wxCommandEvent& event)
{
	
	CurrentSlide->Answer = CurrentSlide->Value;
	VerificaCompletata();
}

void FrmProiettore::OnNoClicked(wxCommandEvent& event)
{
	CurrentSlide->Answer = "";
	VerificaCompletata();
}



void FrmProiettore::OnAvantiClicked(wxCommandEvent& event)
{
	if ((RisposteCorrette + RisposteSbagliate) == (int)(ProjectionList.size())) EsercizioFinito();
	else {
		if (!CurrentSlide->Projected) {
			m_buttonAvanti->Disable();
			m_textCtrlItemCheck->SetValue("");
			YawnTimer.Stop();
			ProjectorTimer.Start(100, true);	// Inizia la proiezione se non è ancora avvenuta
		} 
	}
}



void FrmProiettore::EsercizioFinito()
{
	int Percentuale = (int)(100 * RisposteCorrette / (RisposteCorrette + RisposteSbagliate));

	m_buttonAvanti->Disable();
    m_buttonAvanti->Hide();

	m_panelItemCheck->SetBackgroundColour(BGColour);
	m_textCtrlItemCheck->Hide();

	if (Percentuale == 0) m_staticBitmapEmoticon->SetBitmap(Emoticon_Damn);
	if ((Percentuale > 0) && (Percentuale <= 20)) m_staticBitmapEmoticon->SetBitmap(Emoticon_Ouch);
	if ((Percentuale > 20) && (Percentuale <= 40)) m_staticBitmapEmoticon->SetBitmap(Emoticon_Gotcha);
	if ((Percentuale > 40) && (Percentuale <= 50)) m_staticBitmapEmoticon->SetBitmap(Emoticon_Hey);
	if ((Percentuale > 50) && (Percentuale < 70)) m_staticBitmapEmoticon->SetBitmap(Emoticon_Smile);
	if (Percentuale == 70) m_staticBitmapEmoticon->SetBitmap(Emoticon_Cool);
	if ((Percentuale > 70) && (Percentuale < 80)) m_staticBitmapEmoticon->SetBitmap(Emoticon_Idea);
	if ((Percentuale >= 80) && (Percentuale < 85)) m_staticBitmapEmoticon->SetBitmap(Emoticon_Wow);
	if ((Percentuale >= 85)) m_staticBitmapEmoticon->SetBitmap(Emoticon_Stars);

	m_staticTextMessage->SetLabel("Esercizio terminato!");
	m_staticTextMessage->GetParent()->Layout();

	wxFont m_textCtrlTextItemFont(30, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Tahoma"));
	m_staticTextItem->SetFont(m_textCtrlTextItemFont);
	m_staticTextItem->SetLabel(wxString::Format(_T("%d"), Percentuale) + "% di risposte corrette");
	m_staticTextItem->GetParent()->Layout();

	m_staticBitmapEmoticon->Show();
	m_staticTextItem->SetForegroundColour(FGColour);
	m_staticTextItem->Show();
}


void FrmProiettore::OnButtonterminaLeftUp(wxMouseEvent& event)
{
	printf("LEFT UP\n");
	if (RisposteCorrette + RisposteSbagliate > 0) MakeReport();
	Destroy();
	//event.Skip();
}
