// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeapon.h"
#include "WeaponLaucher.generated.h"

//子弹类导入
class AWeaponBullet;

/**
 * 
 */
UCLASS()
class TANK_FIRE_API AWeaponLaucher : public ABaseWeapon
{
	GENERATED_BODY()
	
protected:
	//子弹类设置
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<AWeaponBullet>WeaponBulletClass;
	
public:
	//射击函数
	virtual void Fire() override;
};
