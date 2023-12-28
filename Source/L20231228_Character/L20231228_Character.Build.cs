// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class L20231228_Character : ModuleRules
{
	public L20231228_Character(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput","EnhancedInput" });//향상된 입력 추가
	}
}
