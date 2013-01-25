/*===================================================================================
                                 RobotVisionHelper
                                     Team 3167

     No requirement for distribution of wxWidgets libraries, source, or binaries.
                             (http://www.wxwidgets.org/)

===================================================================================*/

// File:  mainFrame.h
// Created:  1/22/2012
// Author:  K. Loux
// Description:  Main frame for the application.
// History:

#ifndef _MAIN_FRAME_H_
#define _MAIN_FRAME_H_

// wxWidgets headers
#include <wx/wx.h>

// Local forward declarations
class wxImagePanel;

// The main frame class
class MainFrame : public wxFrame
{
public:
	// Constructor
	MainFrame();

	// Destructor
	~MainFrame();

private:
	// Functions that do some of the frame initialization and control positioning
	void DoLayout(void);
	void SetProperties(void);
	
	static const wxSize imageSize;

	// Controls
	wxImagePanel* originalImageDisplay;
	wxImagePanel* processedImageDisplay;
	
	wxRadioButton* rgb;
	wxRadioButton* hsl;
	
	wxStaticText* value1;
	wxStaticText* value2;
	wxStaticText* value3;
	
	wxTextCtrl* value1Low;
	wxTextCtrl* value2Low;
	wxTextCtrl* value3Low;
	
	wxTextCtrl* value1High;
	wxTextCtrl* value2High;
	wxTextCtrl* value3High;
	
	wxTextCtrl* offsetX;
	wxTextCtrl* offsetY;
	
	wxButton* updateButton;
	
	// The images
	wxImage* originalImage;
	wxImage* processedImage;
	
	// Event handlers
	void OnUpdateButtonClicked(wxCommandEvent& event);
	void OnValueChanged(wxCommandEvent& event);
	void OnRadioChanged(wxCommandEvent& event);
	void OnRightClick(wxMouseEvent& event);
	
	// Event IDs
	enum EventID
	{
		ValueID = wxID_HIGHEST + 100
	};
	
	void ProcessImage(void);
	void CheckLimits(void);
	void ConvertToHSL(const int &r, const int &g, const int &b,
		int &h, int &s, int &l);
	wxString Stringify(long l);

	// For the event table
	DECLARE_EVENT_TABLE();
};

#endif// _MAIN_FRAME_H_