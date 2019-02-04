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
float mouseRealX = 0;
float mouseRealY = 0;
float mouseResetX = 0; 
float mouseResetY = 0;
const int mouseLogSize = 1000; 
float mouseLog[mouseLogSize][2];		// [0] = time, [1] = speed
int mouseLogCounter = 0; 

// PK Timer
typedef std::chrono::high_resolution_clock Clock;
auto GraphStartTime = Clock::now(); 
auto LastEventTime = Clock::now();
auto ThisEventTime = Clock::now();
std::chrono::duration<double> ElapsedTime; 
std::chrono::duration<double> GraphPlotTime;
double GraphTimeScalar = 100000 / 6; 
const int SamplingFrequency = 1000;					// 1,000,000 divided by SamplingFrequency = times per second
const auto TimeInterval = std::chrono::microseconds(SamplingFrequency); 

// PK Screen dimensions
float ScreenY = 800; 
float ScreenX = 2000; 
float ScreenXMid = ScreenX / 2;
float ScreenYMid = ScreenY / 2;
float WidthInSeconds = 4;
float WidthPerSecond = (ScreenX / WidthInSeconds);

// Mouse Tracking
int TrackingModeToggle = 0;

// Scaling for mouse
float ScaleX = 100; 
float ScaleY = 2; 

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
{
	InitializeComponent();



	
}



void App5::MainPage::Pointer_Moved(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	// Check whether tracking mode is on 
	if (TrackingModeToggle == 1)
	{

		// Check that we have a mouse event
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
			mouseRealX += mouseDeltaX; 

			// Set up clock
			ThisEventTime = Clock::now();
			ElapsedTime = ThisEventTime - LastEventTime;
			std::chrono::duration<double>  DisplayTime = ThisEventTime - LastEventTime;
			MainPage::Timer->Text = DisplayTime.count().ToString();

			if (ElapsedTime >= TimeInterval)				// Controls sampling rate
			{
				if (mouseLogCounter >= (mouseLogSize - 1))
				{
					// reset the counter to zero and clear the log
					mouseLogCounter = 0;
					GraphStartTime = Clock::now();
				}

				LastEventTime = Clock::now();							// Save the time when this was logged
				mouseLogCounter++;

				// Was -> mouseLog[mouseLogCounter][0] = mouseRealX;			// Store the mouse data
				GraphPlotTime = (LastEventTime - GraphStartTime) ;
				MainPage::txtboxGraphTimer->Text = GraphPlotTime.count().ToString();
				mouseLog[mouseLogCounter][0] = GraphPlotTime.count() * GraphTimeScalar;
				mouseLog[mouseLogCounter][1] = mouseDeltaX;
				MainPage::txtboxMouseDelta->Text = mouseDeltaX.ToString();
				mouseDeltaX = 0;

				// remember last position for next delta
				mouseLastX = mouseCurrentX;

				// reset mouse to centre of screen if it has moved outside of the bounds
				if (mouseCurrentX > 1500 || mouseCurrentX <500)
				{
					Windows::UI::Core::CoreWindow^ window = Windows::UI::Core::CoreWindow::GetForCurrentThread();
					window->PointerPosition = Point(ScreenXMid, ScreenYMid);
					mouseResetX = ScreenXMid;
					mouseLastX = mouseResetX; 
					mouseDeltaX = 0; 
					//mouseLog[mouseLogCounter][1] = mouseDeltaX;
				}

			}

			MainPage::txtboxMouseCurrent->Text = mouseCurrentX.ToString();
			MainPage::txtboxMouseLast->Text = mouseLastX.ToString();
			MainPage::txtboxMouseReal->Text = mouseRealX.ToString();
			MainPage::txtboxMouseReset->Text = mouseResetX.ToString();
			
			


			Canvas->Invalidate();				// redraw the graph
		}


	}

}



void App5::MainPage::Canvas_Draw(Microsoft::Graphics::Canvas::UI::Xaml::CanvasControl^ sender, Microsoft::Graphics::Canvas::UI::Xaml::CanvasDrawEventArgs^ args)
{
	// Set up the colours 
	Windows::UI::Color LineColBlue{ 255, 0,0,255 }; // blue 
	Windows::UI::Color LineColRed{ 255, 255,0,0 }; // red
	Windows::UI::Color LineColGreen{ 255, 0,255,0 }; // green

	// Set up the line variables
	float X1 = 0;
	float Y1 = ScreenYMid;
	float X2 = ScreenX;
	float Y2 = Y1;

	// Draw a horizontal axis across the middle of the screen 
	args->DrawingSession->DrawLine(X1, Y1, X2, Y2, LineColBlue);
	args->DrawingSession->DrawLine(500, 0, 500, ScreenY, LineColBlue);
	args->DrawingSession->DrawLine(1000, 0, 1000, ScreenY, LineColBlue);
	args->DrawingSession->DrawLine(1500, 0, 1500, ScreenY, LineColBlue);

	
	// Loop through the mousepoints and plot the line
	
	X2 = mouseLog[1][0];		// x-location
	Y2 = mouseLog[1][1];		// speed

	for (int iCounter = 1 ; iCounter < mouseLogSize; iCounter++)
	{
		X1 = mouseLog[iCounter][0];		// x-location
		Y1 = mouseLog[iCounter][1];		// speed

		if (iCounter != (mouseLogCounter + 1))
		{
			// draw the line
			args->DrawingSession->DrawLine((X1 / ScaleX), (Y1 / ScaleY) + ScreenYMid, (X2 / ScaleX) , (Y2 / ScaleY) + ScreenYMid, LineColRed);
		}
		if (iCounter == (mouseLogSize - 1))
		{
			// draw the line back to mouselog[0]
			X2 = mouseLog[1][0];
			Y2 = mouseLog[1][1];
			args->DrawingSession->DrawLine((X1 / ScaleX), (Y1 / ScaleY) + ScreenYMid, (X2 / ScaleX), (Y2 / ScaleY) + ScreenYMid, LineColGreen);
		}

		// don't draw the line if none of these are passed 
		

		X2 = X1;
		Y2 = Y1;
		
	}

	

}


void App5::MainPage::Tracking_Mode(Platform::Object^ sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ e)
{
	// toggle between tracking and non tracking 

	if (e->Key == Windows::System::VirtualKey::T)
	{
		if (TrackingModeToggle == 0)
		{
			TrackingModeToggle = 1; // on 
				// Move the mouse to the middle of the screen and switch off pointer
			Windows::UI::Core::CoreWindow^ window = Windows::UI::Core::CoreWindow::GetForCurrentThread();
			window->PointerPosition = Point(ScreenXMid, ScreenYMid);
			mouseResetX = ScreenXMid;
			mouseResetY = ScreenYMid;
			//window->PointerCursor = nullptr;
		}
		else
		{
			TrackingModeToggle = 0; // off
				// Move the mouse to the middle of the screen and enable the pointer
			Windows::UI::Core::CoreWindow^ window = Windows::UI::Core::CoreWindow::GetForCurrentThread();
			window->PointerPosition = Point(ScreenXMid, ScreenYMid);
			mouseResetX = ScreenXMid;
			mouseResetY = ScreenYMid;
			//window->PointerCursor = ref new Windows::UI::Core::CoreCursor(Windows::UI::Core::CoreCursorType::Arrow, 0);
		}
		
		MainPage::Messages->Text = "T key to toggle capture mode";
		
	}

}
