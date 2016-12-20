// Copyright MB

#include "Types.generated.h"
#pragma once

/**
 * 
 */

UENUM()
enum class EBotBehaviorType : uint8
{
	/* Does not move, remains in place until a player is spotted */
	Passive,

	/* Patrols a region until a player is spotted */
	Patrolling,
};

// Enum for AI perception state
UENUM()
enum class EPerceptionStatus : uint8
{
	Patrolling, 
	Seeking
};


// Enum for aiming state
UENUM()
enum class EFiringStatus : uint8
{
	Reloading, 
	Aiming, 
	Locked, 
	OutOfAmmo
};