#ifndef FRMPROIETTORE_H
#define FRMPROIETTORE_H
#include "wxcrafter.h"
#include "globals.h"
#include <wx/timer.h>
#include <wx/datetime.h>


class FrmProiettore : public FrameProiettore
{
public:
    FrmProiettore(wxWindow* parent);
    virtual ~FrmProiettore();
    
    wxString Report_types;					// Categoria esercizio
	std::list<wxString> Report_typelist;	// Lista delle liste selezionate da cui ha attinto l'esercizio
	wxString Report_expval;					// Valore esposizione
	wxString Report_expum;					// Unità di misura dell'esposizione
	wxString Report_verificationtype;		// Tipo di verifica (con reinserimento o bottoni sì/no)
    wxString Report_filtertype1;			// Tipo Filtro 1
    wxString Report_filtertype2;			// Tipo Filtro 2
    wxString Report_filtertype3;			// Tipo Filtro 3
    wxString Report_filtertext1;			// Testo Filtro 1
    wxString Report_filtertext2;			// Testo Filtro 2
    wxString Report_filtertext3;			// Testo Filtro 3
	wxString Report_TextColorscheme;	// Schema di colori proiettore
	wxString Report_TextCase;			// Maiuscolo o minuscolo
	wxString Report_TextSize;			// Grandezza carattere
	
	int PREAVVISO;
	int MASCHERAMENTO;
    


	std::list<ProjectionItem>::iterator CurrentSlide;
protected:
    void OnProjectorTimer(wxTimerEvent& event);
	void OnYawnTimer(wxTimerEvent& event);
	wxColour BGColour;
	wxColour FGColour;
	wxColour DColour;
	wxTimer ProjectorTimer;
	wxTimer YawnTimer;
	int SlidesProjected;
	
	int YawnCounter;
	int TimerCounter;
	wxString Preavviso;
	
	wxDateTime BeginEx;						// Data ed ora di inizio esercizio
	int RisposteCorrette;					// Numero di risposte date in maniera corretta
	int RisposteSbagliate;					// Numero di risposte date in maniera scorretta
	
	void EsercizioFinito();
	void MakeReport();
	
	wxBitmap Emoticon_Stars;
	wxBitmap Emoticon_Wow;
	wxBitmap Emoticon_Idea;
	wxBitmap Emoticon_Cool;
	wxBitmap Emoticon_Smile;
	wxBitmap Emoticon_Hey;
	wxBitmap Emoticon_Gotcha;
	wxBitmap Emoticon_Ouch;
	wxBitmap Emoticon_Damn;
	wxBitmap Emoticon_Wops;
	wxBitmap Emoticon_Yawn;


	virtual void OnAvantiClicked(wxCommandEvent& event);
	virtual void OnYesClicked(wxCommandEvent& event);
	virtual void OnNoClicked(wxCommandEvent& event);
	virtual void OnTextCtrlItemCheckTextEnter(wxCommandEvent& event);
	virtual void OnButtonVisualizzaReportSetFocus(wxFocusEvent& event);
	virtual void OnButtonterminaLeftUp(wxMouseEvent& event);
    virtual void SettextCtrlItemCheckStyle();
	virtual void VerificaCompletata();
};
#endif // FRMPROIETTORE_H
