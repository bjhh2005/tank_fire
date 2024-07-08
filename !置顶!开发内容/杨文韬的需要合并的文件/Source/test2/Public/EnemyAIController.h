// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class TEST2_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	AEnemyAIController();
	virtual void OnPossess(APawn* inPawn)override;
	virtual void Tick(float deltaTime)override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UEnemyAIPerceptionComponent* AIPerception;


};
