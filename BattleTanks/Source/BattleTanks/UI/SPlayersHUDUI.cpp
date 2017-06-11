// Copyright MB

#include "BattleTanks.h"
#include "MainMenuHUD.h"
#include "SPlayersHUDUI.h"
#include "SlateOptMacros.h"
#include "GlobalMenuWidgetStyle.h"
#include "MenuStyles.h"

//BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
//void SPlayersHUDUI::Construct(const FArguments& InArgs)
//{
	//MainMenuHUD = InArgs._MainMenuHUD;
	//HUDStyle = &FMenuStyles::Get().GetWidgetStyle<FGlobalStyle>("GlobalStyle");

	//
	//ChildSlot
	//[
	//	SNew(SOverlay)
	//	+ SOverlay::Slot()
	//	.HAlign(HAlign_Right)
	//	.VAlign(VAlign_Top)
	//	[
	//		SNew(STextBlock)
	//		.TextStyle(&HUDStyle->PlayersHUDStyle)
	//		.Text(FText::FromString("SCORE: 0"))
	//	]
	//	+ SOverlay::Slot()
	//	.HAlign(HAlign_Left)
	//	.VAlign(VAlign_Top)
	//	[
	//		SNew(STextBlock)
	//		.TextStyle(&HUDStyle->PlayersHUDStyle)
	//		.Text(FText::FromString("AMMO: 20"))
	//	]
	//];
	
//}
//END_SLATE_FUNCTION_BUILD_OPTIMIZATION
