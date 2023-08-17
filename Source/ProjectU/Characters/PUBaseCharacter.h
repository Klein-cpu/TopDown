// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PUBaseCharacter.generated.h"

UCLASS(Abstract, NotBlueprintable)
class PROJECTU_API APUBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APUBaseCharacter();

	//BasicMovement
	virtual void MoveForward(float Value){}
	virtual void MoveRight(float Value){}
	virtual void Dash(){}

protected:
	UPROPERTY()
	UCapsuleComponent* BaseCharacterCapsule;

};
