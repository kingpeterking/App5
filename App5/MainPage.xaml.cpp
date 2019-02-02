//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace App5;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;


//PK for mouse delta X and Y
float mouseLastX = 0;
float mouseLastY = 0;
float mouseDeltaX = 0;
float mouseDeltaY = 0;
const int mouseLogSize = 1000; 
float mouseLog[mouseLogSize][2];		// [0] = time, [1] = speed
int mouseLogCounter = 0; 


// PK Timer
typedef std::chrono::high_resolution_clock Clock;
auto LastEventTime = Clock::now();
auto ThisEventTime = Clock::now();
std::chrono::duration<double> ElapsedTime; 
int SamplingFrequency = 10;					// 1000 divided by 10 = 100 times per second
const auto TimeInterval = std::chrono::milliseconds(SamplingFrequency); 

// PK Screen dimensions
float ScreenY = 800; 
float ScreenYMid = ScreenY / 2; 
float ScreenX = 1000; 
float WidthInSeconds = 4; 
float WidthPerSecond = (ScreenX / WidthInSeconds);

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
{
	InitializeComponent();

}




void App5::MainPage::Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	txtboxMouseX->Text = "Hello, ";

}




void App5::MainPage::Pointer_Moved(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	// First check that we have a mouse event
	Windows::UI::Xaml::Input::Pointer ^ptr = e->Pointer;
	if (ptr->PointerDeviceType == Windows::Devices::Input::PointerDeviceType::Mouse)
	{
		// This accumulates all movements that happen within the timer interval and stores them in mouseLog
		// Check that whether enough time has passed to redraw the grapgh or just log the point 

		// Get the mouse movement
		// Currently just using X, but will change to use X and Y later
		Windows::UI::Input::PointerPoint ^ptrPoint = e->GetCurrentPoint(nullptr);
		float mouseCurrentX = 0;
		mouseCurrentX = ptrPoint->Position.X;
		mouseDeltaX += mouseCurrentX - mouseLastX;

		ThisEventTime = Clock::now();
		ElapsedTime = ThisEventTime - LastEventTime;
		std::chrono::duration<double>  DisplayTime = ThisEventTime - LastEventTime;
		MainPage::Timer->Text = DisplayTime.count().ToString();
		if (ElapsedTime >= TimeInterval)
		{
			if (mouseLogCounter >= mouseLogSize)
			{
				// reset the counter to zero and clear the log
				mouseLogCounter = 0; 
				// Add clearing the log
			}
			LastEventTime = Clock::now();							// Save the time when this was logged
			mouseLog[mouseLogCounter][0] = mouseLogCounter;			// Store the mouse delta
			mouseLog[mouseLogCounter][1] = mouseDeltaX;
			mouseLogCounter++;
			mouseDeltaX = 0; 
			
		}

		MainPage::txtboxMouseX->Text = mouseCurrentX.ToString();
		MainPage::txtboxMouseXAccum->Text = mouseDeltaX.ToString();

		mouseLastX = mouseCurrentX;
		Canvas->Invalidate();				// redraw the graph
	}



}



void App5::MainPage::Canvas_Draw(Microsoft::Graphics::Canvas::UI::Xaml::CanvasControl^ sender, Microsoft::Graphics::Canvas::UI::Xaml::CanvasDrawEventArgs^ args)
{
	// Draw a horizontal axis across the middle of the screen 
	Windows::UI::Color LineColBlue{ 255, 0,0,255 }; // blue 
	float X1 = 0;
	float Y1 = ScreenY / 2;
	float X2 = ScreenX;
	float Y2 = Y1;
	args->DrawingSession->DrawLine(X1, Y1, X2, Y2, LineColBlue);
	
	// Loop through the mousepoints and plot the line
	X1 = 0;
	Y1 = ScreenY / 2;
	Windows::UI::Color LineColRed{ 255, 255,0,0 }; // red
	for (int iCounter = 0 ; iCounter < mouseLogSize; iCounter++)
	{
		X1 = mouseLog[iCounter][0];		//time
		Y1 = mouseLog[iCounter][1];		// speed
		args->DrawingSession->DrawLine(X1, Y1 + ScreenYMid, X2, Y2 + ScreenYMid, LineColRed);
		X2 = X1;
		Y2 = Y1;
	}

	

}
