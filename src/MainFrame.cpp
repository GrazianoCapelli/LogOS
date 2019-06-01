#include "MainFrame.h"
#include "DlgNuovoPaziente.h"
#include "FrmPaziente.h"
#include <wx/aboutdlg.h>
#include <wx/stdpaths.h>
#include <wx/dir.h>
#include <wx/wx.h>
#include <wx/textfile.h>
#include <list>
#include "globals.h"


MainFrame::MainFrame(wxWindow* parent)
	: MainFrameBaseClass(parent)
{
	cognome_index = 0;
	nome_index = 1;
	datanascita_index = 2;
	
	// Crea le cartelle Pazienti e Liste se non esistono
	wxString path = wxStandardPaths::Get().GetExecutablePath();
    wxFileName::SplitPath(wxStandardPaths::Get().GetExecutablePath(),&path,NULL,NULL);
    path.Append(DirChar);
	path.Append(_("Pazienti"));
    path.Append(DirChar);
	wxDir dir(path);
	if ( !dir.IsOpened() ) {
		dir.Make(path);
	}
	path = wxStandardPaths::Get().GetExecutablePath();
    wxFileName::SplitPath(wxStandardPaths::Get().GetExecutablePath(),&path,NULL,NULL);
    path.Append(DirChar);
	path.Append(_("Liste"));
    path.Append(DirChar);
	wxDir dirl(path);
	if ( !dirl.IsOpened() ) {
		dirl.Make(path);
	}
	wxDir dirl1(path);
	if (dirl1.IsOpened() ) {
		path.Append(_("Personalizzate"));
		path.Append(DirChar);
		wxDir dir1(path);
		if ( !dir1.IsOpened() ) {
			dir1.Make(path);
		}
	}

	PopolaListaPazienti();
}


MainFrame::~MainFrame()
{
}


struct Paz {
		wxString Cognome;
		wxString Nome;
		wxString DataDiNascita_GG;
		wxString DataDiNascita_MM;
		wxString DataDiNascita_AAAA;
		wxString DataDiNascita;
		wxString DirPath;
	};

void MainFrame::PopolaListaPazienti()
{
	std::list<Paz>::iterator ListOfPaz_iter;
	Paz TempPaz;
	std::list<Paz> ListOfPaz;				// La lista dei pazienti;
	
	
	
	if (Paziente != NULL) {
		delete Paziente;
		Paziente = NULL;
	}

	m_listCtrlPazienti->ClearAll();

	m_listCtrlPazienti->InsertColumn(cognome_index, _("Cognome"), wxLIST_FORMAT_LEFT, 120);
	m_listCtrlPazienti->InsertColumn(nome_index, _("Nome"), wxLIST_FORMAT_LEFT, 120);
	m_listCtrlPazienti->InsertColumn(datanascita_index, _("Data di nascita"), wxLIST_FORMAT_CENTER, 120);

	// Popola la droplist dei tipi di liste
	// Leggendo le sottocartelle della cartella Pazienti

	wxString path = wxStandardPaths::Get().GetExecutablePath();
    wxFileName::SplitPath(wxStandardPaths::Get().GetExecutablePath(),&path,NULL,NULL);
	//path.Truncate(path.size()-5);
    path.Append(DirChar);
	path.Append(_("Pazienti"));
    path.Append(DirChar);

	wxDir dir(path);
	if ( !dir.IsOpened() ) {
		if (!dir.Make(path)) return;
		//return;
		// deal with the error here - wxDir would already log an error message
		// explaining the exact reason of the failure
	}
	//puts("Enumerating object files in current directory:");
	wxString filename;
	bool cont = dir.GetFirst(&filename, wxEmptyString, wxDIR_DEFAULT);
	while ( cont ) {
		TempPaz.DirPath = _(dir.GetNameWithSep() + filename);
		TempPaz.Cognome = _(filename.c_str()).BeforeFirst('_');
		TempPaz.Nome = _(filename.c_str()).BeforeLast('_').AfterFirst('_');
		TempPaz.DataDiNascita_GG = _(filename.c_str()).AfterLast('_').Right(2);
		TempPaz.DataDiNascita_MM = _(filename.c_str()).AfterLast('_').Right(4).Left(2);
		TempPaz.DataDiNascita_AAAA = _(filename.c_str()).AfterLast('_').Left(4);
		TempPaz.DataDiNascita = TempPaz.DataDiNascita_GG + "/" + TempPaz.DataDiNascita_MM + "/" + TempPaz.DataDiNascita_AAAA;
		
		for (ListOfPaz_iter = ListOfPaz.begin(); (ListOfPaz_iter != ListOfPaz.end()) && (ListOfPaz_iter->DirPath > TempPaz.DirPath); ListOfPaz_iter++);
		ListOfPaz.insert(ListOfPaz_iter,TempPaz);
		
		cont = dir.GetNext(&filename);
	}
	
	if (!ListOfPaz.empty()) {
		for (ListOfPaz_iter = ListOfPaz.begin(); (ListOfPaz_iter != ListOfPaz.end()); ListOfPaz_iter++) {
			long index = m_listCtrlPazienti->InsertItem(cognome_index, _(ListOfPaz_iter->Cognome));
			m_listCtrlPazienti->SetItem(index, nome_index, _(ListOfPaz_iter->Nome));
			m_listCtrlPazienti->SetItem(index, datanascita_index, _(ListOfPaz_iter->DataDiNascita));
		}
	}

	// Disabilitazione voci menu e bottoni toolbar
	m_mainToolbar->EnableTool(wxID_OPEN, false);
	m_mainToolbar->EnableTool(wxID_DELETE, false);
	m_menuItemApri->Enable(false);
	m_menuItemElimina->Enable(false);
}


void MainFrame::OnExit(wxCommandEvent& event)
{
	wxUnusedVar(event);
	Close();
}


void MainFrame::OnAbout(wxCommandEvent& event)
{
	wxUnusedVar(event);
	wxAboutDialogInfo info;
	info.SetName(_("LogOS"));
	info.SetVersion(_(VersionName));
	info.SetCopyright(_("Copyright (C) 2014 Elena Capelli, Graziano Capelli"));

	wxString Lic;

	Lic = "GNU GENERAL PUBLIC LICENSE\nVersion 3, 29 June 2007\n\nPer maggiori informazioni consultare http://www.gnu.org/licenses/gpl-3.0.html\n\nEmoticons by: LazyCrazy (http://www.artdesigner.lv)";

	info.SetLicence(Lic);
	//info.SetLicence(_("GPL v2 or later\n\nQuesto programma non fornisce ALCUNA GARANZIA.\nPer maggiori informazioni consultare http://www.gnu.org/licenses/old-licenses/gpl-2.0.html"));
	info.SetDescription(_("Un programma per allenare la lettura."));
	::wxAboutBox(info);
}


void MainFrame::ApriPaziente(wxCommandEvent& event)
{
	FrmPaziente *FP = new FrmPaziente(this);
	FP->Show();
}


void MainFrame::EliminaPaziente(wxCommandEvent& event)
{
	long item = -1;
	item = m_listCtrlPazienti->GetNextItem(item,
	                                       wxLIST_NEXT_ALL,
	                                       wxLIST_STATE_SELECTED); // use wxLIST_STATE_DONTCARE for all items
	if ( item != -1 ) {
		wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Eliminare definitivamente il paziente\n" + Paziente->Cognome + " " + Paziente->Nome + " (" + Paziente->DataDiNascita + ")\ne tutta la sua cartella clinica?"),
		        wxT("Conferma eliminazione"),
		        wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
		//dial->SetYesNoLabels(_("Sì"), _("No")); // Non compatibile con tutte le piattaforme;
		if (dial->ShowModal() == wxID_YES) {
			/// Eliminazione

			if (wxDir::Remove(Paziente->CartellaDiLavoro, wxPATH_RMDIR_RECURSIVE) == false) {
				wxMessageBox(_T("Non è stato possibile eliminare\nla cartella del paziente"), "Errore", wxICON_ERROR);
			} else {
				PopolaListaPazienti();
			}
		}
	}
}


void MainFrame::NuovoPaziente(wxCommandEvent& event)
{
	DlgNuovoPaziente dialog(this);
	if (dialog.ShowModal() == wxID_OK) PopolaListaPazienti();
}


void MainFrame::PazienteSelezionato(wxListEvent& event)
{
	// Abilitazione voci menu e bottoni toolbar
	m_mainToolbar->EnableTool(wxID_OPEN, true);
	m_mainToolbar->EnableTool(wxID_DELETE, true);
	m_menuItemApri->Enable(true);
	m_menuItemElimina->Enable(true);

	long item = -1;
	item = m_listCtrlPazienti->GetNextItem(item,
	                                       wxLIST_NEXT_ALL,
	                                       wxLIST_MASK_TEXT|wxLIST_STATE_SELECTED); // use wxLIST_STATE_DONTCARE for all items
	if ( item != -1 ) {
		if (Paziente != NULL) {
			delete Paziente;
			Paziente = NULL;
		}
		Paziente = new ClassPaziente(_(m_listCtrlPazienti->GetItemText(item, cognome_index)), _(m_listCtrlPazienti->GetItemText(item, nome_index)), _(m_listCtrlPazienti->GetItemText(item, datanascita_index)), item);
	}

	//if ( item != -1 ) wxMessageBox ("Paziente Selezionato:\n" + m_listCtrlPazienti->GetItemText(item, cognome_index));
}


void MainFrame::PazienteDeselezionato(wxListEvent& event)
{
	// Disabilitazione voci menu e bottoni toolbar
	m_mainToolbar->EnableTool(wxID_OPEN, false);
	m_mainToolbar->EnableTool(wxID_DELETE, false);
	m_menuItemApri->Enable(false);
	m_menuItemElimina->Enable(false);

	if (Paziente != NULL) {
		delete Paziente;
		Paziente = NULL;
	}
}
void MainFrame::OnListCtrlRichiestaApertura(wxListEvent& event)
{
	if (Paziente != NULL) {
		FrmPaziente *FP = new FrmPaziente(this);
		FP->Show();
	}
}
