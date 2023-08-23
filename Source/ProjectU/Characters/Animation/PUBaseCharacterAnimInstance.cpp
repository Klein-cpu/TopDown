// Fill out your copyright notice in the Description page of Project Settings.


#include "PUBaseCharacterAnimInstance.h"

#include "GameFramework/PawnMovementComponent.h"
#include "ProjectU/Characters/PUBaseCharacter.h"

void UPUBaseCharacterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	CachedBaseCharacter = StaticCast<APUBaseCharacter*>(TryGetPawnOwner());
}

void UPUBaseCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if(!CachedBaseCharacter.IsValid())
	{
		return;
	}
	UMovementComponent* CharacterMovement = CachedBaseCharacter->GetMovementComponent();
	Speed = CharacterMovement->Velocity.Size();
	bIsMoving = FMath::IsNearlyZero(Speed) ? false : true;
}
