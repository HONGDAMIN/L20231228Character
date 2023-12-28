// Copyright Epic Games, Inc. All Rights Reserved.

#include "L20231228_CharacterGameMode.h"
#include "L20231228_CharacterCharacter.h"
#include "UObject/ConstructorHelpers.h"

AL20231228_CharacterGameMode::AL20231228_CharacterGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
