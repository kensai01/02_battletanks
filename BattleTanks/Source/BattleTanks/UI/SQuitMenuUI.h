// Copyright MB

#pragma once


#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class BATTLETANKS_API SQuitMenuUI : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SQuitMenuUI)
	{}
	SLATE_ARGUMENT(TWeakObjectPtr<class AMainMenuHUD>, MainMenuHUD)
	SLATE_END_ARGS()

	// Constructs and lays out the Main Menu UI Widget.
	// args Arguments structure that contains widget-specific setup information.
	void Construct(const FArguments& args);

	// Click handler for the Play Game! button – Calls MenuHUD’s PlayGameClicked() event.
	FReply PlayGameClicked();

	// Click handler for the Quit Game button – Calls MenuHUD’s QuitGameClicked() event.
	FReply QuitGameClicked();

	// Stores a weak reference to the HUD controlling this class.
	TWeakObjectPtr<class AMainMenuHUD> MainMenuHUD;

	const struct FGlobalStyle* MenuStyle;
};
