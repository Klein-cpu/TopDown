// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PUBaseCharacter.h"
#include "PUMainCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
UCLASS(Blueprintable)
class PROJECTU_API APUMainCharacter : public APUBaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APUMainCharacter();

	virtual void MoveForward(float Value) override;
	virtual void MoveRight(float Value) override;
	virtual void Dash() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Basic Movement");
	float RotationSpeed = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Basic Movement")
	float DashLength = 500.f;

public:
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY()
	USkeletalMeshComponent* BaseMesh;
};
