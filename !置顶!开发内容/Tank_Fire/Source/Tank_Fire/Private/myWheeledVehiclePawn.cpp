// Fill out your copyright notice in the Description page of Project Settings.


#include "myWheeledVehiclePawn.h"
//生命组件的导入
#include "HealthComponent.h"
//特效组件的导入
#include "Particles/ParticleSystem.h"
//引擎头文件的导入
#include "Kismet/GameplayStatics.h"
//静态网格体组件的导入
#include "Components/StaticMeshComponent.h"
//粒子系统组件的导入
#include "Particles/ParticleSystemComponent.h"
//球形组件的导入
#include"Components/SphereComponent.h"

//构造函数
AmyWheeledVehiclePawn::AmyWheeledVehiclePawn()
{
	//生命组件的绑定
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}



/*
 *	延迟死亡函数
 *	功能：延迟销毁坦克 调用死亡爆炸特效
 *	注意：需要在销毁坦克主体的同时消除坦克头部和武器
 *		  需要加上对空指针的判断以防程序调用空指针引起程序崩溃
 */
void AmyWheeledVehiclePawn::DelayedDestroy()
{
	//关闭特效
	if (ActiveExplosionEffect)
	{
		//停止特效
		ActiveExplosionEffect->Deactivate();
		//销毁特效组件
		ActiveExplosionEffect->DestroyComponent();
	}
	//销毁坦克
	Destroy();
}
// 死亡爆炸函数
// 功能：创建死亡爆炸特效
void AmyWheeledVehiclePawn::DeadExplosionFunction()
{
	// 判断死亡爆炸特效指针是否为空
	if (DeadExplosion)
	{
		// 获取当前世界位置 在当前世界位置创建特效
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeadExplosion, GetActorLocation());
	}
}

// 恢复血量函数
// 功能：恢复血量
// 注意：需要在恢复血量时清除特效
void AmyWheeledVehiclePawn::RecoveryHealth()
{
	//重设状态
	ishurt = false;

	//爆炸的时候播放声音
	UGameplayStatics::PlaySoundAtLocation(this, FixSound, GetActorLocation());
	//恢复血量
	HealthComponent->Recovery();

	//清除特效
	if(ActiveExplosionEffect)
		ActiveExplosionEffect->Deactivate();
}

/*
 *	核心功能
 *	功能：当坦克被攻击时，调用TakeDamage函数，当坦克血量小于等于最大血量的一半时，播放粒子特效，当坦克血量小于等于0时，销毁坦克
 *	      同时设置击中击事件广播，并且设置死亡事件广播 便于实现游戏的胜负逻辑判断 实现游戏得分逻辑的实现
 *		  设置对应的赋值变量避免函数重复调用引起BUG
 *	注意：需要加上对空指针的判断以防程序调用空指针引起程序崩溃
 */
void AmyWheeledVehiclePawn::TakeDamage(float Amount)
{
	//判断生命组件指针是否为空
	if (HealthComponent)
	{
		//调用生命组件的TakeDamage函数
		HealthComponent->TakeDamage(Amount);

		//判断血量小于等于最大血量的一半时，播放粒子特效
		if (HealthComponent->GetHealth() <= HealthComponent->MaxHealth / 2 && !ishurt)
		{
			//设置参数 避免重复播放
			ishurt = true;
			//创建特效
			//设置特效跟随角色位置
			ActiveExplosionEffect = UGameplayStatics::SpawnEmitterAttached(ExplosionEffect, GetRootComponent());
		}

		//判断血量小于等于0时，销毁坦克
		if (isDead && !Dead)
		{
			//设置参数 避免重复调用
			Dead = true;

			//输出调试信息
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("菜 就多练 玩不起 就别玩"));
			}

			//播放特效
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AmyWheeledVehiclePawn::DeadExplosionFunction, 0.0f, false);
			//销毁角色
			DelayedDestroy();
		}
	}
}

