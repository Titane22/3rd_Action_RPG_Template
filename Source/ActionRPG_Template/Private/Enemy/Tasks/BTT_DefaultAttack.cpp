// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Tasks/BTT_DefaultAttack.h"
#include "AIController.h"
#include "Enemy/TemplateEnemyBase.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

UBTT_DefaultAttack::UBTT_DefaultAttack()
{
	NodeName = TEXT("Default Attack");
}

EBTNodeResult::Type UBTT_DefaultAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		UE_LOG(LogTemp, Error, TEXT("BTT_DefaultAttack: AIController is null"));
		return EBTNodeResult::Failed;
	}

	ATemplateEnemyBase* Enemy = Cast<ATemplateEnemyBase>(AIController->GetPawn());
	if (!Enemy)
	{
		UE_LOG(LogTemp, Error, TEXT("BTT_DefaultAttack: Enemy is null"));
		return EBTNodeResult::Failed;
	}

	CachedOwnerComp = &OwnerComp;
	if (!CachedOwnerComp)
	{
		UE_LOG(LogTemp, Error, TEXT("BTT_DefaultAttack: Failed to cache OwnerComp"));
		return EBTNodeResult::Failed;
	}

	// 공격 종료 이벤트에 바인딩
	if (!Enemy->OnAttackEnd.IsAlreadyBound(this, &UBTT_DefaultAttack::FinishingAttacking))
	{
		Enemy->OnAttackEnd.AddDynamic(this, &UBTT_DefaultAttack::FinishingAttacking);
	}
	
	Enemy->Attack();
	
	return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UBTT_DefaultAttack::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// 태스크가 중단될 때 이벤트 바인딩 해제
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController)
	{
		if (ATemplateEnemyBase* Enemy = Cast<ATemplateEnemyBase>(AIController->GetPawn()))
		{
			if (Enemy->OnAttackEnd.IsAlreadyBound(this, &UBTT_DefaultAttack::FinishingAttacking))
			{
				Enemy->OnAttackEnd.RemoveDynamic(this, &UBTT_DefaultAttack::FinishingAttacking);
			}
		}
	}
	
	return EBTNodeResult::Aborted;
}

void UBTT_DefaultAttack::FinishingAttacking()
{
	if (CachedOwnerComp)
	{
		FinishLatentTask(*CachedOwnerComp, EBTNodeResult::Succeeded);
		
		UE_LOG(LogTemp, Display, TEXT("Attack finished successfully"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("BTT_DefaultAttack: FinishingAttacking called but OwnerComp is null"));
	}
}
