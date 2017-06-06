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

#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( FPaths::GameContentDir() / "Static/Slate"/ RelativePath + TEXT(".png"), __VA_ARGS__ )
#define BOX_BRUSH( RelativePath, ... ) FSlateBoxBrush( FPaths::GameContentDir() / "Static/Slate"/ RelativePath + TEXT(".png"), __VA_ARGS__ )
#define BORDER_BRUSH( RelativePath, ... ) FSlateBorderBrush( FPaths::GameContentDir() / "Static/Slate"/ RelativePath + TEXT(".png"), __VA_ARGS__ )
#define TTF_FONT( RelativePath, ... ) FSlateFontInfo( FPaths::GameContentDir() / "Static/Slate"/ RelativePath + TEXT(".ttf"), __VA_ARGS__ )
#define OTF_FONT( RelativePath, ... ) FSlateFontInfo( FPaths::GameContentDir() / "Static/Slate"/ RelativePath + TEXT(".otf"), __VA_ARGS__ )


TSharedRef<FSlateStyleSet> FMenuStyles::Create()
{
	TSharedRef<FSlateStyleSet> StyleRef = FSlateGameResources::New(FMenuStyles::GetStyleSetName(), "/Game/Static/UI/Styles", "/Game/Static/UI/Styles");
	FSlateStyleSet& Style = StyleRef.Get();


	const FLinearColor GoldColor(FColor(255, 213, 160));

	// Fonts still need to be specified in code for now
	Style.Set("BattleTanks.MenuFont", TTF_FONT("Fonts/Roboto-Black", 32));

	Style.Set("BattleTanks.ResourcesTextStyle", FTextBlockStyle()
		.SetFont(TTF_FONT("Fonts/Roboto-Regular", 40))
		.SetColorAndOpacity(GoldColor)
		.SetShadowColorAndOpacity(FLinearColor::Black)
		.SetShadowOffset(FIntPoint(-1, 1))
	);

	Style.Set("BattleTanks.ButtonFont", TTF_FONT("Fonts/Roboto-Black", 18));

	return StyleRef;
}

#undef IMAGE_BRUSH
#undef BOX_BRUSH
#undef BORDER_BRUSH
#undef TTF_FONT
#undef OTF_FONT

void FMenuStyles::ReloadTextures()
{
	FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
}

const ISlateStyle& FMenuStyles::Get()
{
	return *MenuStyleInstance;
}