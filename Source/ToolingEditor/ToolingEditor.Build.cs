// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ToolingEditor : ModuleRules
{
	public ToolingEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core"
			, "CoreUObject"
			, "Engine"
			, "UnrealEd"
			, "EditorSubsystem"
			// FOR UI EDITING
			, "Slate"
			, "SlateCore"
			// main module
			, "Tooling"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
