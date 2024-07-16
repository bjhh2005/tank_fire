// Fill out your copyright notice in the Description page of Project Settings.


#include "ACharacter.h"
#include "BaseCharacter.h"
#include "HealthComponent.h"
#include "myWheeledVehiclePawn.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	//游戏开始时 初始化血量 获取最大值
	health = MaxHealth;
	
}

//
void UHealthComponent::TakeDamage(float Amount)
{
	//如果血量大于0
	if (health  >  0){
		//造成伤害
		health -= Amount;
		//测试使用 用于显示角色伤害
		//UE_LOG(LogTemp, Display, TEXT("Character Damage Amout = %f, Health = %f"), Amount, health);
		
		//如果血量小于等于0
		if (health <= 0)
		{
			//角色死亡
			//获取组件的拥有者
			ABaseCharacter* character1 = Cast<ABaseCharacter>(GetOwner());
			AACharacter* character2 = Cast<AACharacter>(GetOwner());
			AmyWheeledVehiclePawn* character3 = Cast<AmyWheeledVehiclePawn>(GetOwner());

			//判断伤害对象
			if (character1)
			{
				//血量设置为0
				health = 0;
				//播报
				UE_LOG(LogTemp, Display, TEXT("Character Death"));
				//角色死亡
				character1->isDead = true;
			}

			if (character2)
			{
				//血量设置为0
					health = 0;
				//播报
				UE_LOG(LogTemp, Display, TEXT("Character Death"));
				//角色死亡
				character2->isDead = true;
			}

			//玩家角色死亡
			if (character3)
			{
				//血量设置为0
				health = 0;
				//播报
				UE_LOG(LogTemp, Display, TEXT("Character Death"));
				//角色死亡
				character3->isDead = true;
			}
		}
	}

}



// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

