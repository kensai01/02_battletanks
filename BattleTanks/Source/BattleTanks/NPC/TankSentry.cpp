// Copyright MB

#include "BattleTanks.h"
#include "TankSentry.h"
#include "SentryAIController.h"
#include "Player/TankAimingComponent.h"
#include "Player/Tank.h"
#include "AI/BotWaypoint.h"


// Sets default values
//ATankSentry::ATankSentry(const class FObjectInitializer& ObjectInitializer)
//	: Super(ObjectInitializer)
//{
//	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
//	PrimaryActorTick.bCanEverTick = false;
//
//	/* By default we will not let the AI patrol, we can override this value per-instance. */
//	BotType = EBotBehaviorType::Passive;
//
//	/* Note: Visual Setup is done in the AI/ZombieCharacter Blueprint file */
//}

void ATankSentry::TakeAimAndFireOnSensedTarget()
{
	// Get the players tank first so we can get it's location
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	/* Protect player tank pointer */
	if (!ensure(PlayerTank)) { return; }

	/*Aim towards the player by referencing the actors location.
	AimingComponent has a method AimAt that will rotate the barrel and turret 
	towards the supplied FVector*/
	auto AimingComponent = this->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	/* If aiming & locked Fire towrads the player */
	if (AimingComponent->GetFiringState() == EFiringStatus::Locked)
	{
		AimingComponent->Fire(); // TODO limit firing rate
	}
}

/*	Sets the bot type based on the two options:
	Does not move, remains in place until a player is spotted 
	BOT TYPE - Passive,

	Patrols a region until a player is spotted 
	BOT TYPE - Patrolling, 
*/
void ATankSentry::SetBotType(EBotBehaviorType NewType)
{
	BotType = NewType;

	ASentryAIController* AIController = Cast<ASentryAIController>(GetController());
	if (AIController)
	{
		AIController->SetBlackboardBotType(NewType);
	}

	/* TODO: Implement broadcast audio loop 
	when re-working the sound of the character */
	//BroadcastUpdateAudioLoop(bSensedTarget);
}



///UNUSED COMPONENTS / OLD COMPONENTS
//UAudioComponent* ATankSentry::PlayCharacterSound(USoundCue* CueToPlay)
//{
//	if (CueToPlay)
//	{
//		return UGameplayStatics::SpawnSoundAttached(CueToPlay, RootComponent, NAME_None, FVector::ZeroVector, EAttachLocation::SnapToTarget, true);
//	}
//
//	return nullptr;
//}
//
//
//void ASZombieCharacter::PlayHit(float DamageTaken, struct FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser, bool bKilled)
//{
//	Super::PlayHit(DamageTaken, DamageEvent, PawnInstigator, DamageCauser, bKilled);
//
//	/* Stop playing the hunting sound */
//	if (AudioLoopComp && bKilled)
//	{
//		AudioLoopComp->Stop();
//	}
//}

//
//void ATankSentry::OnSeePlayer(APawn* Pawn)
//{
//	if (!IsAlive())
//	{
//		return;
//	}
//
//	if (!bSensedTarget)
//	{
//		// TODO Start playing the search and destroy sound
//		//BroadcastUpdateAudioLoop(true);
//	}
//
//	/* Keep track of the time the player was last sensed in order to clear the target */
//	LastSeenTime = GetWorld()->GetTimeSeconds();
//	bSensedTarget = true;
//	
//	/*If the AIController is present (sentry tank not dead) and the player is alive 
//	set the object that was sensed as the target enemy for the AI Controller.*/
//	ASentryAIController* AIController = Cast<ASentryAIController>(GetController());
//	ATank* SensedPawn = Cast<ATank>(Pawn);
//	if (AIController && SensedPawn->IsAlive())
//	{
//		AIController->SetTargetEnemy(SensedPawn);
//		//TODO Implement to take attack out of Tick function somehow...
//		//PerformRangedStrike(SensedPawn);
//	}
//}

//void ATankSentry::OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
//{
//	if (!IsAlive())
//	{
//		return;
//	}
//
//	if (!bSensedTarget)
//	{
//		// TODO Start playing the search and destroy sound
//		//BroadcastUpdateAudioLoop(true);
//	}
//
//	bSensedTarget = true;
//	LastHeardTime = GetWorld()->GetTimeSeconds();
//
//	/*If the AIController is present (sentry tank not dead) and the player is alive
//	set the object that was sensed as the target enemy for the AI Controller.*/
//	ASentryAIController* AIController = Cast<ASentryAIController>(GetController());
//	ATank* SensedPawn = Cast<ATank>(PawnInstigator);
//	if (AIController && SensedPawn->IsAlive())
//	{
//		AIController->SetTargetEnemy(SensedPawn);
//		//TODO Implement to take attack out of Tick function somehow...
//		//PerformRangedStrike(SensedPawn);
//	}
//}