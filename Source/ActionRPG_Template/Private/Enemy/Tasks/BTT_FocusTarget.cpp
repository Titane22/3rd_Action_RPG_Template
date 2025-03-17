// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Tasks/BTT_FocusTarget.h"
#include "AIController.h"
#include "Enemy/TemplateEnemyBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

UBTT_FocusTarget::UBTT_FocusTarget()
{
	NodeName = TEXT("Focus Target");
}

EBTNodeResult::Type UBTT_FocusTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_FocusTarget: AIController is null"));
		return EBTNodeResult::Failed;
	}

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("UBTT_FocusTarget: Blackboard Component is null"));
		return EBTNodeResult::Failed;
	}

	if (AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject(AttackTargetKey.SelectedKeyName)))
	{
		AIController->SetFocus(TargetActor);
		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed;
	}
}
