// Fill out your copyright notice in the Description page of Project Settings.


#include "PUMainCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Math/UnitConversion.h"

// Sets default values
APUMainCharacter::APUMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring arm"));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	BaseMesh = Cast<USkeletalMeshComponent>(GetMesh());
	
}

void APUMainCharacter::MoveForward(float Value)
{
	Super::MoveForward(Value);
	if(!FMath::IsNearlyZero(Value))
	{
		AddMovementInput(FRotator::ZeroRotator.Vector(), Value);
	}
}

void APUMainCharacter::MoveRight(float Value)
{
	Super::MoveRight(Value);
	if(!FMath::IsNearlyZero(Value))
	{
		AddMovementInput(CameraComponent->GetRightVector(), Value);
	}
}

void APUMainCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	FApp::SetDeltaTime(DeltaSeconds);
	CharacterRotation();
}

void APUMainCharacter::Dash()
{
	float ForwardAxisValue = GetController()->GetInputAxisValue("MoveForward");
	float RightAxisValue = GetController()->GetInputAxisValue("MoveRight");

	if(bCanDash)
	{
		FVector CurrentActorLocation = GetActorLocation();
		FVector TargetOrientationVector = FRotator::ZeroRotator.Vector() * ForwardAxisValue + CameraComponent->GetRightVector() * RightAxisValue;
		FVector TargetActorLocation = CurrentActorLocation + TargetOrientationVector * DashLength;

		SetActorLocation(TargetActorLocation);
		bCanDash = false;
		GetWorld()->GetTimerManager().SetTimer(DashCooldownTimer, [this]{bCanDash = true;}, DashCooldown, false);
	}
}

void APUMainCharacter::CharacterRotation()
{
	float MoveForwardAxisValue = GetController()->GetInputAxisValue("MoveForward");
	float MoveRightAxisValue = GetController()->GetInputAxisValue("MoveRight");

	if(FMath::IsNearlyZero(MoveForwardAxisValue) && FMath::IsNearlyZero(MoveRightAxisValue))
	{
		return;
	}

	float CurrentRotation = GetActorRotation().Yaw;
	float TargetForwardRotation = FRotator::ZeroRotator.Yaw;
	float TargetRightRotation = FRotator::ZeroRotator.Yaw;
	float TargetRotation = FRotator::ZeroRotator.Yaw;
	
	if(!FMath::IsNearlyZero(MoveForwardAxisValue))
	{
		//Changing forward component of rotation
		TargetForwardRotation += (MoveForwardAxisValue < 0.f) ? (CurrentRotation < 0.f && CurrentRotation > -180.f ? -180.f : 180.f) : 0.f;
	}
	
	if(!FMath::IsNearlyZero(MoveRightAxisValue)) //Changing right component of rotation
	{
		TargetRightRotation += 90.f;
		TargetRightRotation -= (MoveRightAxisValue < 0.f) ? 180.f : 0.f;
		if(FMath::Sign(TargetForwardRotation) != FMath::Sign(TargetRightRotation)) TargetForwardRotation *= -1;
	}
	
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Current: %.4f"), CurrentRotation));
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Forward: %.2f"), TargetForwardRotation));
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Right: %.2f"), TargetRightRotation));
	TargetRotation = TargetForwardRotation + TargetRightRotation;
	
	if(!FMath::IsNearlyZero(MoveForwardAxisValue) && !FMath::IsNearlyZero(MoveRightAxisValue))
	{
		TargetRotation /= 2;
	}

	if(FMath::Abs(TargetRotation - CurrentRotation) > 180.f)
	{
		if(TargetRotation > CurrentRotation)
		{
			CurrentRotation += 360.f; 
		}
		else
		{
			CurrentRotation -= 360.f;
		}
	}
	
	CurrentRotation = FMath::FInterpTo(CurrentRotation, TargetRotation, FApp::GetDeltaTime(), RotationSpeed);
	SetActorRotation(FRotator(0.f, CurrentRotation, 0.f));
}