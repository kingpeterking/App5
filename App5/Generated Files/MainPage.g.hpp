﻿//------------------------------------------------------------------------------
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
//------------------------------------------------------------------------------
#include "pch.h"

#pragma warning(push)
#pragma warning(disable: 4100) // unreferenced formal parameter

#if defined _DEBUG && !defined DISABLE_XAML_GENERATED_BINDING_DEBUG_OUTPUT
extern "C" __declspec(dllimport) int __stdcall IsDebuggerPresent();
#endif

#include "MainPage.xaml.h"

void ::App5::MainPage::InitializeComponent()
{
    if (_contentLoaded)
    {
        return;
    }
    _contentLoaded = true;
    ::Windows::Foundation::Uri^ resourceLocator = ref new ::Windows::Foundation::Uri(L"ms-appx:///MainPage.xaml");
    ::Windows::UI::Xaml::Application::LoadComponent(this, resourceLocator, ::Windows::UI::Xaml::Controls::Primitives::ComponentResourceLocation::Application);
}

void ::App5::MainPage::Connect(int __connectionId, ::Platform::Object^ __target)
{
    switch (__connectionId)
    {
    case 2:
        {
            ::Windows::UI::Xaml::Controls::Grid^ element2 = safe_cast<::Windows::UI::Xaml::Controls::Grid^>(__target);
            (safe_cast<::Windows::UI::Xaml::Controls::Grid^>(element2))->PointerMoved += ref new ::Windows::UI::Xaml::Input::PointerEventHandler(this, (void (::App5::MainPage::*)
                (::Platform::Object^, ::Windows::UI::Xaml::Input::PointerRoutedEventArgs^))&MainPage::Pointer_Moved);
        }
        break;
    case 3:
        {
            this->txtboxMouseX = safe_cast<::Windows::UI::Xaml::Controls::TextBox^>(__target);
        }
        break;
    case 4:
        {
            this->txtboxMouseXAccum = safe_cast<::Windows::UI::Xaml::Controls::TextBox^>(__target);
        }
        break;
    case 5:
        {
            this->Test = safe_cast<::Windows::UI::Xaml::Controls::Button^>(__target);
            (safe_cast<::Windows::UI::Xaml::Controls::Button^>(this->Test))->Click += ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::App5::MainPage::*)
                (::Platform::Object^, ::Windows::UI::Xaml::RoutedEventArgs^))&MainPage::Button_Click);
        }
        break;
    case 6:
        {
            this->Canvas = safe_cast<::Microsoft::Graphics::Canvas::UI::Xaml::CanvasControl^>(__target);
            (safe_cast<::Microsoft::Graphics::Canvas::UI::Xaml::CanvasControl^>(this->Canvas))->Draw += ref new ::Windows::Foundation::TypedEventHandler<::Microsoft::Graphics::Canvas::UI::Xaml::CanvasControl^, ::Microsoft::Graphics::Canvas::UI::Xaml::CanvasDrawEventArgs^>(this, (void (::App5::MainPage::*)
                (::Microsoft::Graphics::Canvas::UI::Xaml::CanvasControl^, ::Microsoft::Graphics::Canvas::UI::Xaml::CanvasDrawEventArgs^))&MainPage::Canvas_Draw);
        }
        break;
    case 7:
        {
            this->Timer = safe_cast<::Windows::UI::Xaml::Controls::TextBox^>(__target);
        }
        break;
    }
    _contentLoaded = true;
}

::Windows::UI::Xaml::Markup::IComponentConnector^ ::App5::MainPage::GetBindingConnector(int __connectionId, ::Platform::Object^ __target)
{
    __connectionId;         // unreferenced
    __target;               // unreferenced
    return nullptr;
}

#pragma warning(pop)


