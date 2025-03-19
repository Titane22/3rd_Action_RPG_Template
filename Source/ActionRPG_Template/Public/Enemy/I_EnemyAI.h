// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "I_EnemyAI.generated.h"

UENUM(BlueprintType)
enum class EMovementState : uint8
{
	Idle		UMETA(DisplayName = "Idle"),
	Walking		UMETA(DisplayName = "Walking"),
	Jogging		UMETA(DisplayName = "Jogging"),
	Sprinting	UMETA(DisplayName = "Sprinting")
};

UENUM(BlueprintType)
enum class EAIState : uint8
{
	Passive			UMETA(DisplayName = "Passive"),
	Attacking		UMETA(DisplayName = "Attacking"),
	Frozen			UMETA(DisplayName = "Frozen"),
	Investigating	UMETA(DisplayName = "Investigating"),
	Dead			UMETA(DisplayName = "Dead")
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UI_EnemyAI : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ACTIONRPG_TEMPLATE_API II_EnemyAI
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual float SetMovementSpeed(EMovementState Speed) = 0;
};
