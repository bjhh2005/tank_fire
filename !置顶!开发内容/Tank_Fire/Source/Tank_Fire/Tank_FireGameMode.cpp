// Copyright Epic Games, Inc. All Rights Reserved.

#include "Tank_FireGameMode.h"
#include "Tank_FireCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATank_FireGameMode::ATank_FireGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
