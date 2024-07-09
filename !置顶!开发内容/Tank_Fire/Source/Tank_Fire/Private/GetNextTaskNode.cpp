// Fill out your copyright notice in the Description page of Project Settings.


#include "GetNextTaskNode.h"
#include"BehaviorTree/BlackboardComponent.h"
#include"AIController.h"
#include"NavigationSystem.h"


UGetNextTaskNode::UGetNextTaskNode()
{
	NodeName = "Next Point";
}

EBTNodeResult::Type UGetNextTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//拿到aicontroller

	AAIController* controller = OwnerComp.GetAIOwner();
	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();

	if (!controller || !blackboard)return EBTNodeResult::Failed;

	//拿到aicontroller对应的角色
	APawn* pawn = controller->GetPawn();
	if (!pawn)return EBTNodeResult::Failed;

	FVector location = pawn->GetActorLocation();

	if (isPlayerCenter)
	{
		AActor* actor = Cast<AActor>(blackboard->GetValueAsObject(CenterKey.SelectedKeyName));
		location = actor->GetActorLocation();
	}

	//拿到导航系统
	UNavigationSystemV1* navSystem=  FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
	if (!navSystem)return  EBTNodeResult::Failed;

	FNavLocation navLocation;
	bool found=navSystem->GetRandomReachablePointInRadius(location,radius,navLocation );
	if (!found)return  EBTNodeResult::Failed;

	blackboard->SetValueAsVector(AimLocationKey.SelectedKeyName, navLocation.Location);

	return EBTNodeResult::Succeeded;

}
