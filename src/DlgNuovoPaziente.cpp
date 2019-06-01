#include "DlgNuovoPaziente.h"
#include "globals.h"
#include <wx/stdpaths.h>
#include <wx/dir.h>
#include <wx/filefn.h>
#include <wx/wx.h>


// delete all vowels from the string
bool ValidString(const wxString& original)
{
	bool bresult = false;
	wxString result;
	size_t len = original.length();
	result.Alloc(len);
	for ( size_t n = 0; n < len; n++ ) {
		if ( strchr("abcdefghijklmnopqrstuvwxyz-1234567890 ", tolower(original[n])) != NULL )
			result += original[n];
	}
	if (result == original) bresult = true;
	return bresult;
}


DlgNuovoPaziente::DlgNuovoPaziente(wxWindow* parent)
	: DialogNuovoPaziente(parent)
{
	m_calendarNatoIl->SetDateRange(wxDefaultDateTime, wxDateTime::Now().GetDateOnly());
}


DlgNuovoPaziente::~DlgNuovoPaziente()
{
}


void DlgNuovoPaziente::PossoCreareIlPaziente()
{
	bool posso = true;
	if (m_textCtrlNome->GetValue().Trim() == _("")) posso = false;
	if (!ValidString(m_textCtrlNome->GetValue())) posso = false;

	if (m_textCtrlCognome->GetValue().Trim() == _("")) posso = false;
	if (!ValidString(m_textCtrlCognome->GetValue())) posso = false;

	if (posso) {

		wxDateTime wxNOW = wxDateTime::Now();
		if (m_calendarNatoIl->GetDate().GetDateOnly() == wxNOW.Now().GetDateOnly()) posso = false;

		wxString path = wxStandardPaths::Get().GetExecutablePath();
        wxFileName::SplitPath(wxStandardPaths::Get().GetExecutablePath(),&path,NULL,NULL);
        //path.Truncate(path.size()-5);
        path.Append(DirChar);
        path.Append(_("Pazienti"));
        path.Append(DirChar);
		path = path + m_textCtrlCognome->GetValue().Trim(false).Trim() + "_" + _(m_textCtrlNome->GetValue().Trim(false).Trim()) + "_" + wxString::Format(wxT("%04i"), m_calendarNatoIl->GetDate().GetYear()) + wxString::Format(wxT("%02i"), (m_calendarNatoIl->GetDate().GetMonth()+1)) + wxString::Format(wxT("%02i"), m_calendarNatoIl->GetDate().GetDay());

		//m_staticTextEsistente->SetLabel(m_textCtrlCognome->GetValue().Trim(false).Trim() + "_" + _(m_textCtrlNome->GetValue().Trim(false).Trim()) + "_" + wxString::Format(wxT("%04i"), m_calendarNatoIl->GetDate().GetYear()) + wxString::Format(wxT("%02i"), (m_calendarNatoIl->GetDate().GetMonth()+1)) + wxString::Format(wxT("%02i"), m_calendarNatoIl->GetDate().GetDay()));

		if ( wxDirExists(path) ) {
			posso = false;
			m_staticTextEsistente->SetLabel("Esistente");
		} else {
			m_staticTextEsistente->SetLabel("");
		}
	}


	m_buttonCrea->Enable(posso);
}


void DlgNuovoPaziente::PossoCrearlo(wxCalendarEvent& event)
{
	PossoCreareIlPaziente();
}


void DlgNuovoPaziente::PossoCrearlo(wxCommandEvent& event)
{
	PossoCreareIlPaziente();
}


void DlgNuovoPaziente::CreaPaziente(wxCommandEvent& event)
{
	wxString path = wxStandardPaths::Get().GetExecutablePath();
    wxFileName::SplitPath(wxStandardPaths::Get().GetExecutablePath(),&path,NULL,NULL);
    //path.Truncate(path.size()-5);
    path.Append(DirChar);
	path.Append(_("Pazienti"));
    path.Append(DirChar);
	path = path + m_textCtrlCognome->GetValue().Trim(false).Trim() + "_" + _(m_textCtrlNome->GetValue().Trim(false).Trim()) + "_" + wxString::Format(wxT("%04i"), m_calendarNatoIl->GetDate().GetYear()) + wxString::Format(wxT("%02i"), (m_calendarNatoIl->GetDate().GetMonth()+1)) + wxString::Format(wxT("%02i"), m_calendarNatoIl->GetDate().GetDay());

	//m_staticTextEsistente->SetLabel(m_textCtrlCognome->GetValue().Trim(false).Trim() + "_" + _(m_textCtrlNome->GetValue().Trim(false).Trim()) + "_" + wxString::Format(wxT("%04i"), m_calendarNatoIl->GetDate().GetYear()) + wxString::Format(wxT("%02i"), (m_calendarNatoIl->GetDate().GetMonth()+1)) + wxString::Format(wxT("%02i"), m_calendarNatoIl->GetDate().GetDay()));

	if ( !(wxDir::Make(path, wxPATH_MKDIR_FULL|wxS_DIR_DEFAULT)) ) {
		wxMessageBox(_T("Non è stato possibile creare\nla cartella paziente"), "Errore", wxICON_ERROR);
		EndModal(wxID_CANCEL);
	} else {
		//wxMessageBox ("La cartella del paziente è:\n" + path);
		EndModal(wxID_OK);
	}
}
