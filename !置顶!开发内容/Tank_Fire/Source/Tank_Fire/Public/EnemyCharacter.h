// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/*
*	基于ABaseCharacter的敌人类
*	测试使用
* 	C++类中无实际内容
*	作者：张瑞欣
*	日期：2024年7月4日
*/

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TANK_FIRE_API AEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
	//构造函数
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
