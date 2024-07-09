// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackPlayer.h"
#include"AIController.h"
#include"ACharacter.h"
#include"BehaviorTree/BlackboardComponent.h"

UAttackPlayer::UAttackPlayer()
{
	NodeName = "Attack Player";
}

EBTNodeResult::Type UAttackPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* controller = OwnerComp.GetAIOwner();
	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();

	if (!controller || !blackboard)return EBTNodeResult::Failed;

	//需要替换的地方
	AACharacter* enemy = Cast<AACharacter>(controller->GetPawn());

	if(!enemy)return EBTNodeResult::Failed;

	enemy->Fire();

	return EBTNodeResult::Succeeded;
}
