// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/*
*	作者：杨文韬
* 	日期：2024年7月7日
* 	版本：1.0
* 	更新功能：构建AI的感知组件
* 	继承自 UAIPerceptionComponent
*/


#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "EnemyAIPerceptionComponent.generated.h"

//导入测试玩家类
class AMyActor;

/**
 * 
 */
UCLASS()
class TANK_FIRE_API UEnemyAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()
	
public:

	/*
	* 获取感知到的玩家
	* !核心功能
	*/
	AActor* GetPerceptionPlayer();

	//导入玩家类
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponClass")
	TSubclassOf<AMyActor> MeClass;
	
};
