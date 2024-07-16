// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/*
 *	玩家子弹基类
 *	类名：ABaseBullet
 *   继承自：AActor
 *	创建日期：2024年7月5日
 *	简述：实现玩家子弹基类，实现子弹的移动，伤害判定，死亡事件，特效设置，声音设置，子弹生命周期设置。
 */

/*
 *	作者：张瑞欣
 * 	日期：2024年7月5日
 * 	版本：1.0
 * 	更新功能：设置子弹的移动，伤害判定，死亡事件，特效设置，声音设置，子弹生命周期设置。
 *			  加入生命组件，添加子弹伤害属性，设置子弹的伤害。
 */

/*
 *	作者：张瑞欣
 * 	日期：2024年7月8日
 * 	版本：2.0
 * 	更新功能：引入了敌方坦克基类 实现了对敌方坦克的伤害 碰撞的爆炸
 */

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseBullet.generated.h"

// sphere组件 设置碰撞体积
class USphereComponent;
// 移动组件 实现子弹发射移动
class UProjectileMovementComponent;

UCLASS()
class TANK_FIRE_API ABaseBullet : public AActor
{
	GENERATED_BODY()

public:
	/*
	 *	系统函数
	 */
	// 构造函数
	ABaseBullet();

	// 每一帧调用
	virtual void Tick(float DeltaTime) override;

protected:
	// 开始时调用
	virtual void BeginPlay() override;

	/*
	 *	自定义函数
	 */

	/*
	 *	核心函数！
	 *	碰撞函数的设置
	 *   函数名：OnBulletBeginOverlap
	 *	功能：当子弹与敌方坦克发生碰撞时触发
	 *   参数：
	 *   OverlappedComponent：被覆盖的组件
	 *   OtherActor：被覆盖的组件对应的Actor
	 *   OtherComp：被覆盖的组件对应的组件
	 *   OtherBodyIndex：被覆盖的组件对应的组件的BodyIndex
	 *   bFromSweep：是否从Sweep中覆盖
	 *   SweepResult：Sweep结果
	 */
	UFUNCTION()
	void OnBulletBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	/*
	 * 	组件
	 */

	/*
	 *	Sphere组件的设置
	 *	属性：可见 只读
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent *SphereCollision;

	/*
	 *	移动组件的设置
	 *   属性：可见 只读
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UProjectileMovementComponent *MovementComponent;

	/*
	 *	属性
	 */

	// 特效设置
	UPROPERTY(EditAnywhere, Category = "特效设置")
	UParticleSystem *ExplosionEffect;

	// 声音设置
	UPROPERTY(EditAnywhere, Category = "命中音效设置")
	USoundBase *ExplosionSound;

	// 子弹生命周期设置 初始化为20s
	UPROPERTY(EditDefaultsOnly, Category = "生命周期")
	float LifeSpan = 20.0f;

	// 子弹伤害
	// 初始化为20
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "子弹伤害")
	float HeatHealth = 20.0f;
};
