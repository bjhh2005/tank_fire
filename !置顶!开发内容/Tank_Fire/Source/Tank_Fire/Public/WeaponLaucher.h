// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeapon.h"
#include "WeaponLaucher.generated.h"

class AWeaponBullet;

/**
 * 
 */
UCLASS()
class TANK_FIRE_API AWeaponLaucher : public ABaseWeapon
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<AWeaponBullet>WeaponBulletClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter")
	UParticleSystem* FX_Emitter;	
	
	
public:
	virtual void Fire() override;
};
