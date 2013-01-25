/*===================================================================================
                                 RobotVisionHelper
                                     Team 3167

     No requirement for distribution of wxWidgets libraries, source, or binaries.
                             (http://www.wxwidgets.org/)

===================================================================================*/

// File:  imagePanel.h
// Created:  1/22/2012
// Author:  K. Loux
// Description:  Panel for displaying images
// History:

#ifndef _IMAGE_PANEL_H_
#define _IMAGE_PANEL_H_

// wxWidgets headers
#include <wx/wx.h>

class wxImagePanel : public wxPanel
{
private:
	wxBitmap image;
	
public:
	wxImagePanel(wxFrame* parent, wxWindowID id, wxString file, wxBitmapType format);
        
	void paintEvent(wxPaintEvent& event);
	void paintNow();
	
	void SetImage(const wxBitmap& _image);
	
	void render(wxDC& dc);
        
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

#endif// _IMAGE_PANEL_H_