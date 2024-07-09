// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include"ACharacter.h"
#include"EnemyAIPerceptionComponent.h"
#include"BehaviorTree/BlackboardComponent.h"

AEnemyAIController::AEnemyAIController()
{
	AIPerception = CreateDefaultSubobject<UEnemyAIPerceptionComponent>("AIPerception");
	SetPerceptionComponent(*AIPerception);
}

void AEnemyAIController::OnPossess(APawn* inPawn)
{
	Super::OnPossess(inPawn);

	AACharacter* enemy = Cast<AACharacter>(inPawn);

	if (enemy)
	{
		RunBehaviorTree(enemy->BehaviorTreeAsset);
	}
}

void AEnemyAIController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	AActor *player=GetFocusActor();
	if (player)
	{

		SetFocus(player);
	}
	else
	{
		SetFocus(nullptr);
	}
}

AActor* AEnemyAIController::GetFocusActor()
{
	if (!GetBlackboardComponent())return nullptr;

	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(focusKeyName));
}
