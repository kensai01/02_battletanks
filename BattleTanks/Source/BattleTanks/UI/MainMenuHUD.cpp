// Copyright MB

#include "BattleTanks.h"
#include "MainMenuHUD.h"
#include "SMainMenuUI.h"
#include "Engine.h"

void AMainMenuHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SAssignNew(MainMenuUI, SMainMenuUI).MainMenuHUD(this);

	if (GEngine->IsValidLowLevel())
	{
		GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(MainMenuUI.ToSharedRef()));
	}
}