// Copyright MB

#pragma once
#include "SlateBasics.h"

/**
 * 
 */
class FBattleTanksMenuItem
{
public:
	/** menu item text */
	FText Text;

	/** sub menu if present */
	TSharedPtr<TArray<FBattleTanksMenuItem>> SubMenu;

	/** shared pointer to actual slate widget representing the menu item */
	TSharedPtr<class FBattleTanksMenuItem> Widget;

	/** confirm menu item delegate */
	DECLARE_DELEGATE(FOnConfirmMenuItem);

	/** delegate, which is executed by SShooterMenuWidget if user confirms this menu item */
	FOnConfirmMenuItem OnConfirmMenuItem;

	/** constructor accepting menu item text */
	FBattleTanksMenuItem(FText _text)
	{
		Text = _text;
	}
};
