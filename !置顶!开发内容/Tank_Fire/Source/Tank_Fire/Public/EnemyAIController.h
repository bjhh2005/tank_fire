// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


/*
*	敌人AI控制器实现类
*	继承：AAIController`
*	创建日期：2024年7月7日
*	简述：实现AI的基本功能
*/

/*
 *	作者：杨文韬
 * 	日期：2024年7月7日
 * 	版本：1.0
 * 	更新功能：实现AI的基本功能
 */


#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

UCLASS()
class TANK_FIRE_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	// 调用基类构造函数
	AEnemyAIController();
	// 重写OnPossess函数
	virtual void OnPossess(APawn* inPawn)override;
	// 重写Tick函数
	virtual void Tick(float deltaTime)override;

protected:
	// 感知组件的导入
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UEnemyAIPerceptionComponent* AIPerception;


};
