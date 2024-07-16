// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


 /*
  *		作者：杨文韬
  * 	日期：2024年7月9日
  * 	版本：1.0
  * 	更新功能：实现坦克头部的拼装
  */

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TankHead1.generated.h"

//武器类的调用类
class ABaseWeapon;

UCLASS()
class TANK_FIRE_API ATankHead1 : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATankHead1();

	// 装备武器
	//参数：weapon：要装备的武器 WeaponClass：要装备武器的类
	void Equipgun(ABaseWeapon* weapon, TSubclassOf<ABaseWeapon> WeaponClass);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

