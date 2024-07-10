// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "GetNextTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class TANK_FIRE_API UGetNextTaskNode : public UBTTaskNode
{
	GENERATED_BODY()
public:

	UGetNextTaskNode();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="AI")
	float radius = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	FBlackboardKeySelector AimLocationKey;
};
