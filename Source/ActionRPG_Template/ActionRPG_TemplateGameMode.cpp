// Copyright Epic Games, Inc. All Rights Reserved.

#include "ActionRPG_TemplateGameMode.h"
#include "ActionRPG_TemplateCharacter.h"
#include "UObject/ConstructorHelpers.h"

AActionRPG_TemplateGameMode::AActionRPG_TemplateGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
