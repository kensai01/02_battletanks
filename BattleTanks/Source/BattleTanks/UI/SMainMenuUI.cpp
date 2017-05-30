// Copyright MB

#include "BattleTanks.h"
#include "SMainMenuUI.h"
#include "SlateOptMacros.h"
#include "GlobalMenuWidgetStyle.h"
#include "MenuStyles.h"
#include "MainMenuHUD.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SMainMenuUI::Construct(const FArguments& InArgs)
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
				SNew(STextBlock)
				//.ColorAndOpacity(FLinearColor::White)
				//.ShadowColorAndOpacity(FLinearColor::Black)
				//.ShadowOffset(FIntPoint(-1, 1))
				//.Font(FSlateFontInfo("Arial", 26))
				.TextStyle(&MenuStyle->MenuTitleStyle)
				.Text(FText::FromString("Main Menu"))
			]
			+ SOverlay::Slot()
				.HAlign(HAlign_Right)
				.VAlign(VAlign_Bottom)
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot()
					[
						SNew(SButton)
						.ButtonStyle(&MenuStyle->MenuButtonStyle)
						.TextStyle(&MenuStyle->MenuButtonTextStyle)
						.Text(FText::FromString("Play Game!"))
						.OnClicked(this, &SMainMenuUI::PlayGameClicked)
					]
					+ SVerticalBox::Slot()
					[
						SNew(SButton)
						.ButtonStyle(&MenuStyle->MenuButtonStyle)
						.TextStyle(&MenuStyle->MenuButtonTextStyle)
						.Text(FText::FromString("Quit Game"))
						.OnClicked(this, &SMainMenuUI::QuitGameClicked)
					]
				]
		];

}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

FReply SMainMenuUI::PlayGameClicked()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, TEXT("PlayGameClicked"));
	}

	// actually the BlueprintImplementable function of the HUD is not called; uncomment if you want to handle the OnClick via Blueprint
	MainMenuHUD->PlayGameClicked();
	return FReply::Handled();
}

FReply SMainMenuUI::QuitGameClicked()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, TEXT("QuitGameClicked"));
	}

	// actually the BlueprintImplementable function of the HUD is not called; uncomment if you want to handle the OnClick via Blueprint
	MainMenuHUD->QuitGameClicked();
	return FReply::Handled();
}
