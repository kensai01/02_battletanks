#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "SBattleTanksButtonWidget.h"

//class declare
class BATTLETANKS_API SBattleTanksMenuItem : public SBattleTanksButtonWidget
{
public:
	SLATE_BEGIN_ARGS(SBattleTanksMenuItem)
	{}

	SLATE_DEFAULT_SLOT(FArguments, Content)

	/** Called when the button is clicked */
	SLATE_EVENT(FOnClicked, OnClicked)

	SLATE_ATTRIBUTE(FText, Text)

	SLATE_END_ARGS()

	/** Needed for every widget */
	void Construct(const FArguments& InArgs);

	/** Says that we can support keyboard focus */
	virtual bool SupportsKeyboardFocus() const override { return true; }
};
