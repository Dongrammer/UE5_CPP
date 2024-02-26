// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UE5_CPP : ModuleRules
{
	public UE5_CPP(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });

		PublicIncludePaths.Add(ModuleDirectory);
	}
}
