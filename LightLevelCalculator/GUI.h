#pragma once

#include "wx/wx.h"
#include "frame.h"
#include "wxImagePanel.h"

class GUI : public wxApp
{
public:
	GUI();
	~GUI();

private:
	Frame* frame = nullptr;
	wxImagePanel* bg = nullptr;
public:
	virtual bool OnInit();
};

