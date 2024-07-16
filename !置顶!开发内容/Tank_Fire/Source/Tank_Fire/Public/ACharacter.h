// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/*
 *	敌方坦克基类
 *	类名：AACharacter
 *   继承自：ACharacter
 *	创建日期：2024年7月6日
 *	简述：基本的敌方坦克类的设置
 */

/*
 *	作者：杨文韬
 * 	日期：2024年7月6日
 * 	版本：1.0
 * 	更新功能：实现敌方坦克基类的设置，实现开火，视角锁定，血量判定
 *			  死亡事件，移动参数的设置。
 */

/*
 *	作者：张瑞欣
 * 	日期：2024年7月8日
 * 	版本：1.1
 * 	更新功能：敌方坦克与玩家坦克的相互攻击，丰富了血量判定，实现半血释放特效，死亡延迟等等优化体验，
 *			  加入了一些特效与音效的接口，修复一些空指针引发闪退的BUG。
 */

/*
 *	作者：杨文韬
 * 	日期：2024年7月9日
 * 	版本：2.0
 * 	更新功能：实现了AI行为树的导入，实现了敌方坦克的自动开火，自动寻路避障等等功能。
 */

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ACharacter.generated.h"

/*
 *	系统类
 */

// 碰撞盒组件类
class USphereComponent;
// 摄像机组件类
class UCameraComponent;
// 摄像机臂组件类
class USpringArmComponent;
// 输入映射组件类
class UInputMappingContext;
// 输入映射组件类
class UInputAction;
// 输入映射组件类
struct FInputActionValue;

/*
 * 	自定义类
 */

// 武器基类
class ABaseWeapon;
// 坦克头部类
class ATankHead1;
// 导入生命组件
class UHealthComponent;

// 定义死亡事件
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

UCLASS()
class TANK_FIRE_API AACharacter : public ACharacter
{
	GENERATED_BODY()

	/*
	 *	系统函数部分
	 */
public:
	// 构造函数
	AACharacter();

	// 每帧调用函数
	virtual void Tick(float DeltaTime) override;

	// 事件绑定函数
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	// 游戏开始函数
	virtual void BeginPlay() override;

protected:
	/*
	 *	组件导入区域
	 *
	 *	临时特效组件
	 * 	弹簧臂组件
	 * 	摄像机组件
	 * 	碰撞盒组件
	 *	角色网格组件
	 *	生命组件
	 */

	/*
	 *	临时特效组件设置
	 *	属性：临时
	 */
	UPROPERTY()
	UParticleSystemComponent *ActiveExplosionEffect;

	/*
	 * 	弹簧臂组件导入
	 *	属性：可编辑 蓝图只读 category = "Camera"
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	USpringArmComponent *SpringArmComp;

	/*
	 *	摄像机组件导入
	 *	属性：可编辑 蓝图只读 category = "Camera"
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	UCameraComponent *CameraComp;

	/*
	 *	骨骼网络体组件导入
	 *	属性：可编辑 蓝图只读 category = "TankHeadComponent"
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TankHeadComponent")
	USkeletalMeshComponent *TankHeadMesh;

	/*
	 * 角色网格组件导入
	 * 属性：可编辑 蓝图只读 category = "CharacterMesh"
	 */
	USkeletalMeshComponent *CharacterMesh;
	/*
	 * 	生命组件导入
	 *	属性：可编译 蓝图只读 category = "HealthComponent"
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HealthComponent")
	UHealthComponent *HealthComponent;

	/*
	 *	属性设置区域
	 */
public:
	/*
	 *	AI行为树组件的导入
	 * 	属性：可编译 蓝图只读 category = "AI"
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	class UBehaviorTree *BehaviorTreeAsset;

protected:
	/*
	 *	爆炸特效设置
	 *	属性：可见 category = "特效设置"
	 */
	UPROPERTY(EditAnywhere, Category = "特效设置")
	UParticleSystem *ExplosionEffect;

	/*
	 *	死亡特效设置
	 *	属性：可见 category = "特效设置"
	 */
	UPROPERTY(EditAnywhere, Category = "特效设置")
	UParticleSystem *DeadExplosion;

	/*
	 *	输入映射组部分导入
	 *	属性：可编译 蓝图只读 category = "MyInput"
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MyInput")
	UInputMappingContext *DefaultMappingContext;
	// 移动
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MyInput")
	UInputAction *MoveAction;
	// 摄像头
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MyInput")
	UInputAction *LookAction;
	// 开火
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MyInput")
	UInputAction *FireAction;
	// 跳跃
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MyInput")
	UInputAction *JumpAction;

	/*
	 *	装备部分
	 * 	属性：可编译 蓝图只读 category = "WeaponClass"
	 */
	// 实现武器装备
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponClass")
	TSubclassOf<ABaseWeapon> WeaponClass;
	// 实现坦克头部拼接
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TankHead1Class")
	TSubclassOf<ATankHead1> TankHeadClass;

	/*
	 * 参数设计区域
	 */
public:
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
	FOnDeath OnDeath;

	// 受伤事件
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnDeath OnHit;

	// 武器装备
	ABaseWeapon *weapon;

	// 坦克头部
	ATankHead1 *tankhead1;

	/*
	 *	函数设计区域
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

	/*
	 *	坦克攻击函数
	 *	函数名：Fire
	 *	功能：实现坦克开火
	 *	参数：无
	 *	返回：无
	 */
	UFUNCTION(BlueprintCallable)
	void Fire();

	/*
	 *	函数名：StopMove
	 *	功能：实现坦克死亡以后，断开坦克行为树
	 *	参数：无
	 *	返回：无
	 */
	void StopMove();

protected:
	/*
	 *	死亡爆炸函数
	 *	函数名：DeadExplosionFunction
	 *	功能：辅助函数，实现延迟爆炸，从而实现坦克死亡后一段时间后再爆炸，起到残骸的效果
	 *	参数：无
	 *	返回：无
	 */
	void DeadExplosionFunction();

	/*
	 *	装备武器
	 *	函数名：EquipWeapon
	 * 	功能：实现坦克装备武器，实现坦克的枪管的碰撞体积
	 *	参数：无
	 * 	返回：无
	 */
	void EquipWeapon();

	/*
	 *	坦克移动函数
	 */
	// 移动函数
	void Move(const FInputActionValue &Value);
	// 视角函数
	void Look(const FInputActionValue &Value);

	/*
	 *	实现延迟死亡
	 * 	函数名：DelayedDestroy
	 * 	功能：辅助函数，实现坦克死亡后，延迟一段时间再销毁坦克
	 * 	参数：无
	 * 	返回：无
	 */
	void DelayedDestroy();
};
