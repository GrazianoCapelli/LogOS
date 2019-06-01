#ifndef MAINFRAME_H
#define MAINFRAME_H
#include "wxcrafter.h"


class MainFrame : public MainFrameBaseClass
{
public:
	MainFrame(wxWindow* parent);
	virtual ~MainFrame();

	void PopolaListaPazienti();
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);

	long cognome_index;
	long nome_index;
	long datanascita_index;

protected:
	virtual void OnListCtrlRichiestaApertura(wxListEvent& event);
	virtual void PazienteDeselezionato(wxListEvent& event);
	virtual void PazienteSelezionato(wxListEvent& event);
	virtual void ApriPaziente(wxCommandEvent& event);
	virtual void EliminaPaziente(wxCommandEvent& event);
	virtual void NuovoPaziente(wxCommandEvent& event);
};
#endif // MAINFRAME_H
