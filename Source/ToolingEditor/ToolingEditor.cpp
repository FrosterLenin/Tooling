// Copyright Epic Games, Inc. All Rights Reserved.

#include "ToolingEditor.h"
#include "SMyTool.h"
//#include "Framework/Application/SlateApplication.h"

void FToolingEditorModule::StartupModule()
{
    // This code will execute after your module is loaded into memory; 
    //the exact timing is specified in the .uplugin file per-module

    TSharedRef<SWindow> window = SNew(SWindow)
        .Title(FText::FromString("My Tool"))
        .ClientSize(FVector2D(400, 300))
        [
            SNew(SMyTool) // add my custom widget to the window of the module
        ];
    // adding to the slate application (the application in which widgets resides in the editor) the window
    FSlateApplication::Get().AddWindow(window);
    UE_LOG(LogTemp, Warning, TEXT("ToolingEditor module has started!"));
}

void FToolingEditorModule::ShutdownModule()
{
    // This function may be called during shutdown to clean up your module.  
    // For modules that support dynamic reloading
    // we call this function before unloading the module
    UE_LOG(LogTemp, Warning, TEXT("ToolingEditor module has shut down"));
}

// Implement the module class using the IMPLEMENT_MODULE macro
// which takes the class name and the module name as parameters
// so now it appears in the list of loaded modules
//  and can be used by the engine and other modules
IMPLEMENT_MODULE(FToolingEditorModule, ToolingEditor)
