// Copyright MB

#pragma once

#include "Types.h"
#include "GameFramework/HUD.h"
#include "MainMenuHUD.generated.h"


/**
 * 
 */

namespace EMenuAction
{
	enum Type
	{
		GoBack = -1,
		SetEasy = 0,
		SetMedium,
		SetHard
	};
}


UCLASS(Blueprintable)
class BATTLETANKS_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()

public:
	AMainMenuHUD(const class FObjectInitializer& ObjectInitializer);

	// Initializes the Slate UI and adds it as widget content to the game viewport.
	virtual void PostInitializeComponents() override;

	/** Main menu. */
	TSharedPtr<TArray<class FBattleTanksMenuItem>> MainMenu;

	/** Currently visible menu. */
	TSharedPtr<TArray<class FBattleTanksMenuItem>> CurrentMenu;

	/** Menu that is about to open. */
	TSharedPtr<TArray<class FBattleTanksMenuItem>> NextMenu;

	/** Menu history stack. */
	TArray<TSharedPtr<TArray<class FBattleTanksMenuItem>>> MenuHistory;


	// Called by SMainMenu whenever the Play Game! button has been clicked.s
	UFUNCTION(BlueprintImplementableEvent, Category = "Menus|Main Menu")
	void PlayGameClicked();

	// Called by SMainMenu whenever the Quit Game button has been clicked.
	UFUNCTION(BlueprintImplementableEvent, Category = "Menus|Main Menu")
	void QuitGameClicked();

	/**
	* Clears out the old widgets, rebuilds them
	*
	* @param	bHotRelead	Not used.
	*/
	void RebuildWidgets(bool bHotReload = false);

private:
	/** Menu widget pointer. */
	TSharedPtr<class SBattleTanksMenuWidget> MenuWidget;

	/** Selected game difficulty. */
	TEnumAsByte<EGameDifficulty::Type> Difficulty;

	/**
	* Helper for adding menu items .
	*
	* @param	SubMenu	The item to add.
	* @param	Text	The item text.
	*/
	FBattleTanksMenuItem* AddMenuItem(TSharedPtr<TArray<class FBattleTanksMenuItem>> &SubMenu, FText Text);

	/** Callback for quit button. */
	void ExecuteQuitAction();

	/**
	* Callback for start button.
	*
	* @param	Action	Action to take. (Should be EMenuAction type)
	*/
	void ExecuteSelectMapAction(int32 Action);

	/** Starts the game with selected difficulty. */
	void LaunchGame();

	/** Quits the game. */
	void Quit();

	/** Show the loading screen. */
	void ShowLoadingScreen();

};
