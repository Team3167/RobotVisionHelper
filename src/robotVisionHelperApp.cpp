/*===================================================================================
                                 RobotVisionHelper
                                     Team 3167

     No requirement for distribution of wxWidgets libraries, source, or binaries.
                             (http://www.wxwidgets.org/)

===================================================================================*/

// File:  robotVisionHelperApp.cpp
// Created:  1/22/2012
// Author:  K. Loux
// Description:  The application class.
// History:

// wxWidgets headers
#include <wx/wx.h>

// Local headers
#include "robotVisionHelperApp.h"
#include "mainFrame.h"

// Implement the application (have wxWidgets set up the appropriate entry points, etc.)
IMPLEMENT_APP(RobotVisionHelperApp);

//==========================================================================
// Class:			RobotVisionHelperApp
// Function:		Constant Declarations
//
// Description:		Constant declarations for the RobotVisionHelperApp class.
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
const wxString RobotVisionHelperApp::applicationTitle = _T("Robot Vision Helper");
const wxString RobotVisionHelperApp::applicationName = _T("RobotVisionHelperApplication");
const wxString RobotVisionHelperApp::creator = _T("Kerry Loux");

//==========================================================================
// Class:			RobotVisionHelperApp
// Function:		OnInit
//
// Description:		Initializes the application window.
//
// Input Arguments:
//		None
//
// Output Arguments:
//		None
//
// Return Value:
//		bool = true for successful window initialization, false for error
//
//==========================================================================
bool RobotVisionHelperApp::OnInit()
{
	// Set the application's name and the vendor's name
	SetAppName(applicationName);
	SetVendorName(creator);

	// Create the MainFrame object - this is the parent for all other objects
	mainFrame = new MainFrame();

	// Make sure the MainFrame was successfully created
	if (mainFrame == NULL)
		return false;

	// Make the window visible
	mainFrame->Show(true);

	// Bring the window to the top
	//SetTopWindow(mainFrame);

	return true;
}