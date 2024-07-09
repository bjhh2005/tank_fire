// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AttackPlayer.generated.h"

/**
 * 
 */
UCLASS()
class TANK_FIRE_API UAttackPlayer : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UAttackPlayer(); 
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
