// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIC_EnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONRPG_TEMPLATE_API AAIC_EnemyBase : public AAIController
{
	GENERATED_BODY()
	
public:
	AAIC_EnemyBase();

	virtual void OnPossess(APawn* InPawn) override;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	UBlackboardComponent* BlackboardComp;

	UPROPERTY(EditDefaultsOnly, Category = "Blackboard Keys")
	FName AttackTargetKeyName = FName("AttackTarget");
};
