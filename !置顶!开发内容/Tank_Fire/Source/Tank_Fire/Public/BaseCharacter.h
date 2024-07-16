// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/*
 *	测试类 可伤害玩家基类
 *	类名：ABaseCharacter
 *   继承自：AActor
 *	创建日期：2024年7月4日
 *	继承自：ACharacter
 *	简述：实现可被伤害的玩家基类，实现死亡逻辑特效的播放等等。
 */

/*
 *	作者：张瑞欣
 * 	日期：2024年7月4日
 * 	版本：1.0
 * 	更新功能：设置可被伤害的玩家基类，实现死亡逻辑特效的播放等等。
 */

/*
 *	作者：张瑞欣
 * 	日期：2024年7月15日
 * 	版本：1.1
 * 	更新功能：根据ACharacter类的功能，加入了死亡事件受伤事件等用于游戏总体测试。
 */

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

// 导入生命组件
class UHealthComponent;

// 定义死亡事件
DECLARE_DYNAMIC_MULTICAST_DELEGATE(Fdead);

UCLASS()
class TANK_FIRE_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	/*
	 *	系统函数
	 */

	ABaseCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*
	 * 	自定义函数
	 */

public:
	/*
	 *	坦克受伤
	 *	函数名：TakeDamage
	 *	功能：实现坦克受伤
	 *		  实现坦克死亡以后触发死亡事件
	 *		  实现坦克受伤以后触发受伤事件
	 *		  实现坦克血量低于一半触发特效
	 *	参数：Amount 伤害数值
	 *	返回：无
	 */
	UFUNCTION(BlueprintCallable)
	void TakeDamage(float Amount);

protected:
	/*
	 *	死亡爆炸函数
	 *	函数名：DeadExplosionFunction
	 *	功能：辅助函数，实现延迟爆炸，从而实现坦克死亡后一段时间后再爆炸，起到残骸的效果
	 *	参数：无
	 *	返回：无
	 */
	void DelayedDestroy();

	/*
	 *	实现延迟死亡
	 * 	函数名：DelayedDestroy
	 * 	功能：辅助函数，实现坦克死亡后，延迟一段时间再销毁坦克
	 * 	参数：无
	 * 	返回：无
	 */
	void DeadExplosionFunction();

	/*
	 *	组件导入
	 */

	// 生命组件的导入
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HealthComponent")
	UHealthComponent *HealthComponent;

	// 特效组件的引用
	UPROPERTY()
	UParticleSystemComponent *ActiveExplosionEffect;

	/*
	 *	属性设置
	 */

	// 特效设置
	UPROPERTY(EditAnywhere, Category = "特效设置")
	UParticleSystem *ExplosionEffect;

	// 特效设置
	UPROPERTY(EditAnywhere, Category = "特效设置")
	UParticleSystem *DeadExplosion;

	/*
	 *	变量设置
	 */

public:
	// 导入ShouldDead属性变量 用于UE引擎中的游戏模式的开发
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DEAD")
	bool ShouldDead = false;

	// 判断是否受伤
	bool ishurt = false;
	// 判断是否触发死亡
	bool Dead = false;
	// 判断血量是否低于0
	bool isDead = false;

protected:
	// 设置生命

	float health;

	// 计时器句柄
	FTimerHandle TimerHandle;

	// 定时器句柄
	FTimerHandle DestroyTimerHandle;

	// 死亡事件
	UPROPERTY(BlueprintAssignable, Category = "Events")
	Fdead OnDeath;

	// 受伤事件
	UPROPERTY(BlueprintAssignable, Category = "Events")
	Fdead OnHit;
};
