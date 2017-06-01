// Copyright MB

#pragma once

#include "SlateBasics.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class BATTLETANKS_API SPlayersHUDUI : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SPlayersHUDUI)
	{}
	SLATE_ARGUMENT(TWeakObjectPtr<class AMainMenuHUD>, MainMenuHUD);
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	/* Stores a weak reference to the HUD owning object*/
	TWeakObjectPtr<class AMainMenuHUD> MainMenuHUD;

	/* A reference to the slate style used for this HUD's widgets*/
	const struct FGlobalStyle* HUDStyle;


};
