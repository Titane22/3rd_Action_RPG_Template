// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_DefaultAttack.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONRPG_TEMPLATE_API UBTT_DefaultAttack : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTT_DefaultAttack();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	// 태스크가 중단될 때 호출되는 함수
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UFUNCTION()
	void FinishingAttacking();

	UBehaviorTreeComponent* CachedOwnerComp;
};
