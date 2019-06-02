/**
 * MainFrame.h
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
