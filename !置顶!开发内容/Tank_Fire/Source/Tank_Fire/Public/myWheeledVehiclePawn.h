// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/*
 *	玩家坦克基类
 *	类名：AmyWheeledVehiclePawn
 *  继承自：AWheeledVehiclePawn
 *	创建日期：2024年7月5日
 *	简述：玩家坦克类的设置
 */

 /*
  *	作者：张瑞欣
  * 	日期：2024年7月6日
  * 	版本：1.0
  * 	更新功能：实现开火 死亡爆炸 音效设置 血量设置 死亡爆炸等音效接口
  */

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "myWheeledVehiclePawn.generated.h"

//导入生命组件
class UHealthComponent;

UCLASS()
class TANK_FIRE_API AmyWheeledVehiclePawn : public AWheeledVehiclePawn
{
	GENERATED_BODY()
	
public:
	
	/*
	* 系统函数
	*/

	//  Sets default values for this pawn's properties
	AmyWheeledVehiclePawn();

	//by Zhanng
	//伤害函数

	/*
	*  自定义函数
	*/
	UFUNCTION(BlueprintCallable)
	void TakeDamage(float Amount);


protected:
	//辅助函数 帮助销毁
	void DelayedDestroy();

	//恢复生命值函数
	UFUNCTION(BlueprintCallable)
	void RecoveryHealth();


	//死亡爆炸特效函数
	void DeadExplosionFunction();



	/*
	* 组件导入
	*/

protected:


	// 生命组件
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HealthComponent")
	UHealthComponent* HealthComponent;
	
	// 特效组件的引入
	UPROPERTY()
	UParticleSystemComponent* ActiveExplosionEffect;
	
	//特效设置
	UPROPERTY(EditAnywhere, Category = "Emitter")
	UParticleSystem* ExplosionEffect;

	/*
	* 参数设置
	*/
public:

	//辅助变量
	//判断血量低于一半
	bool ishurt = false;
	//判断是否触发死亡爆炸
	bool Dead = false;
	//判是否死亡
	bool isDead = false;

protected:

	//特效设置
	UPROPERTY(EditAnywhere, Category = "Emitter")
	UParticleSystem* DeadExplosion;

	//声音设置
	UPROPERTY(EditAnywhere, Category = "修复声音")
	USoundBase* FixSound;

	// 定时器
	FTimerHandle TimerHandle;

	// 定时器
	FTimerHandle DestroyTimerHandle;

	//生命值恢复速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float RecoveryHealthRate = 0.3;

};
