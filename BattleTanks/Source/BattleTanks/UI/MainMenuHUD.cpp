// Copyright MB

#include "BattleTanks.h"
#include "MainMenuHUD.h"
#include "SMainMenuUI.h"
#include "SlateBasics.h"
#include "SlateExtras.h"
#include "SBattleTanksMenuWidget.h"
#include "BattleTanksMenuItem.h"
#include "GlobalMenuWidgetStyle.h"
#include "Engine.h"

#define LOCTEXT_NAMESPACE "BattleTanks.HUD.Menu"

AMainMenuHUD::AMainMenuHUD(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//MenuButtonTexture = LoadObject<UTexture2D>(nullptr, TEXT("/Game/UI/MainMenu/MenuButton.MenuButton"), nullptr, LOAD_None, nullptr);

	AddMenuItem(MainMenu, LOCTEXT("Start", "START"));
	AddMenuItem(MainMenu->Last().SubMenu, LOCTEXT("Easy", "EASY"))->OnConfirmMenuItem.BindUObject(this, &AMainMenuHUD::ExecuteSelectMapAction, (int32)EMenuAction::SetEasy);
	AddMenuItem(MainMenu->Last().SubMenu, LOCTEXT("Normal", "NORMAL"))->OnConfirmMenuItem.BindUObject(this, &AMainMenuHUD::ExecuteSelectMapAction, (int32)EMenuAction::SetMedium);
	AddMenuItem(MainMenu->Last().SubMenu, LOCTEXT("Hard", "HARD"))->OnConfirmMenuItem.BindUObject(this, &AMainMenuHUD::ExecuteSelectMapAction, (int32)EMenuAction::SetHard);
	AddMenuItem(MainMenu->Last().SubMenu, LOCTEXT("Back", "BACK"))->OnConfirmMenuItem.BindUObject(this, &AMainMenuHUD::ExecuteSelectMapAction, (int32)EMenuAction::GoBack);

	if (FPlatformProperties::SupportsQuit())
	{
		AddMenuItem(MainMenu, LOCTEXT("Quit", "QUIT"))->OnConfirmMenuItem.BindUObject(this, &AMainMenuHUD::ExecuteQuitAction);
	}
	CurrentMenu = MainMenu;

}

FBattleTanksMenuItem* AMainMenuHUD::AddMenuItem(TSharedPtr<TArray<class FBattleTanksMenuItem>> &SubMenu, FText Text)
{
	if (!SubMenu.IsValid())
	{
		SubMenu = MakeShareable(new TArray<FBattleTanksMenuItem>());
	}
	FBattleTanksMenuItem MenuItem(Text);
	SubMenu->Add(MenuItem);
	return &SubMenu->Last();
}

void AMainMenuHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//Now that we are here, build our menu widget
	RebuildWidgets();
}

void AMainMenuHUD::ExecuteQuitAction()
{
	MenuWidget->HideMenu();
	//const FStrategyHUDSoundsStyle& HUDSounds = FStrategyStyle::Get().GetWidgetStyle<FStrategyHUDSoundsStyle>("DefaultStrategyHUDSoundsStyle");
	//MenuHelper::PlaySoundAndCall(PlayerOwner->GetWorld(), HUDSounds.ExitGameSound, this, &AMainMenuHUD::Quit);
	MenuWidget->LockControls(true);
}

void AMainMenuHUD::Quit()
{
	GetOwningPlayerController()->ConsoleCommand("quit");
}

void AMainMenuHUD::ExecuteSelectMapAction(int32 index)
{
	switch (index)
	{
	case EMenuAction::GoBack:
		MenuWidget->MenuGoBack();
		return;
	case EMenuAction::SetEasy:
		Difficulty = EGameDifficulty::Easy;
		break;
	case EMenuAction::SetMedium:
		Difficulty = EGameDifficulty::Medium;
		break;
	case EMenuAction::SetHard:
		Difficulty = EGameDifficulty::Hard;
		break;
	default:
		return;
	}

	MenuWidget->HideMenu();
	MenuWidget->LockControls(true);
	//const FStrategyHUDSoundsStyle& HUDSounds = FStrategyStyle::Get().GetWidgetStyle<FStrategyHUDSoundsStyle>("DefaultStrategyHUDSoundsStyle");
	//MenuHelper::PlaySoundAndCall(PlayerOwner->GetWorld(), HUDSounds.StartGameSound, this, &AMainMenuHUD::LaunchGame);
}

void AMainMenuHUD::LaunchGame()
{
	//FString StartStr = FString::Printf(TEXT("/Game/Maps/TowerDefenseMap?%s=%d"), *AStrategyGameMode::DifficultyOptionName, (uint8)Difficulty);
	//GetWorld()->ServerTravel(StartStr);
	ShowLoadingScreen();
}

void AMainMenuHUD::RebuildWidgets(bool bHotReload)
{
	MenuWidget.Reset();

	if (GEngine &&
		GEngine->GameViewport)
	{
		UGameViewportClient* GVC = GEngine->GameViewport;
		SAssignNew(MenuWidget, SBattleTanksMenuWidget)
			.Cursor(EMouseCursor::Default)
			.MainMenuHUD(TWeakObjectPtr<AMainMenuHUD>(this));

		GVC->AddViewportWidgetContent(
			SNew(SWeakWidget)
			.PossiblyNullContent(MenuWidget.ToSharedRef()));
	}
}

void AMainMenuHUD::ShowLoadingScreen()
{
	//IStrategyGameLoadingScreenModule* LoadingScreenModule = FModuleManager::LoadModulePtr<IStrategyGameLoadingScreenModule>("StrategyGameLoadingScreen");
	//if (LoadingScreenModule != nullptr)
	//{
	//	LoadingScreenModule->StartInGameLoadingScreen();
	//}
}

#undef LOCTEXT_NAMESPACE

//void AAMainMenuHUD::PostInitializeComponents()
//{
//	Super::PostInitializeComponents();
//
//	SAssignNew(MainMenuUI, SMainMenuUI).AMainMenuHUD(this);
//
//	if (GEngine->IsValidLowLevel())
//	{
//		if (GEngine->GameViewport != nullptr) 
//		{
//			GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(MainMenuUI.ToSharedRef()));
//		}
//	}
//}

