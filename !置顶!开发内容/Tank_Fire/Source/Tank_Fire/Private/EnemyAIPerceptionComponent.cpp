// Fill out your copyright notice in the Description page of Project Settings.

/*
* 系统类头文件
*/
#include"Perception/AISense_Sight.h"

/*
* 自定义头文件
*/

//感知感知组件
#include "EnemyAIPerceptionComponent.h"
//智能控制类
#include"AIController.h"
//测试模式
#include"MyActor.h"
//敌方角色类
#include"ACharacter.h"
//玩家类
#include "myWheeledVehiclePawn.h"

/*
*	函数名：GetPerceptionPlayer
*	功能描述：获取感知感知组件感知到的玩家
*   返回值： 感知到的玩家
*/
AActor* UEnemyAIPerceptionComponent::GetPerceptionPlayer()
{
	//获取感知感知组件感知到的所有智能体
	TArray<AActor*>percptionActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), percptionActors);

	//判断是否感知到玩家类 如果为0则返回空
	if (percptionActors.Num() == 0)return nullptr;

	//获取智能控制类 转化为智能控制类
	AAIController* controller = Cast<AAIController>(GetOwner());
	if (!controller)return nullptr;

	//获取智能控制类所控制的玩家
	APawn* pawn = controller->GetPawn();
	if (!pawn)return nullptr;

	//设置感知距离
	float bastDistance = MAX_FLT;
	//遍历感知到的智能体
	AActor* playerActor = nullptr;

	//遍历感知到的智能体
	for (AActor* currentActor : percptionActors)
	{
		//获取所有玩家类的智能体
		AWheeledVehiclePawn* player = Cast<AWheeledVehiclePawn>(currentActor);
		
		//判断是否为玩家类
		if (player)
		{
			//测试用 判断是否获取玩家
			//UE_LOG(LogTemp, Display, TEXT("see you again"));
				
			//获取玩家与智能体之间的距离
			float distance = (player->GetActorLocation() - pawn->GetActorLocation()).Size();
			//判断距离
			if (distance < bastDistance)
			{
				//获取距离
				bastDistance = distance;
			}	
			//获取玩家
			playerActor = player;
			//如果获取到玩家则跳出循环
			break;
		}
	}

	//返回玩家类
	return playerActor;
}
