// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "myWheeledVehiclePawn.generated.h"

class UHealthComponent;
class USphereComponent;

/**
 * 
 */
UCLASS()
class TANK_FIRE_API AmyWheeledVehiclePawn : public AWheeledVehiclePawn
{
	GENERATED_BODY()
public:
	AmyWheeledVehiclePawn();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* SphereCollision;

	//by�?
//伤害函数
	UFUNCTION(BlueprintCallable)
	void TakeDamage(float Amount);

	//辅助变量
	bool ishurt = false;
	bool Dead = false;
	bool isDead = false;


protected:

	//�������
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HealthComponent")
	UHealthComponent* HealthComponent;


	//特效设置
	UPROPERTY(EditAnywhere, Category = "Emitter")
	UParticleSystem* ExplosionEffect;

	// 特效组件的引�?
	UPROPERTY()
	UParticleSystemComponent* ActiveExplosionEffect;

	//辅助函数 帮助销�?
	void DelayedDestroy();

	//特效设置
	UPROPERTY(EditAnywhere, Category = "Emitter")
	UParticleSystem* DeadExplosion;

	//设置生命
	float health;

	// 计时器句�?
	FTimerHandle TimerHandle;

	// 定时器句�?
	FTimerHandle DestroyTimerHandle;

	//死亡爆炸
	void DeadExplosionFunction();

	
};
