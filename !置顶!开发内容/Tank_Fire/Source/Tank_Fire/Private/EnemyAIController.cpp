// Fill out your copyright notice in the Description page of Project Settings.


/*
* 自定义头文件
*/

#include "EnemyAIController.h"
//敌人类导入
#include"ACharacter.h"
//敌人AI感知组件导入
#include"EnemyAIPerceptionComponent.h"

// Called when the game starts or when spawned
AEnemyAIController::AEnemyAIController()
{
	//创建感知组件
	AIPerception = CreateDefaultSubobject<UEnemyAIPerceptionComponent>("AIPerception");
	//设置感知组件
	SetPerceptionComponent(*AIPerception);
}

/*
*	函数名：OnPossess
*	作用：转换为敌人类 实行感知与运行行为树
*/
void AEnemyAIController::OnPossess(APawn* inPawn)
{
	Super::OnPossess(inPawn);

	//转换为敌人类
	AACharacter* enemy = Cast<AACharacter>(inPawn);

	if (enemy)
	{
		//运行行为树
		RunBehaviorTree(enemy->BehaviorTreeAsset);
	}
}
/*
*	函数名：Tick
*	作用：感知玩家位置，实现枪口对转向玩家位置
*/
void AEnemyAIController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	//感知玩家位置
	AActor *player=AIPerception->GetPerceptionPlayer();
	if (player)
	{
		//设置玩家为焦点
		SetFocus(player);
	}
}
