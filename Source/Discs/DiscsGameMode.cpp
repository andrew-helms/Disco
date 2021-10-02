// Copyright Epic Games, Inc. All Rights Reserved.

#include "DiscsGameMode.h"
#include "DiscsHUD.h"
#include "DiscsCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADiscsGameMode::ADiscsGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ADiscsHUD::StaticClass();
}
