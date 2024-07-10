// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include"ACharacter.h"
#include"EnemyAIPerceptionComponent.h"

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

	AActor *player=AIPerception->GetPerceptionPlayer();
	if (player)
	{

		SetFocus(player);
	}
}
