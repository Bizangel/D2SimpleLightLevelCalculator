#include "Frame.h"

BEGIN_EVENT_TABLE(Frame,wxFrame)
	EVT_MENU(wxID_ABOUT, Frame::OnAbout)
	EVT_MENU(wxID_EXIT, Frame::OnQuit)
END_EVENT_TABLE()

Frame::Frame() : wxFrame(nullptr, wxID_ANY,"Light Level Calculator", wxPoint(30, 30), wxSize(700, 600), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
	bg = new wxImagePanel(this, wxT("bg.jpg"), wxBITMAP_TYPE_JPEG,10); //place everything on top of background, background is like canvas

	
	wxFont font(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);
	wxFont lightfont(wxFontInfo(16).FaceName("Helvetica").Italic());
	resultfont = wxFont(wxFontInfo(18).FaceName("Helvetica").Bold());

	wxFont titlefont(wxFontInfo(18).Underlined().Bold());
	bg->DrawText(titlefont, "Input Light: ", wxPoint(150, 30), 8);

	wxString pieces[Npieces] = {"Kinetic","Energy","Heavy","Head","Arms","Chest","Legs","Class"};
	lightboxes = new wxTextCtrl* [Npieces];

	wxTextCtrl* lightbox;
	for (int i = 0; i < 8; i++) {
		if (i < 3) { //weapons
			lightbox = new wxTextCtrl(bg, 1000 + i, wxEmptyString, wxPoint(150, 100 + 100 * i), wxSize(100, 30 + 5));
			bg->DrawText(font, pieces[i], wxPoint(30, 100 + 100 * i), i);
		}
		else { //armor
			lightbox = new wxTextCtrl(bg, 1000 + i, wxEmptyString, wxPoint(400, 50 + 75 * (i-3)), wxSize(100, 30 + 5));
			bg->DrawText(font, pieces[i], wxPoint(520, 50 + 75 * (i-3)), i);	
		}

		lightbox->SetMaxLength(4);
		lightbox->SetFont(lightfont);
		lightbox->SetBackgroundColour(wxColour("lightgrey"));
		lightbox->Bind(wxEVT_KEY_DOWN, &Frame::OnChar, this);
		lightboxes[i] = lightbox;
	}

	
	

	
	calculate_button = new wxButton(bg, wxID_ANY, "Calculate!", wxPoint(275, 400), wxSize(100, 50));
	calculate_button->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Frame::Calculate, this);
	calculate_button->SetBackgroundColour(wxColour("grey"));
	//debugbox  = new wxTextCtrl(bg, wxID_ANY, "", wxPoint(400, 100), wxSize(300, 30), wxTE_RIGHT);
	
	SetIcon(wxIcon("ghosticon.ico", wxBITMAP_TYPE_ICO));
	/* MENU BAR AND STATUS BAR
	MENUBAR: ATOP MENU BAR File info... etc.
	STATUS BAR: STATUS BELOW WINDOW, SAYS STATUS "READY" AND STUFF.
	wxMenu* fileMenu = new wxMenu;
	wxMenu* helpMenu = new wxMenu;
	//helpMenu->Append(wxID_ABOUT, wxT("About...\tF1"), wxT("Show about dialog")); can add extra dialogue to display on status bar
	helpMenu->Append(wxID_ABOUT, wxT("&About...\tF1"));
	fileMenu->Append(wxID_EXIT, wxT("E&xit\tAlt-X"));
	wxMenuBar* menuBar = new wxMenuBar();
	menuBar->Append(fileMenu, wxT("File"));
	menuBar->Append(helpMenu, wxT("Help"));
	SetMenuBar(menuBar);
	CreateStatusBar(2);
	SetStatusText(wxT("Status bar default"));
	*/
}

Frame::~Frame()
{
	delete[] lightboxes; //no need to delete buttons individually, module does it
}

void Frame::OnQuit(wxCommandEvent& event)
{
	Close();
}

void Frame::OnAbout(wxCommandEvent& event)
{
	wxString msg;
	msg.Printf(wxT("Hello and welcome to Light Level Calculator!\n Just Simply Input your info, and the calculator will do the rest"));

	wxMessageBox(msg, wxT("About Minimal"), wxOK | wxICON_INFORMATION, this);

}

void Frame::Calculate(wxCommandEvent& evt)
{
	//wxMessageBox(wxT("This was called"), wxT("About Minimal"), wxOK | wxICON_INFORMATION, this);
	
	long numbers[Npieces] = {0,0,0,0,0,0,0,0};
	long x;
	for (int i = 0; i < Npieces; i++)
		if (lightboxes[i]->GetValue().ToLong(&x)) {
			numbers[i] = x;
		}

	double prom = 0;
	for (int i = 0; i < Npieces; i++)
		prom += numbers[i];

	prom = double(prom / 8);
	int light = double(ceil(prom)-prom) * 8;
	if (light == 0) {
		light = 8;
	}
	wxString lighttext1("LightLevel: %.3f");
	wxString lighttext2(", you require %d points for next level");
	lighttext1 = wxString::Format(lighttext1, prom);
	lighttext2 = wxString::Format(lighttext2, light);
	bg->DrawText(resultfont, lighttext1 + lighttext2,wxPoint(50,470),9);
	bg->paintNow(); //update
	evt.Skip();
}

void Frame::OnChar(wxKeyEvent& event)
{	
	/*ONLY ACCEPTS NUMPADS AND NUMKEYS*/
	int x = event.GetKeyCode();
	//int id = event.GetId() - 1000;
	if ((47 < x && x < 58) || x == 8 ||
		(323 < x && x < 334) ) { //if backspace or numbers, or numpad
			event.Skip();
	}
	//ignored if not a number or backspace
}

