/**
 * FrmReport.h
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
 
#ifndef FRMREPORT_H
#define FRMREPORT_H
#include "wxcrafter.h"


class FrmReport : public FrameReport
{
public:
	FrmReport(wxWindow* parent);
	virtual ~FrmReport();

	void LoadPage(const wxString& location);
protected:
	virtual void OnCloseClicked(wxCommandEvent& event);
};
#endif // FRMREPORT_H
