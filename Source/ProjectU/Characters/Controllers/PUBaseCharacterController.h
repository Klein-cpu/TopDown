// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PUBaseCharacterController.generated.h"

class APUBaseCharacter;
/**
 * 
 */
UCLASS()
class PROJECTU_API APUBaseCharacterController : public APlayerController
{
	GENERATED_BODY()

	virtual void SetPawn(APawn* InPawn) override;

public:
	
protected:
	//BasicMovement
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Dash();
	
    TWeakObjectPtr<APUBaseCharacter> CachedBaseCharacter;

	virtual void SetupInputComponent() override;
	
};
