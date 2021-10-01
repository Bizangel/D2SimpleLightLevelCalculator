#pragma once

#include "wx/wx.h"

struct PanelText { /*Panel text to easily modify text*/
    wxFont font;
    wxPoint loc;
    wxString text;
    int id;
};

class wxImagePanel : public wxPanel
{
    wxBitmap image;
    PanelText** savedtext;
    int max_text;
public:
    wxImagePanel(wxFrame* parent, wxString file, wxBitmapType format, int max_n_texts);
    ~wxImagePanel();
    void paintEvent(wxPaintEvent& evt);
    void paintNow();

    void render(wxDC& dc);

    void draw_stored_text(wxDC& dc);

    void DrawText(wxFont textfont,wxString text,wxPoint loc,int id);

    void RemoveText(int id);

        // some useful events
        /*
         void mouseMoved(wxMouseEvent& event);
         void mouseDown(wxMouseEvent& event);
         void mouseWheelMoved(wxMouseEvent& event);
         void mouseReleased(wxMouseEvent& event);
         void rightClick(wxMouseEvent& event);
         void mouseLeftWindow(wxMouseEvent& event);
         void keyPressed(wxKeyEvent& event);
         void keyReleased(wxKeyEvent& event);
         */

    DECLARE_EVENT_TABLE()
};

