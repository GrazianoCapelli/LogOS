#ifndef DLGNUOVOPAZIENTE_H
#define DLGNUOVOPAZIENTE_H
#include "wxcrafter.h"


class DlgNuovoPaziente : public DialogNuovoPaziente
{
public:
	DlgNuovoPaziente(wxWindow* parent);
	virtual ~DlgNuovoPaziente();
	
protected:
	virtual void CreaPaziente(wxCommandEvent& event);
	virtual void PossoCrearlo(wxCommandEvent& event);
	virtual void PossoCrearlo(wxCalendarEvent& event);
	virtual void PossoCreareIlPaziente();
};
#endif // DLGNUOVOPAZIENTE_H
