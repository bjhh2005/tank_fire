// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Tank_Fire : ModuleRules
{
	public Tank_Fire(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
