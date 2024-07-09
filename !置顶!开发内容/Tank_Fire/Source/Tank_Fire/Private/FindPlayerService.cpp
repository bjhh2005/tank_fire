// Fill out your copyright notice in the Description page of Project Settings.


#include "FindPlayerService.h"
#include"EnemyAIController.h"
#include"BehaviorTree/BlackboardComponent.h"
#include"EnemyAIPerceptionComponent.h"


UFindPlayerService::UFindPlayerService()
{
	NodeName = "FindPlayer";
}

void UFindPlayerService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
	if (blackboard)
	{
		AEnemyAIController* controller = Cast<AEnemyAIController>(OwnerComp.GetOwner());

		UEnemyAIPerceptionComponent* aiperception = controller->GetComponentByClass<UEnemyAIPerceptionComponent>();

		if (aiperception)
		{
			blackboard->SetValueAsObject(PlayerActorKey.SelectedKeyName, aiperception->GetPerceptionPlayer());

		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
