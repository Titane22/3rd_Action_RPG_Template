// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_ClearFocus.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONRPG_TEMPLATE_API UBTT_ClearFocus : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTT_ClearFocus();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
