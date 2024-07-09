// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class TANK_FIRE_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	AEnemyAIController();	
	virtual void OnPossess(APawn* inPawn)override;
	virtual void Tick(float deltaTime)override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UEnemyAIPerceptionComponent* AIPerception;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName focusKeyName = "PlayerActor";

private:

	AActor* GetFocusActor();

};
