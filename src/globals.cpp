/**
 * globals.cpp
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

#include <wx/app.h>
#include <wx/wx.h>
#include <wx/stdpaths.h>
#include <wx/dir.h>
#include <wx/textfile.h>
#include <wx/wx.h>
#include <list>
#include <wx/tokenzr.h>
#include <wx/filename.h>
#include "globals.h"


// --------------------- SISTEMA -----------------------------

#ifdef __UNIX__
    wxString DirChar = "/";
#endif
#ifdef __WINDOWS__
    wxString DirChar = "\\";
#endif

//wxString VersionName = "v1.2.0";		// La versione del software
wxString VersionName = "v1.2.1b_20190601";		// La versione del software


// --------------------- PAZIENTI -----------------------------

ClassPaziente::~ClassPaziente ()
{
	Cognome.Clear();
	Nome.Clear();
	DataDiNascita.Clear();
	CartellaDiLavoro.Clear();
}

ClassPaziente::ClassPaziente(const wxString& cognome, const wxString& nome, const wxString& natoil, const long listitem)
{
	Cognome = cognome;
	Cognome.Trim(false).Trim();
	
	Nome = nome;
	Nome.Trim(false).Trim();
	
	DataDiNascita = natoil;
	item = listitem;
	
	wxString DDN_GG = DataDiNascita.Left(2);
	wxString DDN_MM = DataDiNascita.Left(5).Right(2);
	wxString DDN_AAAA = DataDiNascita.Right(4);
	
	wxString path = wxStandardPaths::Get().GetExecutablePath();
    wxFileName::SplitPath(wxStandardPaths::Get().GetExecutablePath(),&path,NULL,NULL);
    //path.Truncate(path.size()-5);
    path.Append(DirChar);
	path.Append(_("Pazienti"));
    path.Append(DirChar);
	path = path + Cognome + "_" + Nome + "_" + DDN_AAAA + DDN_MM + DDN_GG;

	CartellaDiLavoro = path;
	
	LoadReportList();
}


void ClassPaziente::LoadReportList()
{
	Base_per_nuovo_esercizio = NULL;
	ReportList.clear();
	
	wxDir dir(CartellaDiLavoro);
	if ( !dir.IsOpened() ) {
		return;
	}
	//puts("Enumerating object files in current directory:");
	wxString filename;
	
	bool fcont = dir.GetFirst(&filename, "Tachistoscopio*.html", wxDIR_FILES);
	while ( fcont ) {
		// Apro il file
		wxTextFile TextFile;
		if (TextFile.Open(dir.GetNameWithSep() + filename)) {
			
			wxString HtmlFileText = "";
			wxString str;
			
			for ( str = TextFile.GetFirstLine(); !TextFile.Eof(); str = TextFile.GetNextLine())
			{
				HtmlFileText.append(str);
			}
			
			Report NewReport;
			NewReport.NameFile = dir.GetNameWithSep() + filename;		// Nome File
			wxString st;
			std::list<Report>::iterator ListOfReport_iter;
			
			if (HtmlFileText.Find("<!-- /typeex -->") != wxNOT_FOUND) // Tipo di esercizio
			{
				st = HtmlFileText.Left(HtmlFileText.Find("<!-- /typeex -->"));
				NewReport.ExerciseType = st.Right(st.length() - st.Find("<!-- typeex -->") - 15);
			}
			
			if (HtmlFileText.Find("<!-- /date -->") != wxNOT_FOUND) // DATA
			{
				st = HtmlFileText.Left(HtmlFileText.Find("<!-- /date -->"));
				NewReport.Date = st.Right(st.length() - st.Find("<!-- date -->") - 13);
			}
			
			if (HtmlFileText.Find("<!-- /hour -->") != wxNOT_FOUND) // ORA
			{
				st = HtmlFileText.Left(HtmlFileText.Find("<!-- /hour -->"));
				NewReport.Time = st.Right(st.length() - st.Find("<!-- hour -->") - 13);
			}
			
			if (HtmlFileText.Find("<!-- /expval -->") != wxNOT_FOUND) // Esposizione
			{
				st = HtmlFileText.Left(HtmlFileText.Find("<!-- /expval -->"));
				NewReport.ExpVal = st.Right(st.length() - st.Find("<!-- expval -->") - 15);
			}
			
			if (HtmlFileText.Find("<!-- /expum -->") != wxNOT_FOUND) // Esposizione Unità di misura
			{
				st = HtmlFileText.Left(HtmlFileText.Find("<!-- /expum -->"));
				NewReport.ExpUm = st.Right(st.length() - st.Find("<!-- expum -->") - 14);
			}
			
			if (HtmlFileText.Find("<!-- /result -->") != wxNOT_FOUND) // Risultato
			{
				st = HtmlFileText.Left(HtmlFileText.Find("<!-- /result -->"));
				NewReport.EsitoPercent = st.Right(st.length() - st.Find("<!-- result -->") - 15);
			}
			
			if (HtmlFileText.Find("<!-- /types -->") != wxNOT_FOUND) // Gruppo esercizio liste
			{
				st = HtmlFileText.Left(HtmlFileText.Find("<!-- /types -->"));
				NewReport.Type = st.Right(st.length() - st.Find("<!-- types -->") - 14);
			}
			
			if (HtmlFileText.Find("<!-- /typelist -->") != wxNOT_FOUND) // Liste usate
			{
				st = HtmlFileText.Left(HtmlFileText.Find("<!-- /typelist -->"));
				NewReport.Typelist = st.Right(st.length() - st.Find("<!-- typelist -->") - 17);
			}
			
			if (HtmlFileText.Find("<!-- /numitems -->") != wxNOT_FOUND) // Numero di items
			{
				st = HtmlFileText.Left(HtmlFileText.Find("<!-- /numitems -->"));
				NewReport.Numitems = st.Right(st.length() - st.Find("<!-- numitems -->") - 17);
			}
            
            NewReport.Flags = "";
            if (HtmlFileText.Find("<!-- filter_type") != wxNOT_FOUND) // Flags: aggiunge una F se la lista è stata filtrata
			{
				NewReport.Flags.append("F");
			}
			
			if (HtmlFileText.Find("<!-- /filter_type1 -->") != wxNOT_FOUND) // Tipo filtro 1
			{
				st = HtmlFileText.Left(HtmlFileText.Find("<!-- /filter_type1 -->"));
				NewReport.FilterType1 = st.Right(st.length() - st.Find("<!-- filter_type1 -->") - 21);
			}
			
			if (HtmlFileText.Find("<!-- /filter_type2 -->") != wxNOT_FOUND) // Tipo filtro 2
			{
				st = HtmlFileText.Left(HtmlFileText.Find("<!-- /filter_type2 -->"));
				NewReport.FilterType2 = st.Right(st.length() - st.Find("<!-- filter_type2 -->") - 21);
			}
			
			if (HtmlFileText.Find("<!-- /filter_type3 -->") != wxNOT_FOUND) // Tipo filtro 3
			{
				st = HtmlFileText.Left(HtmlFileText.Find("<!-- /filter_type3 -->"));
				NewReport.FilterType3 = st.Right(st.length() - st.Find("<!-- filter_type3 -->") - 21);
			}
			
			if (HtmlFileText.Find("<!-- /filter_text1 -->") != wxNOT_FOUND) // Filtro 1
			{
				st = HtmlFileText.Left(HtmlFileText.Find("<!-- /filter_text1 -->"));
				NewReport.Filter1 = st.Right(st.length() - st.Find("<!-- filter_text1 -->") - 21);
			}
			
			if (HtmlFileText.Find("<!-- /filter_text2 -->") != wxNOT_FOUND) // Filtro 2
			{
				st = HtmlFileText.Left(HtmlFileText.Find("<!-- /filter_text2 -->"));
				NewReport.Filter2 = st.Right(st.length() - st.Find("<!-- filter_text2 -->") - 21);
			}
			
			if (HtmlFileText.Find("<!-- /filter_text3 -->") != wxNOT_FOUND) // Filtro 3
			{
				st = HtmlFileText.Left(HtmlFileText.Find("<!-- /filter_text3 -->"));
				NewReport.Filter3 = st.Right(st.length() - st.Find("<!-- filter_text3 -->") - 21);
			}
			
			if (HtmlFileText.Find("<!-- /validation -->") != wxNOT_FOUND) // Validazione
			{
				st = HtmlFileText.Left(HtmlFileText.Find("<!-- /validation -->"));
				NewReport.Validation = st.Right(st.length() - st.Find("<!-- validation -->") - 19);
			}
			
			if (HtmlFileText.Find("<!-- /colorscheme -->") != wxNOT_FOUND) // Schema colori
			{
				st = HtmlFileText.Left(HtmlFileText.Find("<!-- /colorscheme -->"));
				NewReport.TextColorscheme = st.Right(st.length() - st.Find("<!-- colorscheme -->") - 20);
			}
			
			if (HtmlFileText.Find("<!-- /textcase -->") != wxNOT_FOUND) // Maiuscolo - Minuscolo
			{
				st = HtmlFileText.Left(HtmlFileText.Find("<!-- /textcase -->"));
				NewReport.TextCase = st.Right(st.length() - st.Find("<!-- textcase -->") - 17);
			}
			
			if (HtmlFileText.Find("<!-- /textsize -->") != wxNOT_FOUND) // Dimensione testo
			{
				st = HtmlFileText.Left(HtmlFileText.Find("<!-- /textsize -->"));
				NewReport.TextSize = st.Right(st.length() - st.Find("<!-- textsize -->") - 17);
			}
			
			if (HtmlFileText.Find("<!-- /mask -->") != wxNOT_FOUND) // Mascheramento
			{
				st = HtmlFileText.Left(HtmlFileText.Find("<!-- /mask -->"));
				NewReport.Mask = st.Right(st.length() - st.Find("<!-- mask -->") - 13);
			}
			//if (HtmlFileText.Find("<!-- mask -->") != wxNOT_FOUND) NewReport.Mask = true;	// Mascheramento
			//else NewReport.Mask = false;
			
			if (HtmlFileText.Find("<!-- /forewarning -->") != wxNOT_FOUND) // Dimensione testo
			{
				st = HtmlFileText.Left(HtmlFileText.Find("<!-- /forewarning -->"));
				NewReport.Forewarning = st.Right(st.length() - st.Find("<!-- forewarning -->") - 20);
			}
			//if (HtmlFileText.Find("<!-- forewarning -->") != wxNOT_FOUND) NewReport.Forewarning = true;		// Preavviso
			//else NewReport.Forewarning = false;
			
			// Finiscimi !! manca l'inserimento ordinato;
			
			for (ListOfReport_iter = ReportList.begin(); (ListOfReport_iter != ReportList.end()) && (ListOfReport_iter->NameFile < NewReport.NameFile); ListOfReport_iter++);
			ReportList.insert(ListOfReport_iter, NewReport);
			//ReportList.push_front(NewReport);
			
		}
		fcont = dir.GetNext(&filename);
	}
}


ClassPaziente *Paziente;


// --------------------- LISTE ED ITEM -----------------------------


std::list<List> ListOfLists;				// La lista contenente tutte le liste disponibili;
std::list<Item> ItemListUnfiltered;			// Gli item selezionati;
std::list<Item> ItemListFiltered;			// Gli item selezionati e filtrati;

int MinNumSillabe;	// Numero di sillabe Minimo e Massimo della lista filtrata;
int MaxNumSillabe;

void LoadLists ()
{	
	// Legge le sottocartelle della cartella Liste

	wxString path = wxStandardPaths::Get().GetExecutablePath();
    wxFileName::SplitPath(wxStandardPaths::Get().GetExecutablePath(),&path,NULL,NULL);
    //path.Truncate(path.size()-5);
    path.Append(DirChar);
	path.Append(_("Liste"));
    path.Append(DirChar);

	wxDir ddir(path);
	if ( !ddir.IsOpened() ) {
		return;
	}
	//puts("Enumerating object files in current directory:");
	wxString dfilename;
	bool cont = ddir.GetFirst(&dfilename, wxEmptyString, wxDIR_DEFAULT);
	while ( cont ) {
		
		// Sfoglio i files e creo una lista per ogni file
		
		wxString filepath = ddir.GetName();
		filepath.Append(DirChar);
		filepath.Append(dfilename.c_str());
		wxDir dir(filepath);
		if ( !dir.IsOpened() ) {
			return;
		}
		//puts("Enumerating object files in current directory:");
		wxString filename;
		bool fcont = dir.GetFirst(&filename, wxEmptyString,wxDIR_FILES);
		while ( fcont ) {
			// Apro il file
			wxTextFile TextFile;
			if (TextFile.Open(dir.GetNameWithSep() + filename)) {
			
				//m_checkListBoxListe->Append(filename.c_str());
				
				// TODO: Allocare e riempire le liste!
				
				List NewList;
				NewList.Name = filename;
				NewList.FileName = dir.GetName();
				NewList.FileName.Append(DirChar);
				NewList.FileName.Append(filename.c_str());
				ListOfLists.push_front(NewList);
				
				int numsillabe = 0;	// numero di sillabe impostato;
				std::list<List>::iterator list_iter = ListOfLists.begin();
				
				
				wxString str;
				// Tutte le linee tranne l'ultima;
				for ( str = TextFile.GetFirstLine().Trim(false).Trim().MakeLower(); !TextFile.Eof(); str = TextFile.GetNextLine().Trim(false).Trim().MakeLower())
				{
					if ((str != "") && (str[0] != '#'))
					{
						wxString StrLN = str;
						wxStringTokenizer ItemTokenizer(StrLN," ,;:.", wxTOKEN_STRTOK);
		
						while ( ItemTokenizer.HasMoreTokens() )
						{
							wxString token = ItemTokenizer.GetNextToken();
		
							if (token.IsNumber()) {
								long tolong;
								if (token.ToLong(&tolong)) {
									numsillabe = tolong;
								}
							} else {
								Item NewItem;
								NewItem.NumSillabe = numsillabe;
								NewItem.Value = token;
								list_iter->ItemList.push_back(NewItem);
							}
						}
					}
				}
				
				//+last line
				if ((str != "") && (str[0] != '#'))
				{
					wxString StrLN = str;
					wxStringTokenizer ItemTokenizer(StrLN," ,", wxTOKEN_STRTOK);
	
					while ( ItemTokenizer.HasMoreTokens() )
					{
						wxString token = ItemTokenizer.GetNextToken();
	
						if (token.IsNumber()) {
							long tolong;
							if (token.ToLong(&tolong)) {
								numsillabe = tolong;
							}
						} else {
							Item NewItem;
							NewItem.NumSillabe = numsillabe;
							NewItem.Value = token;
							list_iter->ItemList.push_back(NewItem);
						}
					}
				}
			}
			
			//printf("%s\n", filename.c_str());
			fcont = dir.GetNext(&filename);
		}
		cont = ddir.GetNext(&dfilename);
	}
}

void UnloadLists ()
{
	ListOfLists.clear();
}



// --------------------- FILTRI -----------------------------

Filter FilterList1;
Filter FilterList2;
Filter FilterList3;


// Aggiunge un filtro alla lista dei filtri;
void Filter::AddFilter (wxString SubStr)
{
	FilterList.push_back(SubStr);
	Enabled = true;
}


// Aggiunge una serie di filtri alla lista dei filtri;
void Filter::AddFilters (wxString StrFilters)
{
	if (StrFilters != "")
	{
		wxString StrFT = StrFilters;
		wxStringTokenizer FilterTokenizer(StrFT," ,.;-+:&|", wxTOKEN_STRTOK);
		
		while ( FilterTokenizer.HasMoreTokens() )
		{
			wxString token = FilterTokenizer.GetNextToken();
			AddFilter(token);
		}
	}
}

// Azzera la lista dei filtri;
void Filter::ClearFilters()
{
	Enabled = false;
	FilterList.clear();
}



bool Filter::Check(wxString ItemString)
{
	bool Result = true;
	
	if (!Enabled || FilterList.empty())
	{
		return Result;
	}
	else
	{
		if (FilterType == "Inizia per")   // FILTRO: INIZIA PER
		{
			Result = false;
			for (std::list<wxString>::iterator filter_iter = FilterList.begin(); filter_iter != FilterList.end(); ++filter_iter)
			{
				if (ItemString.Find(*filter_iter) == 0) Result = true;
			}
		}
		
		if (FilterType == "Non inizia per")   // FILTRO: NON INIZIA PER
		{
			Result = true;
			for (std::list<wxString>::iterator filter_iter = FilterList.begin(); filter_iter != FilterList.end(); ++filter_iter)
			{
				if (ItemString.Find(*filter_iter) == 0) Result = false;
			}
		}
		
		if (FilterType == "Contiene (AND)")   // FILTRO: CONTIENE (AND)
		{
			Result = true;
			for (std::list<wxString>::iterator filter_iter = FilterList.begin(); filter_iter != FilterList.end(); ++filter_iter)
			{
				if (ItemString.Find(*filter_iter) == wxNOT_FOUND) Result = false;
			}
		}
		
		if (FilterType == "Contiene (OR)")   // FILTRO: CONTIENE (OR)
		{
			Result = false;
			for (std::list<wxString>::iterator filter_iter = FilterList.begin(); filter_iter != FilterList.end(); ++filter_iter)
			{
				if (ItemString.Find(*filter_iter) != wxNOT_FOUND) Result = true;
			}
		}
		
		if (FilterType == "Non contiene")   // FILTRO: NON CONTIENE
		{
			Result = true;
			for (std::list<wxString>::iterator filter_iter = FilterList.begin(); filter_iter != FilterList.end(); ++filter_iter)
			{
				if (ItemString.Find(*filter_iter) != wxNOT_FOUND) Result = false;
			}
		}
	}
	return Result;
}




void MakeFilteredList()
{
	ItemListFiltered.clear();
	ItemListFiltered.assign(ItemListUnfiltered.begin(), ItemListUnfiltered.end());
	
	// Eseguo il filtraggio
	
	if(!ItemListFiltered.empty())
	{
		for (std::list<Item>::iterator filter_iter = ItemListFiltered.begin(); filter_iter != ItemListFiltered.end(); ) {
			if (!FilterList1.Check(filter_iter->Value) || (!FilterList2.Check(filter_iter->Value)) || (!FilterList3.Check(filter_iter->Value)))
			{
				filter_iter = ItemListFiltered.erase(filter_iter);
			}
			else
			{
				++filter_iter;
			}
		}
	}	
	
	// Inventario del numero di sillabe
	
	MinNumSillabe = 100;
	MaxNumSillabe = 0;
	
	if(!ItemListFiltered.empty()) {
		for (std::list<Item>::iterator filter_iter = ItemListFiltered.begin(); filter_iter != ItemListFiltered.end(); ++filter_iter ) {
			if (MaxNumSillabe < filter_iter->NumSillabe) MaxNumSillabe = filter_iter->NumSillabe;
			if (MinNumSillabe > filter_iter->NumSillabe) MinNumSillabe = filter_iter->NumSillabe;
		}
	}
}


// --------------------- Variabili Proiettore -----------------------------

int Proj_Text_Size = 40;
bool Proj_Preavviso = true;
bool Proj_Mascheramento = false;
int Proj_Text_Maiuscolo = 0;
int Proj_Text_Colori = 0;
double Proj_Esposizione;
int Proj_EsposizioneUM;		// 0 = Millisecondi;	1 = Sillabe al secondo;
int Proj_VerificaRisposta;	// 0 = Reinserimento;	1 = Pulsanti Sì/No;


std::list<ProjectionItem> ProjectionList;		// La lista delle proiezioni;


void InitProjector(int NumItems)
{
	std::list<Item> TempItemListFiltered;
	TempItemListFiltered.assign(ItemListFiltered.begin(), ItemListFiltered.end());
	ProjectionList.clear();
	
	srand(time(NULL));
	
	for (int i = 0; i < NumItems; i++) {
		int rn = rand() % (int)(TempItemListFiltered.size());
		std::list<Item>::iterator li = TempItemListFiltered.begin();
		for (int ii = 0; ii < rn; ii++, li++);
		ProjectionItem TPI;
		if (Proj_Text_Maiuscolo > 0) TPI.Value = li->Value.MakeUpper();
		else TPI.Value = li->Value.MakeLower();
		TPI.NumSillabe = li->NumSillabe;
		TPI.Projected = false;
		TPI.Answer = "";
		TPI.CorrectAnswer = false;
		TPI.exposureTime = Proj_EsposizioneUM ? (int)(1000*(double)TPI.NumSillabe/Proj_Esposizione) : (int)(Proj_Esposizione);
		TempItemListFiltered.erase(li);		// Cancello l'elemento dalla lista da cui "pesco"
		ProjectionList.push_back(TPI);		// Inserisco la proiezione "pescata" nella lista
	}
	
	TempItemListFiltered.clear();
}
