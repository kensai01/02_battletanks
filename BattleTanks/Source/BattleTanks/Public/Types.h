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