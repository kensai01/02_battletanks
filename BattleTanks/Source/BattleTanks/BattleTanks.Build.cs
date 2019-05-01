// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class BattleTanks : ModuleRules
{
	public BattleTanks(ReadOnlyTargetRules Target) : base(Target)
	{

        DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");

        PublicDependencyModuleNames.AddRange(new string[] { "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "AIModule",
            "GameplayTasks",
            "OnlineSubsystem",
            "OnlineSubsystemUtils",
            "NavigationSystem"
        });

		PrivateDependencyModuleNames.AddRange(new string[] { });

		// Uncomment if you are using Slate UI
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "UMG" });


    }
}
