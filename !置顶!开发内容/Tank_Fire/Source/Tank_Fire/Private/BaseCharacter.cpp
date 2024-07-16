// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"

/*
 *	系统头文件的导入
 */
// 粒子特效系统头文件的导入
#include "Particles/ParticleSystem.h"
// 游戏引擎头文件的导入
#include "Kismet/GameplayStatics.h"
// 静态网格头文件的导入
#include "Components/StaticMeshComponent.h"
// 粒子组件组件头文件的导入
#include "Particles/ParticleSystemComponent.h"

/*
 *	自定义头文件的导入
 */
#include "HealthComponent.h"

/*
 *	构造函数
 *	功能：实习了弹簧臂组件 摄像机组件的初始化
 *		  生命组件的导入
 */
ABaseCharacter::ABaseCharacter()
{
	// 开启默认的Tick函数
	//  Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 生命组件的设置
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseCharacter::DeadExplosionFunction()
{
	if (DeadExplosion)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeadExplosion, GetActorLocation());
	}
}

/*
 *	核心功能
 *	功能：当坦克被攻击时，调用TakeDamage函数，当坦克血量小于等于最大血量的一半时，播放粒子特效，当坦克血量小于等于0时，销毁坦克
 *	      同时设置击中击事件广播，并且设置死亡事件广播 便于实现游戏的胜负逻辑判断 实现游戏得分逻辑的实现
 *		  设置对应的赋值变量避免函数重复调用引起BUG
 *	注意：需要加上对空指针的判断以防程序调用空指针引起程序崩溃
 */

void ABaseCharacter::TakeDamage(float Amount)
{
	// 判断是否存在生命组件
	if (HealthComponent)
	{
		// 通过调生命组件的TakeDamage函数，传入伤害值
		HealthComponent->TakeDamage(Amount);

		// 判断血量是否小于等于0
		if (HealthComponent != 0)
		{
			// 触发击中击事件
			OnHit.Broadcast();
		}

		// 判断血量是否小于等于最大血量的一半
		if (HealthComponent->GetHealth() <= HealthComponent->MaxHealth / 2 && !ishurt)
		{
			// 设置受伤事件 避免重复调用
			ishurt = true;
			// 播放粒子特效并保存对粒子特效组件的引用
			// 调用attacheed让粒子特效跟随玩家移动
			ActiveExplosionEffect = UGameplayStatics::SpawnEmitterAttached(ExplosionEffect, GetRootComponent());
		}

		if (isDead && !Dead)
		{
			// 设置参数 避免重复调用
			Dead = true;

			// 触发死亡事件
			OnDeath.Broadcast();

			// 死亡以后断开行为树
			StopMove();

			// 如果引擎组件存在，则输出字符串
			// if (GEngine)
			//{
			//	//测试用
			//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("你杀死了一名敌人"));
			// }

			// 设置定时器，6秒后触发爆炸粒子特效
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AACharacter::DeadExplosionFunction, 6.0f, false);

			// 设置定时器，10秒后销毁坦克
			GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, this, &AACharacter::DelayedDestroy, 10.0f, false); // !!!!}
		}
	}
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

/*
 *	延迟死亡函数
 *	功能：延迟销毁坦克 调用死亡爆炸特效
 *	注意：需要加上对空指针的判断以防程序调用空指针引起程序崩溃
 */
void ABaseCharacter::DelayedDestroy()
{

	// 检查特效组件指针是否为空
	if (ActiveExplosionEffect)
	{
		// 关闭特效
		ActiveExplosionEffect->Deactivate();
		// 销毁临时特效组件
		ActiveExplosionEffect->DestroyComponent();
	}

	// 销毁坦克
	Destroy();
}