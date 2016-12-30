// Copyright MB

#include "BattleTanks.h"
#include "TankSentry.h"
#include "Player/TankAIController.h" //TODO Remove association
#include "SentryAIController.h"
#include "Player/TankAimingComponent.h"
#include "Player/Tank.h"
#include "AI/BotWaypoint.h"

//#include "SPlayerState.h"

/* AI Include */
#include "Perception/PawnSensingComponent.h"
#include "Perception/AIPerceptionComponent.h"

// Sets default values
ATankSentry::ATankSentry(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/* Our sensing component to detect players by visibility and noise checks. */
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComp->SetPeripheralVisionAngle(60.0f);
	PawnSensingComp->SightRadius = 2000;
	PawnSensingComp->HearingThreshold = 600;
	PawnSensingComp->LOSHearingThreshold = 1200;

	/* By default we will not let the AI patrol, we can override this value per-instance. */
	BotType = EBotBehaviorType::Passive;

	/* Default value for the amount of time after the player leaves the detection radius before
	the sentry goes back to patrolling and give sup pursuit.*/
	SenseTimeOut = 2.5f;

	/* Note: Visual Setup is done in the AI/ZombieCharacter Blueprint file */
}

void ATankSentry::BeginPlay()
{
	Super::BeginPlay();

	/* This is the earliest moment we can bind our delegates(events) to the component */
	/* Explanation: The OnSeePawn and OnHearNoise methods were manually created and this is how we 
	add them to the sensing component of the sentry. This way OnSeePawn and OnHearNoise are events in blueprint
	that can be used to create various functionality directly via blueprint.*/
	if (PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &ATankSentry::OnSeePlayer);
		PawnSensingComp->OnHearNoise.AddDynamic(this, &ATankSentry::OnHearNoise);
	}
}


void ATankSentry::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	ASentryAIController* AIController = Cast<ASentryAIController>(GetController());
	/* Ensure that the AIController is present to avoid having dead
	sentry tanks firing on the player when they get in sense radius */
	if (bSensedTarget && AIController) 
	{
		return TakeAimAndFireOnSensedTarget();
	}

	/* Check if the last time we sensed a player is beyond the
	time out value to prevent bot from endlessly following a player.*/
	auto CurrentTime = GetWorld()->TimeSeconds;
	if (bSensedTarget && (CurrentTime - LastSeenTime) > SenseTimeOut
		&& (CurrentTime - LastHeardTime) > SenseTimeOut)
	{
		if (AIController)
		{
			/* Reset */
			bSensedTarget = false;
			AIController->SetTargetEnemy(nullptr);

			/* Stop playing the search and destroy sound */
			// TODO Implement search and destroy sound/music
			//BroadcastUpdateAudioLoop(false);
		}
	}
}

void ATankSentry::TakeAimAndFireOnSensedTarget()
{
	// Get the players tank first so we can get it's location
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!ensure(PlayerTank)) { return; }
	//UE_LOG(LogTemp, Warning, TEXT("Found Enemy, SEARCH AND DESTROY!"))

	/*Aim towards the player by referencing the actors location.
	AimingComponent has a method AimAt that will rotate the barrel and turret 
	towards the supplied FVector*/
	auto AimingComponent = this->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	// If aim & locked Fire towrads the player
	if (AimingComponent->GetFiringState() == EFiringStatus::Locked)
	{
		AimingComponent->Fire(); // TODO limit firing rate
	}
}


void ATankSentry::OnSeePlayer(APawn* Pawn)
{
	if (!IsAlive())
	{
		return;
	}

	if (!bSensedTarget)
	{
		// TODO Start playing the search and destroy sound
		//BroadcastUpdateAudioLoop(true);
	}

	/* Keep track of the time the player was last sensed in order to clear the target */
	LastSeenTime = GetWorld()->GetTimeSeconds();
	bSensedTarget = true;
	
	/*If the AIController is present (sentry tank not dead) and the player is alive 
	set the object that was sensed as the target enemy for the AI Controller.*/
	ASentryAIController* AIController = Cast<ASentryAIController>(GetController());
	ATank* SensedPawn = Cast<ATank>(Pawn);
	if (AIController && SensedPawn->IsAlive())
	{
		AIController->SetTargetEnemy(SensedPawn);
		//TODO Implement to take attack out of Tick function somehow...
		//PerformRangedStrike(SensedPawn);
	}
}

void ATankSentry::OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
{
	if (!IsAlive())
	{
		return;
	}

	if (!bSensedTarget)
	{
		// TODO Start playing the search and destroy sound
		//BroadcastUpdateAudioLoop(true);
	}

	bSensedTarget = true;
	LastHeardTime = GetWorld()->GetTimeSeconds();

	/*If the AIController is present (sentry tank not dead) and the player is alive
	set the object that was sensed as the target enemy for the AI Controller.*/
	ASentryAIController* AIController = Cast<ASentryAIController>(GetController());
	ATank* SensedPawn = Cast<ATank>(PawnInstigator);
	if (AIController && SensedPawn->IsAlive())
	{
		AIController->SetTargetEnemy(SensedPawn);
		//TODO Implement to take attack out of Tick function somehow...
		//PerformRangedStrike(SensedPawn);
	}
}

void ATankSentry::SetBotType(EBotBehaviorType NewType)
{
	BotType = NewType;

	ASentryAIController* AIController = Cast<ASentryAIController>(GetController());
	if (AIController)
	{
		AIController->SetBlackboardBotType(NewType);
	}

	//BroadcastUpdateAudioLoop(bSensedTarget);
}


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
