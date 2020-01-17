// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "GhostProjGameMode.h"
#include "GhostProjCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGhostProjGameMode::AGhostProjGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
