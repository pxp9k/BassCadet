// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "NinSessionGameMode.h"
#include "NinSessionCharacter.h"
#include "UObject/ConstructorHelpers.h"

ANinSessionGameMode::ANinSessionGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
