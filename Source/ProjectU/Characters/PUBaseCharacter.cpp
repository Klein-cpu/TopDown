// Fill out your copyright notice in the Description page of Project Settings.


#include "PUBaseCharacter.h"

#include "Components/CapsuleComponent.h"

// Sets default values
APUBaseCharacter::APUBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseCharacterCapsule = Cast<UCapsuleComponent>(GetCapsuleComponent());
}

