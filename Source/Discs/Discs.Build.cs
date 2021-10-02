// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Discs : ModuleRules
{
	public Discs(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
