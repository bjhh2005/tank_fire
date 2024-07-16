// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/*
 *	实现枪支功能的类
 *	ABaseWeapon
 * 	继承自：AActor
 * 	创建日期：2024年7月日
 *	简述:实现了枪支的装备与开火功能。
 */

/*
 *	作者：杨文韬
 * 	日期：2024年7月6日
 * 	版本：1.0
 * 	更新功能：设置枪支类，实现开火功能。
 *	继承基类：AActor
 */

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

UCLASS()
class TANK_FIRE_API ABaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	/*
	 *	系统函数
	 */

	// 构造函数
	ABaseWeapon();

	// 游戏开始或生成时调用
	virtual void BeginPlay() override;

protected:
	/*
	 *	组件部分
	 */

	/*
	 *	作用：作用枪支静态网格体组件的导入
	 *	属性：引擎内可见 只读属性 category = "MyComponent"
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyComponent")
	USkeletalMeshComponent *WeaponMesh;

public:
	/*
	 *	自定义函数部分
	 */

	/*
	 *	作用：实现射击功能
	 * 	参数：无
	 */
	virtual void Fire();
};
