/*===================================================================================
                                 RobotVisionHelper
                                     Team 3167

     No requirement for distribution of wxWidgets libraries, source, or binaries.
                             (http://www.wxwidgets.org/)

===================================================================================*/

// File:  robotVisionHelperApp.h
// Created:  1/22/2012
// Author:  K. Loux
// Description:  The application class.
// History:

#ifndef _ROBOT_VISION_HELPER_APP_H_
#define _ROBOT_VISION_HELPER_APP_H_

// wxWidgets headers
#include <wx/wx.h>

// Local forward declarations
class MainFrame;

// The application class
class RobotVisionHelperApp : public wxApp
{
public:
	// Initialization function
	bool OnInit();

	// The name of the application
	static const wxString applicationTitle;// As displayed
	static const wxString applicationName;// Internal
	static const wxString creator;

private:
	// The main class for the application - this object is the parent for all other objects
	MainFrame *mainFrame;
};

// Declare the application object (have wxWidgets create the wxGetApp() function)
DECLARE_APP(RobotVisionHelperApp);

#endif// _ROBOT_VISION_HELPER_APP_H_