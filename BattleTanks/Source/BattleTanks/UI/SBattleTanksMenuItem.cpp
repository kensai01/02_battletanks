#include "BattleTanks.h"
#include "SBattleTanksMenuItem.h"
#include "MenuStyles.h"

void SBattleTanksMenuItem::Construct(const FArguments& InArgs)
{
	SBattleTanksButtonWidget::Construct(
		SBattleTanksButtonWidget::FArguments()
		.ButtonText(InArgs._Text)
		.TextFont(FMenuStyles::Get().GetFontStyle(TEXT("BattleTanks.MenuFont")))
		.TextVAlign(EVerticalAlignment::VAlign_Center)
		.TextMargin(FMargin(0))
		.Visibility(EVisibility::Visible)
		.OnClicked(InArgs._OnClicked)
		[
			InArgs._Content.Widget
		]
	);
}