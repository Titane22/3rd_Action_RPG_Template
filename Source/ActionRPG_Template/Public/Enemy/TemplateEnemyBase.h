// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TemplatePlayer.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "TemplateEnemyBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackEndDelegate);

/**
 * 
 */
UCLASS()
class ACTIONRPG_TEMPLATE_API ATemplateEnemyBase : public ATemplatePlayer
{
	GENERATED_BODY()
	
public:
	ATemplateEnemyBase();

	void Attack();
	
	// 공격 종료 델리게이트
	UPROPERTY(BlueprintAssignable, Category = "Combat")
	FOnAttackEndDelegate OnAttackEnd;
	
protected:
	virtual void BeginPlay() override;

	UAnimInstance* BossAnim;

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
};
