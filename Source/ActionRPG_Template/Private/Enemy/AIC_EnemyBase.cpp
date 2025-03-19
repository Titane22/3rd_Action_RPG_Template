// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/AIC_EnemyBase.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy/I_EnemyAI.h"
#include "GameFramework/Character.h"

AAIC_EnemyBase::AAIC_EnemyBase()
	:Super()
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
}

void AAIC_EnemyBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (BlackboardComp && BehaviorTreeAsset && BehaviorTreeAsset->BlackboardAsset)
	{
		BlackboardComp->InitializeBlackboard(*(BehaviorTreeAsset->BlackboardAsset));

		RunBehaviorTree(BehaviorTreeAsset);

		// 약간의 지연 후 플레이어 찾기 시도
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
		{
			if (ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
			{
				SetStateAsPassive();
			}
		}, 1.0f, false);
	}
}

void AAIC_EnemyBase::SetStateAsPassive()
{
	if (BlackboardComp && BehaviorTreeAsset && BehaviorTreeAsset->BlackboardAsset)
	{
		BlackboardComp->SetValueAsEnum(StateKeyName, static_cast<uint8>(EAIState::Passive));
	}
}

void AAIC_EnemyBase::SetStateAsAttacking(AActor* TargetActor)
{
	if (TargetActor && BlackboardComp && BehaviorTreeAsset && BehaviorTreeAsset->BlackboardAsset)
	{
		BlackboardComp->SetValueAsObject(AttackTargetKeyName, TargetActor);
		BlackboardComp->SetValueAsEnum(StateKeyName, static_cast<uint8>(EAIState::Attacking));
	}
}
