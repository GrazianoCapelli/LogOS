/**
 * globals.h
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

#include <list>
#include <wx/wx.h>
#include <wx/filename.h>


// --------------------- SISTEMA -----------------------------

extern wxString DirChar;
extern wxString VersionName;	// La versione del software

// --------------------- PAZIENTI -----------------------------


struct Report
{
	wxString NameFile;
	wxString Date;
	wxString Time;
	wxString ExerciseType;
	wxString Type;
	wxString Typelist;
    wxString Flags;
	wxString ExpVal;
	wxString ExpUm;
	wxString Numitems;
	wxString EsitoPercent;
	wxString FilterType1;
	wxString FilterType2;
	wxString FilterType3;
	wxString Filter1;
	wxString Filter2;
	wxString Filter3;
	wxString Validation;		// Metodo di validazione
	wxString TextColorscheme;	// Schema di colori proiettore
	wxString TextCase;			// Maiuscolo o minuscolo
	wxString TextSize;			// Grandezza carattere
	wxString Mask;					// Mascheramento
	wxString Forewarning;			// Preavviso
};


class ClassPaziente
{
public:
	ClassPaziente(const wxString& cognome, const wxString& nome, const wxString& natoil, const long listitem);
	~ClassPaziente();
	
	void LoadReportList();
	
	wxString Cognome;
	wxString Nome;
	wxString DataDiNascita;
	wxString CartellaDiLavoro;
	
	std::list<Report> ReportList;
	Report *Base_per_nuovo_esercizio;		// Indica dove prendere le preimpostazione per il nuovo esercizio
	
	long item;
};


extern ClassPaziente *Paziente;


// --------------------- LISTE ED ITEM -----------------------------


// Definizione elemento ITEM
struct Item {
	wxString Value;
	int NumSillabe;
};

// Definizione LISTA
struct List {
	wxString Name;
	wxString FileName;
	std::list<Item> ItemList;
};

// Definizione della lista delle liste
extern std::list<List> ListOfLists;				// La lista contenente tutte le liste disponibili;
extern std::list<Item> ItemListUnfiltered;		// Gli item selezionati;
extern std::list<Item> ItemListFiltered;		// Gli item selezionati e filtrati;

extern int MinNumSillabe ;	// Numero di sillabe Minimo e Massimo della lista filtrata
extern int MaxNumSillabe ;

void LoadLists ();
void UnloadLists ();



// --------------------- FILTRI -----------------------------

class Filter
{
public:
	std::list<wxString> FilterList;
	bool Enabled;
	wxString FilterType;
	bool Check(wxString ItemString);
	void AddFilter (wxString SubStr);
	void AddFilters (wxString StrFilters);
	void ClearFilters();
};

extern Filter FilterList1;
extern Filter FilterList2;
extern Filter FilterList3;

void MakeFilteredList();



// --------------------- Variabili Proiettore -----------------------------

extern int 		Proj_Text_Size;
extern bool 	Proj_Preavviso;
extern bool 	Proj_Mascheramento;
extern int 		Proj_Text_Maiuscolo;
extern int 		Proj_Text_Colori;
extern double 	Proj_Esposizione;
extern int 		Proj_EsposizioneUM;
extern int 		Proj_VerificaRisposta;

struct ProjectionItem {
	wxString Value;
	int NumSillabe;
	
	wxString Answer;
	bool CorrectAnswer;
	bool Projected;
	double exposureTime;
};

extern std::list<ProjectionItem> ProjectionList;		// La lista delle proiezioni;

void InitProjector(int NumItems);