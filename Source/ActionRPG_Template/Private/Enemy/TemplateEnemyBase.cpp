// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy/TemplateEnemyBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ATemplateEnemyBase::ATemplateEnemyBase()
	:Super()
{
	
}

float ATemplateEnemyBase::SetMovementSpeed(EMovementState Speed)
{
	switch (Speed)
	{
	case EMovementState::Idle:
		GetCharacterMovement()->MaxWalkSpeed = 0.0f;
		break;
	case EMovementState::Walking:
		GetCharacterMovement()->MaxWalkSpeed = 100.0f;
		break;
	case EMovementState::Jogging:
		GetCharacterMovement()->MaxWalkSpeed = 300.0f;
		break;
	case EMovementState::Sprinting:
		GetCharacterMovement()->MaxWalkSpeed = 550.0f;
		break;
	default:
		break;
	}
	return GetCharacterMovement()->MaxWalkSpeed;
}

void ATemplateEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
	{
		BossAnim = AnimInstance;
	}

	// 캐릭터 이동 설정
	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = false;
}

void ATemplateEnemyBase::Attack()
{
	if (!BossAnim)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attack: BossAnim is null"));
		return;
	}

	if (UAnimMontage* AnimMont = LoadObject<UAnimMontage>(nullptr, TEXT("/Game/ThirdPerson/BossyEnemy/Animations/RootMotion/Attacks/AM_Boss_Swing")))
	{
		BossAnim->Montage_Play(AnimMont);
		
		FOnMontageEnded EndDelegate;
		EndDelegate.BindUObject(this, &ATemplateEnemyBase::OnAttackMontageEnded);
		BossAnim->Montage_SetEndDelegate(EndDelegate, AnimMont);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Attack: Failed to load animation montage"));
	}
}

void ATemplateEnemyBase::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	OnAttackEnd.Broadcast();
	
	if (bInterrupted)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attack montage was interrupted"));
	}
}