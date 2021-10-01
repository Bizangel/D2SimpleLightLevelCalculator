#include "GUI.h"


wxIMPLEMENT_APP(GUI);

GUI::GUI()
{
}

GUI::~GUI()
{
}

bool GUI::OnInit()
{
	wxInitAllImageHandlers();
	
	frame = new Frame;

	
	frame->Show();



	return true; // means that it was succesfully loading the GUI
}

