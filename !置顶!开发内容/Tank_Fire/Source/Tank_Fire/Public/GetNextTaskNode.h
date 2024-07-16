// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/*
*	作者：杨文韬
* 	日期：2024年7月8日
* 	版本：1.0
* 	更新功能：设置AI感知范围 行动路径的结点
*			  获取下一个任务的结点
* 	继承自 UBTTaskNode
*/

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "GetNextTaskNode.generated.h"


UCLASS()
class TANK_FIRE_API UGetNextTaskNode : public UBTTaskNode
{
	GENERATED_BODY()
public:
	//构造函数
	UGetNextTaskNode();

	/*
	*	函数名称：ExecuteTask
	*	功能：获取下一个任务的位置
	*	参数：
	* 		OwnerComp：行为树组件
	* 		NodeMemory：节点内存
	* 	返回值：
	*		EBTNodeResult::Type
	*/
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	//感知范围设定
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="AI")
	float radius = 1000;

	//获取下一个任务的
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	FBlackboardKeySelector AimLocationKey;
};
