// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "BattleTanksGameMode.h"
#include "UI/MainMenuHUD.h"
#include "TankTeamStart.h"
#include "NPC/SentryAIController.h"

//
//AActor* ABattleTanksGameMode::ChoosePlayerStart_Implementation(AController* Player)
//{
//	TArray<APlayerStart*> PreferredSpawns;
//	TArray<APlayerStart*> FallbackSpawns;
//
//	APlayerStart* BestStart = NULL;
//	for (TActorIterator<APlayerStart> It(GetWorld()); It; ++It)
//	{
//		APlayerStart* TestSpawn = *It;
//		if (TestSpawn->IsA<APlayerStartPIE>())
//		{
//			// Always prefer the first "Play from Here" PlayerStart, if we find one while in PIE mode
//			BestStart = TestSpawn;
//			break;
//		}
//		else
//		{
//			if (IsSpawnpointAllowed(TestSpawn, Player))
//			{
//				if (IsSpawnpointPreferred(TestSpawn, Player))
//				{
//					PreferredSpawns.Add(TestSpawn);
//				}
//				else
//				{
//					FallbackSpawns.Add(TestSpawn);
//				}
//			}
//		}
//	}
//
//
//	if (BestStart == NULL)
//	{
//		if (PreferredSpawns.Num() > 0)
//		{
//			BestStart = PreferredSpawns[FMath::RandHelper(PreferredSpawns.Num())];
//		}
//		else if (FallbackSpawns.Num() > 0)
//		{
//			BestStart = FallbackSpawns[FMath::RandHelper(FallbackSpawns.Num())];
//		}
//	}
//
//	return BestStart ? BestStart : Super::ChoosePlayerStart_Implementation(Player);
//}
//
//bool ABattleTanksGameMode::IsSpawnpointAllowed(APlayerStart* SpawnPoint, AController* Player) const
//{
//	ATankTeamStart* ShooterSpawnPoint = Cast<ATankTeamStart>(SpawnPoint);
//	if (ShooterSpawnPoint)
//	{
//		ASentryAIController* AIController = Cast<ASentryAIController>(Player);
//		if (ShooterSpawnPoint->bNotForBots && AIController)
//		{
//			return false;
//		}
//
//		if (ShooterSpawnPoint->bNotForPlayers && AIController == NULL)
//		{
//			return false;
//		}
//		return true;
//	}
//
//	return false;
//}
//
//bool ABattleTanksGameMode::IsSpawnpointPreferred(APlayerStart* SpawnPoint, AController* Player) const
//{
//	ATrackedVehicle* MyPawn = Cast<ATrackedVehicle>((*DefaultPawnClass)->GetDefaultObject<ATrackedVehicle>());
//	ASentryAIController* AIController = Cast<ASentryAIController>(Player);
//	if (AIController != nullptr)
//	{
//		MyPawn = Cast<ATrackedVehicle>(BotPawnClass->GetDefaultObject<ATrackedVehicle>());
//	}
//
//	if (MyPawn)
//	{
//		const FVector SpawnLocation = SpawnPoint->GetActorLocation();
//		for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; ++It)
//		{
//			ATrackedVehicle* OtherPawn = Cast<ATrackedVehicle>(*It);
//			if (OtherPawn && OtherPawn != MyPawn)
//			{
//				const float CombinedHeight = (MyPawn->GetDefaultHalfHeight() + OtherPawn->GetDefaultHalfHeight()) * 2.0f;
//				const float CombinedRadius = MyPawn->GetSimpleCollisionRadius() + OtherPawn->GetSimpleCollisionRadius();
//				const FVector OtherLocation = OtherPawn->GetActorLocation();
//
//				// check if player start overlaps this pawn
//				if (FMath::Abs(SpawnLocation.Z - OtherLocation.Z) < CombinedHeight && (SpawnLocation - OtherLocation).Size2D() < CombinedRadius)
//				{
//					return false;
//				}
//			}
//		}
//	}
//	else
//	{
//		return false;
//	}
//
//	return true;
//}