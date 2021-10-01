#pragma once

#include "wx/wx.h"
#include "wxImagePanel.h"
#include <math.h>

int const Npieces = 8;

class Frame : public wxFrame
{
public:
	
	Frame();
	~Frame();

	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);

private:
	DECLARE_EVENT_TABLE()
public:
	int count = 0;
	wxFont resultfont;
	
	wxButton* calculate_button = nullptr;
	
	//wxTextCtrl* debugbox = nullptr;
	
	
	wxTextCtrl** lightboxes = nullptr;
	wxImagePanel* bg = nullptr;
	
	void Calculate(wxCommandEvent& evt);

	void OnChar(wxKeyEvent& event);
};

