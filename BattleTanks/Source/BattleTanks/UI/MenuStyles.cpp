// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "BattleTanks.h"
#include "MenuStyles.h"
#include "SlateGameResources.h" 

TSharedPtr<FSlateStyleSet> FMenuStyles::MenuStyleInstance = NULL;

void FMenuStyles::Initialize()
{
	if (!MenuStyleInstance.IsValid())
	{
		MenuStyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*MenuStyleInstance);
	}
}

void FMenuStyles::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*MenuStyleInstance);
	ensure(MenuStyleInstance.IsUnique());
	MenuStyleInstance.Reset();
}

FName FMenuStyles::GetStyleSetName()
{
	static FName StyleSetName(TEXT("MenuStyles"));
	return StyleSetName;
}

TSharedRef<FSlateStyleSet> FMenuStyles::Create()
{
	TSharedRef<FSlateStyleSet> StyleRef = FSlateGameResources::New(FMenuStyles::GetStyleSetName(), "/Game/Static/UI/Styles", "/Game/Static/UI/Styles");
	return StyleRef;
}

const ISlateStyle& FMenuStyles::Get()
{
	return *MenuStyleInstance;
}