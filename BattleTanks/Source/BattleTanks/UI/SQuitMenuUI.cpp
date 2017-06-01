// Copyright MB

#include "BattleTanks.h"
#include "SQuitMenuUI.h"
#include "SlateOptMacros.h"
#include "MenuStyles.h"
#include "MainMenuHUD.h"
#include "GlobalMenuWidgetStyle.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SQuitMenuUI::Construct(const FArguments& InArgs)
{
	MainMenuHUD = InArgs._MainMenuHUD;
	MenuStyle = &FMenuStyles::Get().GetWidgetStyle<FGlobalStyle>("GlobalStyle");

	ChildSlot
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Top)
			[
				SNew(SImage)
				.Image(&MenuStyle->BackgroundBrush)
			]
			+ SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Top)
			[
				SNew(STextBlock)
				.TextStyle(&MenuStyle->MenuTitleStyle)
				.Text(FText::FromString("Game Over"))
			]
			+ SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SButton)
					.ButtonStyle(&MenuStyle->MenuButtonStyle)
					.TextStyle(&MenuStyle->MenuButtonTextStyle)
					.Text(FText::FromString("Play Again"))
					.OnClicked(this, &SQuitMenuUI::PlayGameClicked)
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SButton)
					.ButtonStyle(&MenuStyle->MenuButtonStyle)
					.TextStyle(&MenuStyle->MenuButtonTextStyle)
					.Text(FText::FromString("Quit Game"))
					.OnClicked(this, &SQuitMenuUI::QuitGameClicked)
				]
			]
		];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

FReply SQuitMenuUI::PlayGameClicked()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, TEXT("PlayGameClicked"));
	}

	// actually the BlueprintImplementable function of the HUD is not called; uncomment if you want to handle the OnClick via Blueprint
	MainMenuHUD->PlayGameClicked();
	return FReply::Handled();
}

FReply SQuitMenuUI::QuitGameClicked()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, TEXT("QuitGameClicked"));
	}

	// actually the BlueprintImplementable function of the HUD is not called; uncomment if you want to handle the OnClick via Blueprint
	MainMenuHUD->QuitGameClicked();
	return FReply::Handled();
}
