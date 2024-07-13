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
	//�õ�aicontroller

	AAIController* controller = OwnerComp.GetAIOwner();
	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();

	if (!controller || !blackboard)return EBTNodeResult::Failed;

	//�õ�aicontroller��Ӧ�Ľ�ɫ
	APawn* pawn = controller->GetPawn();
	if (!pawn)return EBTNodeResult::Failed;

	//�õ�����ϵͳ
	UNavigationSystemV1* navSystem=  FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
	if (!navSystem)return  EBTNodeResult::Failed;

	FNavLocation navLocation;
	bool found=navSystem->GetRandomReachablePointInRadius(pawn->GetActorLocation(),radius,navLocation );
	if (!found)return  EBTNodeResult::Failed;

	blackboard->SetValueAsVector(AimLocationKey.SelectedKeyName, navLocation.Location);

	return EBTNodeResult::Succeeded;

}
