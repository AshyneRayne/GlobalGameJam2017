// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "GGJ17Alpha.h"
#include "GGJ17AlphaGameMode.h"
#include "GGJPlayer.h"
#include "GGJ17AlphaPawn.h"

AGGJ17AlphaGameMode::AGGJ17AlphaGameMode()
{
	// set default pawn class to our flying pawn
	DefaultPawnClass = AGGJPlayer::StaticClass();
}
