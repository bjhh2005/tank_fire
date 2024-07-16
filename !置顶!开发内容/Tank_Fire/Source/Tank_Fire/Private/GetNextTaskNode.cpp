// Fill out your copyright notice in the Description page of Project Settings.


/*
*	系统头文件
*/

#include"BehaviorTree/BlackboardComponent.h"
#include"NavigationSystem.h"

/*
*	自定义头文件
*/

#include"AIController.h"
#include "GetNextTaskNode.h"

//构造函数
UGetNextTaskNode::UGetNextTaskNode()
{
	//设置节点名称
	NodeName = "Next Point";
}

/*
*	函数名称：ExecuteTask
*	功能：获取下一个任务的位置
*	参数：
* 		OwnerComp：行为树组件
* 		NodeMemory：节点内存
* 	返回值：
*		EBTNodeResult::Type
*/

EBTNodeResult::Type UGetNextTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//获取AIController
	AAIController* controller = OwnerComp.GetAIOwner();
	//设置Blackboard组件
	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();

	//检测是否获取控制器 如果没有 则返回失败
	if (!controller || !blackboard)
	{
		return EBTNodeResult::Failed;
	}

	//获取AIController所控制的Pawn
	APawn* pawn = controller->GetPawn();
	if (!pawn) 
	{
		//如果获取失败 返回失败
		return EBTNodeResult::Failed;
	}

	//获取导航系统
	UNavigationSystemV1* navSystem=  FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
	if (!navSystem)
	{
		//如果获取失败 返回失败
		return EBTNodeResult::Failed;
	}

	//获取随机位置
	FNavLocation navLocation;
	//获取随机位置，实现随机游走
	bool found=navSystem->GetRandomReachablePointInRadius(pawn->GetActorLocation(),radius,navLocation );
	if (!found)
	{
		return  EBTNodeResult::Failed;
	}
	blackboard->SetValueAsVector(AimLocationKey.SelectedKeyName, navLocation.Location);

	//返回成功
	return EBTNodeResult::Succeeded;
}