// Copyright MB

#pragma once

#include "GameFramework/PlayerStart.h"
#include "TankTeamStart.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankTeamStart : public APlayerStart
{
	GENERATED_BODY()

public:
	/** Which team can start at this point */
	UPROPERTY(EditInstanceOnly, Category = Team)
	int32 SpawnTeam;

	/** Whether players can start at this point */
	UPROPERTY(EditInstanceOnly, Category = Team)
	uint32 bNotForPlayers : 1;

	/** Whether bots can start at this point */
	UPROPERTY(EditInstanceOnly, Category = Team)
	uint32 bNotForBots : 1;
	
};
