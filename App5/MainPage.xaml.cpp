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
float mouseLog[mouseLogSize][2];		// [0] = speed, [1] = speed


// PK Timer
typedef std::chrono::high_resolution_clock Clock;
auto LastEventTime = Clock::now();
auto ThisEventTime = Clock::now();
std::chrono::duration<double> ElapsedTime; 

// PK Screen dimensions
float ScreenY = 800; 
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
	ThisEventTime = Clock::now();
	ElapsedTime = ThisEventTime - LastEventTime;
	LastEventTime = Clock::now();

	Windows::UI::Xaml::Input::Pointer ^ptr = e->Pointer;

	if (ptr->PointerDeviceType == Windows::Devices::Input::PointerDeviceType::Mouse)
	{
		Windows::UI::Input::PointerPoint ^ptrPoint = e->GetCurrentPoint(nullptr);
		
		float mouseCurrentX = 0; 
		float mouseCurrentY = 0;

		mouseCurrentX = ptrPoint->Position.X; 
		mouseDeltaX = mouseCurrentX - mouseLastX; 

		MainPage::txtboxMouseX->Text = mouseCurrentX.ToString();
		MainPage::txtboxMouseXAccum->Text = mouseDeltaX.ToString();

		mouseLastX = mouseCurrentX;
			   
		Canvas->Invalidate();
	}



}



void App5::MainPage::Canvas_Draw(Microsoft::Graphics::Canvas::UI::Xaml::CanvasControl^ sender, Microsoft::Graphics::Canvas::UI::Xaml::CanvasDrawEventArgs^ args)
{

	std::chrono::duration<double>  DisplayTime = ThisEventTime - LastEventTime;
	MainPage::Timer->Text = DisplayTime.count().ToString();

	Windows::UI::Color LineCol{ 255, 255,0,0 };
	float X1 = mouseLastX;
	float Y1 = 100;
	float X2 = 200;
	float Y2 = 200;

	args->DrawingSession->DrawLine(X1, Y1, X2, Y2, LineCol);

	
	


}
