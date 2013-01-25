/*===================================================================================
                                 RobotVisionHelper
                                     Team 3167

     No requirement for distribution of wxWidgets libraries, source, or binaries.
                             (http://www.wxwidgets.org/)

===================================================================================*/

// File:  mainFrame.h
// Created:  1/22/2012
// Author:  K. Loux
// Description:  Contains the class functionality (event handlers, etc.) for the
//				 MainFrame class.  Uses wxWidgets for the GUI components.
// History:

// Standard C++ headers
#include <sstream>

// wxWidgets headers
#include <wx/clipbrd.h>

// Local headers
#include "mainFrame.h"
#include "robotVisionHelperApp.h"
#include "imagePanel.h"

const wxSize MainFrame::imageSize = wxSize(339, 276);

//==========================================================================
// Class:			MainFrame
// Function:		MainFrame
//
// Description:		Constructor for MainFrame class.  Initializes the form
//					and creates the controls, etc.
//
// Input Arguments:
//		None
//
// Output Arguments:
//		None
//
// Return Value:
//		None
//
//==========================================================================
MainFrame::MainFrame() : wxFrame(NULL, wxID_ANY, wxEmptyString, wxDefaultPosition,
								 wxDefaultSize, wxDEFAULT_FRAME_STYLE)
{
	originalImage = NULL;
	processedImage = NULL;
	
	DoLayout();
	SetProperties();
}

//==========================================================================
// Class:			MainFrame
// Function:		~MainFrame
//
// Description:		Destructor for MainFrame class.  Frees memory and
//					releases GUI object managers.
//
// Input Arguments:
//		None
//
// Output Arguments:
//		None
//
// Return Value:
//		None
//
//==========================================================================
MainFrame::~MainFrame()
{
	if (originalImage)
		delete originalImage;
	
	if (processedImage)
		delete processedImage;
}

//==========================================================================
// Class:			MainFrame
// Function:		DoLayout
//
// Description:		Creates sizers and controls and lays them out in the window.
//
// Input Arguments:
//		None
//
// Output Arguments:
//		None
//
// Return Value:
//		None
//
//==========================================================================
void MainFrame::DoLayout(void)
{
	// Create the top sizer, and on inside of it just to pad the borders a bit
	wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);
	topSizer->Add(mainSizer, 0, wxALL, 5);
	
	unsigned int padding(5);
	
	// Left side, original image box
	wxInitAllImageHandlers();
	originalImageDisplay = new wxImagePanel(this, wxID_ANY, wxEmptyString, wxBITMAP_TYPE_BMP);
	originalImageDisplay->SetSize(imageSize);
	mainSizer->Add(originalImageDisplay);
	
	// Add the controls in the middle
	wxBoxSizer* centerSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(centerSizer, 0, wxALL, padding);
	
	wxFlexGridSizer* offsetSizer = new wxFlexGridSizer(2, padding, padding);
	centerSizer->Add(offsetSizer, 0, wxALIGN_CENTER_HORIZONTAL);

	offsetSizer->Add(new wxStaticText(this, wxID_ANY, _T("X Offset")));
	offsetX = new wxTextCtrl(this, wxID_ANY, _T("39"), wxDefaultPosition,
		wxDefaultSize, 0, wxTextValidator(wxFILTER_NUMERIC));
	offsetSizer->Add(offsetX);
	
	offsetSizer->Add(new wxStaticText(this, wxID_ANY, _T("Y Offset")));
	offsetY = new wxTextCtrl(this, wxID_ANY, _T("99"), wxDefaultPosition,
		wxDefaultSize, 0, wxTextValidator(wxFILTER_NUMERIC));
	offsetSizer->Add(offsetY);
	
	centerSizer->AddSpacer(15);
	
	wxBoxSizer* colorSpaceSizer = new wxBoxSizer(wxHORIZONTAL);
	centerSizer->Add(colorSpaceSizer, 0, wxALIGN_CENTER_HORIZONTAL);
	rgb = new wxRadioButton(this, wxID_ANY, _T("RGB"));
	hsl = new wxRadioButton(this, wxID_ANY, _T("HSL"));
	colorSpaceSizer->Add(rgb);
	colorSpaceSizer->Add(hsl);
	
	centerSizer->AddSpacer(15);
	
	wxFlexGridSizer* rangeSizer = new wxFlexGridSizer(3, padding, padding);
	centerSizer->Add(rangeSizer);
	
	rangeSizer->AddSpacer(-1);
	rangeSizer->Add(new wxStaticText(this, wxID_ANY, _T("Min")));
	rangeSizer->Add(new wxStaticText(this, wxID_ANY, _T("Max")));
	
	value1 = new wxStaticText(this, wxID_ANY, _T("Hue"));
	rangeSizer->Add(value1);
	value1Low = new wxTextCtrl(this, ValueID, _T("0"));
	rangeSizer->Add(value1Low);
	value1High = new wxTextCtrl(this, ValueID, _T("255"));
	rangeSizer->Add(value1High);
	
	value2 = new wxStaticText(this, wxID_ANY, _T("Saturation"));
	rangeSizer->Add(value2);
	value2Low = new wxTextCtrl(this, ValueID, _T("0"));
	rangeSizer->Add(value2Low);
	value2High = new wxTextCtrl(this, ValueID, _T("255"));
	rangeSizer->Add(value2High);
	
	value3 = new wxStaticText(this, wxID_ANY, _T("Luminance"));
	rangeSizer->Add(value3);
	value3Low = new wxTextCtrl(this, ValueID, _T("0"));
	rangeSizer->Add(value3Low);
	value3High = new wxTextCtrl(this, ValueID, _T("255"));
	rangeSizer->Add(value3High);
	
	centerSizer->AddSpacer(15);
	
	updateButton = new wxButton(this, wxID_ANY, _T("Update From Clipboard"));
	centerSizer->Add(updateButton, 0, wxALIGN_CENTER_HORIZONTAL);
	
	// Right side, processed image box
	processedImageDisplay = new wxImagePanel(this, wxID_ANY, wxEmptyString, wxBITMAP_TYPE_BMP);
	processedImageDisplay->SetSize(imageSize);
	mainSizer->Add(processedImageDisplay);
	
	// Set defaults
	hsl->SetValue(true);

	// Required to make mouse events for the images propegate up to this frame
	originalImageDisplay->Connect(wxEVT_RIGHT_UP, wxMouseEventHandler(MainFrame::OnRightClick), NULL, this);

	// Assign sizers and resize the frame
	SetSizerAndFit(topSizer);
	SetAutoLayout(true);
	topSizer->SetSizeHints(this);
}

//==========================================================================
// Class:			MainFrame
// Function:		SetProperties
//
// Description:		Sets the window properties for this window.  Includes
//					title, frame size, and default fonts.
//
// Input Arguments:
//		None
//
// Output Arguments:
//		None
//
// Return Value:
//		None
//
//==========================================================================
void MainFrame::SetProperties(void)
{
	SetTitle(RobotVisionHelperApp::applicationTitle);
	SetName(RobotVisionHelperApp::applicationName);
	Center();

	// Allow dragging-and-dropping of files onto this window to open them
	//SetDropTarget(dynamic_cast<wxDropTarget*>(new DropTarget(*this)));
}

//==========================================================================
// Class:			MainFrame
// Function:		Event Table
//
// Description:		Links GUI events with event handler functions.
//
// Input Arguments:
//		None
//
// Output Arguments:
//		None
//
// Return Value:
//		None
//
//==========================================================================
BEGIN_EVENT_TABLE(MainFrame, wxFrame)
	// Buttons
	EVT_BUTTON(wxID_ANY,				MainFrame::OnUpdateButtonClicked)
 
	// Radio buttons
	EVT_RADIOBUTTON(wxID_ANY,			MainFrame::OnRadioChanged)
 
	// Text boxes
	EVT_TEXT(ValueID,					MainFrame::OnValueChanged)
END_EVENT_TABLE();

void MainFrame::OnUpdateButtonClicked(wxCommandEvent& WXUNUSED(event))
{
	if (!processedImage)
		processedImage = new wxImage();
	
	// Get image from clipboard
	wxBitmapDataObject clipboardData;
	wxTheClipboard->Open();
	if (wxTheClipboard->GetData(clipboardData))
	{
		if (originalImage)
			delete originalImage;
		
		originalImage = new wxImage(clipboardData.GetBitmap().ConvertToImage());
		long x, y;
		offsetX->GetValue().ToLong(&x);
		offsetY->GetValue().ToLong(&y);
		*originalImage = originalImage->GetSubImage(
			wxRect(x, y, imageSize.GetWidth(), imageSize.GetHeight()));
		originalImageDisplay->SetImage(*originalImage);
		
		ProcessImage();
	}
	wxTheClipboard->Close();
}

void MainFrame::OnValueChanged(wxCommandEvent& WXUNUSED(event))
{
	CheckLimits();
	ProcessImage();
}

void MainFrame::OnRadioChanged(wxCommandEvent& WXUNUSED(event))
{
	if (rgb->GetValue())
	{
		value1->SetLabel(_T("Red"));
		value2->SetLabel(_T("Green"));
		value3->SetLabel(_T("Blue"));
	}
	else
	{
		value1->SetLabel(_T("Hue"));
		value2->SetLabel(_T("Saturation"));
		value3->SetLabel(_T("Luminance"));
	}
	
	CheckLimits();
	ProcessImage();
}

void MainFrame::CheckLimits(void)
{
	long v;//, u;
	
	value1High->GetValue().ToLong(&v);
	if (v > 255)
		value1High->ChangeValue(_T("255"));
		
	value2High->GetValue().ToLong(&v);
	if (v > 255)
		value2High->ChangeValue(_T("255"));
	
	value3High->GetValue().ToLong(&v);
	if (v > 255)
		value3High->ChangeValue(_T("255"));
	
	/*value1High->GetValue().ToLong(&v);
	value1Low->GetValue().ToLong(&u);
	if (u < 0)
		value1Low->ChangeValue(_T("0"));
	else if (u > v)
		value1Low->ChangeValue(Stringify(v));
	
	value2High->GetValue().ToLong(&v);
	value2Low->GetValue().ToLong(&u);
	if (u < 0)
		value2Low->ChangeValue(_T("0"));
	else if (u > v)
		value2Low->ChangeValue(Stringify(v));
	
	value3High->GetValue().ToLong(&v);
	value3Low->GetValue().ToLong(&u);
	if (u < 0)
		value3Low->ChangeValue(_T("0"));
	else if (u > v)
		value3Low->ChangeValue(Stringify(v));*/
}

void MainFrame::ProcessImage(void)
{
	if (!originalImage)
		return;
	
	if (!originalImage->IsOk())
		return;

	*processedImage = *originalImage;
	
	long h1, h2, h3, l1, l2, l3;
	value1Low->GetValue().ToLong(&l1);
	value2Low->GetValue().ToLong(&l2);
	value3Low->GetValue().ToLong(&l3);
			
	value1High->GetValue().ToLong(&h1);
	value2High->GetValue().ToLong(&h2);
	value3High->GetValue().ToLong(&h3);
	
	int i, j, r, g, b, h, s, l;
	for (i = 0; i < processedImage->GetWidth(); i++)
	{
		for (j = 0; j < processedImage->GetHeight(); j++)
		{
			r = processedImage->GetRed(i, j);
			g = processedImage->GetGreen(i, j);
			b = processedImage->GetBlue(i, j);
			
			if (rgb->GetValue())
			{
				if (r > h1 || r < l1 ||
					g > h2 || g < l2 ||
					b > h3 || b < l3)
					processedImage->SetRGB(i, j, 0, 0, 0);// Black
				else
					processedImage->SetRGB(i, j, 255, 255, 255);// White
			}
			else
			{
				ConvertToHSL(r, g, b, h, s, l);
				if (h > h1 || h < l1 ||
					s > h2 || s < l2 ||
					l > h3 || l < l3)
					processedImage->SetRGB(i, j, 0, 0, 0);// Black
				else
					processedImage->SetRGB(i, j, 255, 255, 255);// White
			}
		}
	}
	
	processedImageDisplay->SetImage(*processedImage);
}

void MainFrame::ConvertToHSL(const int &r, const int &g, const int &b,
							 int &h, int &s, int &l)
{
	double max, min, c, rd(r / 255.0), gd(g / 255.0), bd(b / 255.0);
	if (rd >= gd && rd >= bd)
		max = rd;
	else if (gd >= bd)
		max = gd;
	else
		max = bd;
	if (rd <= gd && rd <= bd)
		min = rd;
	else if (gd <= bd)
		min = gd;
	else
		min = bd;
	
	l = int(255.0 * (max + min) * 0.5);
	
	c = max - min;

	if (c == 0)
	{
		h = 0;
		s = 0;
		return;
	}
	
	if (l < 0.5)
		s = int(c / (max + min) * 255.0);
	else
		s = int(c / (2 - max - min) * 255.0);

	double delR, delG, delB;
	delR = ((max - rd) / 6.0 + 0.5 * c) / c;
	delG = ((max - gd) / 6.0 + 0.5 * c) / c;
	delB = ((max - bd) / 6.0 + 0.5 * c) / c;
	
	if (max == rd)
		h = int(255.0 * (delB - delG));
	else if (max == gd)
		h = int(255.0 * (1.0 / 3.0 + delR - delB));
	else
		h = int(255.0 * (2.0 / 3.0 + delG - delR));

	while (h >= 255)
		h -= 255;
	while (h < 0)
		h += 255;

	/*wxString st;
	st.Printf("R: %i\nG: %i\nB: %i\n\nH: %i\nS: %i\nL: %i\n\nMax: %f\nMin: %f\nC: %f",r, g, b, h, s, l, max, min, c);
	wxMessageBox(st);*/
}

wxString MainFrame::Stringify(long l)
{
	std::stringstream ss;
	ss << l;

	return ss.str();
}

void MainFrame::OnRightClick(wxMouseEvent& event)
{
	if (!originalImage)
		return;

	if (!originalImage->IsOk())
		return;

	// Get the color under the pointer and set the range around this color
	int delta = 5;

	int r, g, b;
	r = originalImage->GetRed(event.GetX(), event.GetY());
	g = originalImage->GetGreen(event.GetX(), event.GetY());
	b = originalImage->GetBlue(event.GetX(), event.GetY());

	// We check limits here, too, because we're stricter than when people are typing
	if (hsl->GetValue())
	{
		int h, s, l;
		ConvertToHSL(r, g, b, h, s, l);

		if (h - delta < 0)
			value1Low->ChangeValue(_T("0"));
		else
			value1Low->ChangeValue(Stringify(h - delta));

		if (h + delta > 255)
			value1High->ChangeValue(_T("255"));
		else
			value1High->ChangeValue(Stringify(h + delta));

		if (s - delta < 0)
			value2Low->ChangeValue(_T("0"));
		else
			value2Low->ChangeValue(Stringify(s - delta));

		if (s + delta > 255)
			value2High->ChangeValue(_T("255"));
		else
			value2High->ChangeValue(Stringify(s + delta));

		if (l - delta < 0)
			value3Low->ChangeValue(_T("0"));
		else
			value3Low->ChangeValue(Stringify(l - delta));

		if (l + delta > 255)
			value3High->ChangeValue(_T("255"));
		else
			value3High->ChangeValue(Stringify(l + delta));
	}
	else
	{
		if (r - delta < 0)
			value1Low->ChangeValue(_T("0"));
		else
			value1Low->ChangeValue(Stringify(r - delta));

		if (r + delta > 255)
			value1High->ChangeValue(_T("255"));
		else
			value1High->ChangeValue(Stringify(r + delta));

		if (g - delta < 0)
			value2Low->ChangeValue(_T("0"));
		else
			value2Low->ChangeValue(Stringify(g - delta));

		if (g + delta > 255)
			value2High->ChangeValue(_T("255"));
		else
			value2High->ChangeValue(Stringify(g + delta));

		if (b - delta < 0)
			value3Low->ChangeValue(_T("0"));
		else
			value3Low->ChangeValue(Stringify(b - delta));

		if (b + delta > 255)
			value3High->ChangeValue(_T("255"));
		else
			value3High->ChangeValue(Stringify(b + delta));
	}

	ProcessImage();
}