// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Enemy/I_EnemyAI.h"
#include "BTT_SetMovementSpeed.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONRPG_TEMPLATE_API UBTT_SetMovementSpeed : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTT_SetMovementSpeed();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OtherComp, uint8* NodeMemory) override;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	EMovementState State = EMovementState::Idle;
};
