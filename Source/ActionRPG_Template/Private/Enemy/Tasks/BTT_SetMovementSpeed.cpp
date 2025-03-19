// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Tasks/BTT_SetMovementSpeed.h"
#include "AIController.h"
#include "Enemy/TemplateEnemyBase.h"

UBTT_SetMovementSpeed::UBTT_SetMovementSpeed()
{
	NodeName = TEXT("Set Movement Speed");
}

EBTNodeResult::Type UBTT_SetMovementSpeed::ExecuteTask(UBehaviorTreeComponent& OtherComp, uint8* NodeMemory)
{
	AAIController* AIController = OtherComp.GetAIOwner();
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}
	ATemplateEnemyBase* Enemy = Cast<ATemplateEnemyBase>(AIController->GetPawn());
	if (!Enemy)
	{
		return EBTNodeResult::Failed;
	}
	Enemy->SetMovementSpeed(State);

	return EBTNodeResult::Succeeded;
}
