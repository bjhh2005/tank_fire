// Fill out your copyright notice in the Description page of Project Settings.


#include "myWheeledVehiclePawn.h"
//导入生命组件头文件
#include "HealthComponent.h"
//导入粒子系统头文件
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include"Components/SphereComponent.h"

AmyWheeledVehiclePawn::AmyWheeledVehiclePawn()
{

	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereCollision->InitSphereRadius(500.0f);
	SetRootComponent(SphereCollision);

	//生命组件的设置
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

}


// by 张 辅助函数 延迟摧毁坦克
void AmyWheeledVehiclePawn::DelayedDestroy()
{
	if (ActiveExplosionEffect)
	{
		ActiveExplosionEffect->Deactivate();
		ActiveExplosionEffect->DestroyComponent();
	}
	// 销毁坦克
	Destroy();
}

//by 张
//死亡爆炸特效
void AmyWheeledVehiclePawn::DeadExplosionFunction()
{
	if (DeadExplosion)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeadExplosion, GetActorLocation());
	}
}


void AmyWheeledVehiclePawn::TakeDamage(float Amount)
{
	if (HealthComponent)
	{
		HealthComponent->TakeDamage(Amount);
		if (HealthComponent->GetHealth() <= HealthComponent->MaxHealth / 2 && !ishurt)
		{
			ishurt = true;
			// 播放粒子特效并保存对粒子特效组件的引用
			ActiveExplosionEffect = UGameplayStatics::SpawnEmitterAttached(ExplosionEffect, GetRootComponent());
		}

		if (isDead && !Dead)
		{
			Dead = true;

			////如果引擎组件存在，则输出字符串
			//if (GEngine)
			//{
			//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("你杀死了一名敌人"));
			//}


			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AmyWheeledVehiclePawn::DeadExplosionFunction, 2.5f, false);

			// 设置定时器，5秒后销毁坦克
			GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, this, &AmyWheeledVehiclePawn::DelayedDestroy, 5.0f, false); // !!!!}
		}
	}
}
