// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/AIC_EnemyBase.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"
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
				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Player Found"));
				BlackboardComp->SetValueAsObject(AttackTargetKeyName, PlayerCharacter);
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Player Not Found"));
			}
		}, 1.0f, false);
	}
	else if (!BlackboardComp)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("BlackboardComp"));

	}
	else if (!BehaviorTreeAsset)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("BehaviorTreeAsset"));

	}
	else if (!BehaviorTreeAsset->BlackboardAsset)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("BehaviorTreeAsset->BlackboardAsset"));

	}
}
