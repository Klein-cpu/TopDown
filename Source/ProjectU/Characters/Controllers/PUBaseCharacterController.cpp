// Fill out your copyright notice in the Description page of Project Settings.


#include "PUBaseCharacterController.h"

#include "ProjectU/Characters/PUBaseCharacter.h"

void APUBaseCharacterController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	CachedBaseCharacter = Cast<APUBaseCharacter>(InPawn);
}

void APUBaseCharacterController::MoveForward(float Value)
{
	if(CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->MoveForward(Value);
	}
}

void APUBaseCharacterController::MoveRight(float Value)
{
	if(CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->MoveRight(Value);
	}
}

void APUBaseCharacterController::Dash()
{
	if(CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->Dash();
	}
}

void APUBaseCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//Axises
	InputComponent->BindAxis("MoveForward", this, &APUBaseCharacterController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APUBaseCharacterController::MoveRight);

	//Actions
	InputComponent->BindAction("Dash", IE_Pressed, this, &APUBaseCharacterController::Dash);
}
