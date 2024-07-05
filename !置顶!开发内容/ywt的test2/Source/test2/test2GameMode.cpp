// Copyright Epic Games, Inc. All Rights Reserved.

#include "test2GameMode.h"
#include "test2Character.h"
#include "UObject/ConstructorHelpers.h"

Atest2GameMode::Atest2GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
