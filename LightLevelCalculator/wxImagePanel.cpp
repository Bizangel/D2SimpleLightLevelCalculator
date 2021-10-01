#include "wxImagePanel.h"

BEGIN_EVENT_TABLE(wxImagePanel, wxPanel)
// some useful events
/*
 EVT_MOTION(wxImagePanel::mouseMoved)
 EVT_LEFT_DOWN(wxImagePanel::mouseDown)
 EVT_LEFT_UP(wxImagePanel::mouseReleased)
 EVT_RIGHT_DOWN(wxImagePanel::rightClick)
 EVT_LEAVE_WINDOW(wxImagePanel::mouseLeftWindow)
 EVT_KEY_DOWN(wxImagePanel::keyPressed)
 EVT_KEY_UP(wxImagePanel::keyReleased)
 EVT_MOUSEWHEEL(wxImagePanel::mouseWheelMoved)
 */

 // catch paint events
EVT_PAINT(wxImagePanel::paintEvent)

END_EVENT_TABLE()


    // some useful events
    /*
     void wxImagePanel::mouseMoved(wxMouseEvent& event) {}
     void wxImagePanel::mouseDown(wxMouseEvent& event) {}
     void wxImagePanel::mouseWheelMoved(wxMouseEvent& event) {}
     void wxImagePanel::mouseReleased(wxMouseEvent& event) {}
     void wxImagePanel::rightClick(wxMouseEvent& event) {}
     void wxImagePanel::mouseLeftWindow(wxMouseEvent& event) {}
     void wxImagePanel::keyPressed(wxKeyEvent& event) {}
     void wxImagePanel::keyReleased(wxKeyEvent& event) {}
     */

    wxImagePanel::wxImagePanel(wxFrame* parent, wxString file, wxBitmapType format,int max_n_texts) : //constructor
    wxPanel(parent,-1,wxDefaultPosition)
{
    max_text = max_n_texts;
    // load the file... ideally add a check to see if loading was successful
    image.LoadFile(file, format);

    //create texts
    savedtext = new PanelText*[max_text];
    for (int i=0; i < max_text; i++)
        savedtext[i] = nullptr;



}

/*
 * Called by the system of by wxWidgets when the panel needs
 * to be redrawn. You can also trigger this call by
 * calling Refresh()/Update().
 */

void wxImagePanel::paintEvent(wxPaintEvent& evt)
{
    // depending on your system you may need to look at double-buffered dcs
    wxPaintDC dc(this);
    render(dc);
    draw_stored_text(dc);
}

/*
 * Alternatively, you can use a clientDC to paint on the panel
 * at any time. Using this generally does not free you from
 * catching paint events, since it is possible that e.g. the window
 * manager throws away your drawing when the window comes to the
 * background, and expects you will redraw it when the window comes
 * back (by sending a paint event).
 */
void wxImagePanel::paintNow()
{
    // depending on your system you may need to look at double-buffered dcs
    wxClientDC dc(this);
    render(dc);
    draw_stored_text(dc);
}

/*
 * Here we do the actual rendering. I put it in a separate
 * method so that it can work no matter what type of DC
 * (e.g. wxPaintDC or wxClientDC) is used.
 */
void wxImagePanel::render(wxDC& dc)
{
    dc.DrawBitmap(image, 0, 0, false);
}

wxImagePanel::~wxImagePanel() {
    /* We need to delete all PanelText items*/
    for (int i=0; i < max_text; i++) {
        if (savedtext[i] != nullptr) {
            delete savedtext[i]; //delete each element
        }
    }

    delete[] savedtext; //delete array
}

void wxImagePanel::draw_stored_text(wxDC& dc) {

    for (int i=0; i < max_text; i++) {
        if (savedtext[i] != nullptr) {
            dc.SetFont(savedtext[i]->font);
            dc.DrawText(savedtext[i]->text, savedtext[i]->loc);
        }
    }
}

void wxImagePanel::DrawText(wxFont textfont, wxString text, wxPoint loc, int id)
{
    /* ID MUST BE WITHIN 0 AND MAXTEXT-1*/
    if (savedtext[id] == nullptr) { //if doesn't exist
        PanelText* drawtext = new PanelText;   
        drawtext->font = textfont;
        drawtext->text = text;
        drawtext->loc = loc;
        savedtext[id] = drawtext;
    }
    else {
        savedtext[id]->font = textfont;
        savedtext[id]->text = text;
        savedtext[id]->loc = loc;
    }
}

void wxImagePanel::RemoveText(int id)
{
    /*Attemps to remove text at id*/
    if (savedtext[id] != nullptr) {
        delete savedtext[id];
        savedtext[id] = nullptr;
    }
}
