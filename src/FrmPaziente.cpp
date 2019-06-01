#include "FrmPaziente.h"
#include "DlgNuovoEsercizio.h"
#include "globals.h"
#include "FrmReport.h"

Report* SelectedReport;

FrmPaziente::FrmPaziente(wxWindow* parent)
	: FramePaziente(parent)
{
	Parent = parent;
	Parent->Disable();
	Parent->Hide();

	m_textCtrlNome->SetValue(Paziente->Nome);
	m_textCtrlCognome->SetValue(Paziente->Cognome);
	m_textCtrlNatoIl->SetValue(Paziente->DataDiNascita);
	
    #ifdef __UNIX__
        if (wxFileExists(Paziente->CartellaDiLavoro + DirChar + "Notes.txt")) m_textCtrlNote->LoadFile(Paziente->CartellaDiLavoro + DirChar + "Notes.txt", wxTextFileType_Dos);
    #endif
    #ifdef __WINDOWS__
        if (wxFileExists(Paziente->CartellaDiLavoro + DirChar + "Notes.txt")) m_textCtrlNote->LoadFile(Paziente->CartellaDiLavoro + DirChar + "Notes.txt");
    #endif
	
	FrmPaziente::SetTitle("Cartella Paziente - " + Paziente->Cognome + " " + Paziente->Nome + " (" + Paziente->DataDiNascita + ")");

	LoadReports();

	//this->SetTitle("Cartella Paziente (" + Paziente->Nome + " " + Paziente->Cognome + ")");
}


FrmPaziente::~FrmPaziente()
{
	if (!wxIsEmpty(m_textCtrlNote->GetValue().Trim().Trim(false)))				// Nota presente
        #ifdef __UNIX__
            m_textCtrlNote->SaveFile(Paziente->CartellaDiLavoro + DirChar + "Notes.txt", wxTextFileType_Dos);
        #endif
        #ifdef __WINDOWS__
            m_textCtrlNote->SaveFile(Paziente->CartellaDiLavoro + DirChar + "Notes.txt");
        #endif
	else {																		// Nota non presente
		if (wxFileExists(Paziente->CartellaDiLavoro + DirChar + "Notes.txt")) wxRemoveFile(Paziente->CartellaDiLavoro + DirChar + "Notes.txt");
	}
	
	Parent->Show();
	Parent->Enable();
}


void FrmPaziente::OnChiudiPaziente(wxCommandEvent& event)
{		
	this->Close();
}


void FrmPaziente::OnNuovoEsercizio(wxCommandEvent& event)
{
	Paziente->Base_per_nuovo_esercizio = NULL;	// Non prende spunto da nessun esercizio esistente
	DlgNuovoEsercizio *DNEX = new DlgNuovoEsercizio(this);
	DNEX->Show();
	//LoadReports();
}

void FrmPaziente::OnNuovoEsercizioComePrecedente(wxCommandEvent& event)
{

	if (!Paziente->ReportList.empty()) {
		Paziente->Base_per_nuovo_esercizio = &(Paziente->ReportList.back());	// Prende spunto dall'ultimo esercizio svolto
	}
	DlgNuovoEsercizio *DNEX = new DlgNuovoEsercizio(this);
	DNEX->Show();
	//LoadReports();
}

void FrmPaziente::OnNuovoEsercizioComeSelezione(wxCommandEvent& event)
{
	if (!Paziente->ReportList.empty() && (SelectedReport != NULL)) {
		Paziente->Base_per_nuovo_esercizio = SelectedReport;	// Report selezionato
	}
	DlgNuovoEsercizio *DNEX = new DlgNuovoEsercizio(this);
	DNEX->Show();
}


void FrmPaziente::LoadReports()
{
	int Rep_date_index = 0;
	int Rep_time_index = 1;
	int Rep_type_allenamento = 2;
    int Rep_flags = 3;
	int Rep_exp = 4;
	int Rep_esito = 5;

	m_listCtrlReports->ClearAll();

	m_listCtrlReports->InsertColumn(Rep_date_index, _("Data"), wxLIST_FORMAT_LEFT, 90);
	m_listCtrlReports->InsertColumn(Rep_time_index , _("Ora"), wxLIST_FORMAT_LEFT, 70);
	m_listCtrlReports->InsertColumn(Rep_type_allenamento , _("Tipo di allenamento"), wxLIST_FORMAT_LEFT, 220);
    m_listCtrlReports->InsertColumn(Rep_flags , _("+"), wxLIST_FORMAT_CENTER, 20);
	m_listCtrlReports->InsertColumn(Rep_exp , _("Esposizione"), wxLIST_FORMAT_LEFT, 140);
	m_listCtrlReports->InsertColumn(Rep_esito , _("Esito"), wxLIST_FORMAT_CENTER, 50);

	if (!Paziente->ReportList.empty()) {
		for (std::list<Report>::iterator Rep_iter = Paziente->ReportList.begin(); (Rep_iter != Paziente->ReportList.end()); Rep_iter++) {
			long index = m_listCtrlReports->InsertItem(Rep_date_index, _(Rep_iter->Date));
			m_listCtrlReports->SetItem(index, Rep_time_index , _(Rep_iter->Time));
			m_listCtrlReports->SetItem(index, Rep_type_allenamento , _(Rep_iter->Type + ": " + Rep_iter->Typelist));
            m_listCtrlReports->SetItem(index, Rep_flags , _(Rep_iter->Flags));
			m_listCtrlReports->SetItem(index, Rep_exp , _(Rep_iter->ExpVal + " " + Rep_iter->ExpUm));
			m_listCtrlReports->SetItem(index, Rep_esito , _(Rep_iter->EsitoPercent + "%"));
		}
	}
	
	if (Paziente->ReportList.empty()) m_menuItemNuovoComePrecedente->Enable(false);
	else m_menuItemNuovoComePrecedente->Enable(true);
	
	m_menuItemNuovoComeSelezione->Enable(false);
	SelectedReport = NULL;
}

void FrmPaziente::OnListCtrlReportOpenReport(wxListEvent& event)
{
	std::list<Report>::iterator ListOfReport_iter = Paziente->ReportList.end();
	
	long RepIndex = -1;
	RepIndex = m_listCtrlReports->GetNextItem(RepIndex,
	                                       wxLIST_NEXT_ALL,
	                                       wxLIST_MASK_TEXT|wxLIST_STATE_SELECTED); // use wxLIST_STATE_DONTCARE for all items
	if (RepIndex != -1)
	{
		for (long i = 0; i <= RepIndex; i++) ListOfReport_iter--;
		
		FrmReport *DREP = new FrmReport(this);
		//DREP->Raise();
		DREP->Show();
		DREP->LoadPage(ListOfReport_iter->NameFile);
	}
}

void FrmPaziente::OnListCtrlReportItemSelected(wxListEvent& event)
{
	if (!Paziente->ReportList.empty() && m_listCtrlReports->GetSelectedItemCount()>0) {
		printf("Selected: \n");
		
		std::list<Report>::iterator ListOfReport_iter = Paziente->ReportList.end();
	
		long RepIndex = -1;
		RepIndex = m_listCtrlReports->GetNextItem(RepIndex,
											   wxLIST_NEXT_ALL,
											   wxLIST_MASK_TEXT|wxLIST_STATE_SELECTED); // use wxLIST_STATE_DONTCARE for all items
		if (RepIndex != -1)
		{
			for (long i = 0; i <= RepIndex; i++) ListOfReport_iter--;
			SelectedReport = &(*ListOfReport_iter);
			m_menuItemNuovoComeSelezione->Enable(true);
		}
	}
	else {
		SelectedReport = NULL;
		m_menuItemNuovoComeSelezione->Enable(false);
	};
}
