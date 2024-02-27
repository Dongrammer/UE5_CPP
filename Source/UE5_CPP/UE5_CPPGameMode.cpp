// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE5_CPPGameMode.h"
#include "UE5_CPPCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUE5_CPPGameMode::AUE5_CPPGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Script/Engine.Blueprint'/Game/Template/ThirdPerson/Blueprints/BP_ThirdPersonCharacter.BP_ThirdPersonCharacter'"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
