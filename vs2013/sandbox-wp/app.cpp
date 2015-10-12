#include "pch.h"
#include "App.h"

#include <ppltasks.h>
#include "sani/platform/file/file_system.hpp"
#include "sani/platform/file/file_stream.hpp"
using namespace sandbox_wp;

using namespace concurrency;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::UI::Core;
using namespace Windows::UI::Input;
using namespace Windows::System;
using namespace Windows::Foundation;
using namespace Windows::Graphics::Display;

// The main function is only used to initialize our IFrameworkView class.
[Platform::MTAThread]
int main(Platform::Array<Platform::String^>^)
{
	using namespace sani::io;
	FileSystem fs;
	const std::string path("test.txt");
	FileStream* stream = nullptr;
	if (fs.fileExists(path)) {
		fs.openFile(path, Filemode::Read, &stream);
		std::string contents = fs.getFileDataString(path);
		assert(contents.size());
	}
	auto direct3DApplicationSource = ref new Direct3DApplicationSource();
	CoreApplication::Run(direct3DApplicationSource);
	return 0;
}

IFrameworkView^ Direct3DApplicationSource::CreateView()
{
	return ref new App();
}

App::App() 
{
}

// The first method called when the IFrameworkView is being created.
void App::Initialize(CoreApplicationView^ applicationView)
{

}

// Called when the CoreWindow object is created (or re-created).
void App::SetWindow(CoreWindow^ window)
{

}

// Initializes scene resources, or loads a previously saved app state.
void App::Load(Platform::String^ entryPoint)
{

}

// This method is called after the window becomes active.
void App::Run()
{

}

// Required for IFrameworkView.
// Terminate events do not cause Uninitialize to be called. It will be called if your IFrameworkView
// class is torn down while the app is in the foreground.
void App::Uninitialize()
{
}
