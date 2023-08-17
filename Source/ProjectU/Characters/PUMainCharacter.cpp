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
		float Current = GetMesh()->GetRelativeRotation().Yaw;
		float Target = FRotator::ZeroRotator.Yaw;
		Target += (Value < 0.f) ? ((Current > -180.f && Current < 0.f) ? -180.f : 180.f) : 0.f;
		if(!FMath::IsNearlyZero(FMath::Abs(Target-Current)) && !FMath::IsNearlyEqual(FMath::Abs(Target-Current), 360.f))
		{
			Current = FMath::FInterpTo(Current, Target, FApp::GetDeltaTime(), RotationSpeed);
			GetMesh()->SetRelativeRotation(FRotator(0.f, Current, 0.f));
		}
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void APUMainCharacter::MoveRight(float Value)
{
	Super::MoveRight(Value);
	if(!FMath::IsNearlyZero(Value))
	{
		float Current = GetMesh()->GetRelativeRotation().Yaw;
		float Target = FRotator::ZeroRotator.Yaw + 90.f;
		Target -= (Value < 0.f) ? 180.f : 0.f;
		if(!FMath::IsNearlyZero(FMath::Abs(Target-Current)) && !FMath::IsNearlyEqual(FMath::Abs(Target-Current), 360.f))
		{
			if(FMath::Abs(Target - (360.f + Current)) < FMath::Abs(Target - Current))
			{
				Current += 360.f;
			}
			if(Target + FMath::Abs(360.f - Current) < FMath::Abs(Target - Current))
			{
				Current -= 360.f;
			}
			
			Current = FMath::FInterpTo(Current, Target, FApp::GetDeltaTime(), RotationSpeed);
			GetMesh()->SetRelativeRotation(FRotator(0.f, Current, 0.f));
	 	}
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void APUMainCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	FApp::SetDeltaTime(DeltaSeconds);
}
