// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UHealthComponent;

UCLASS()
class TANK_FIRE_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//生命组件的导入
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HealthComponent")
	UHealthComponent* HealthComponent;

	//特效设置
	UPROPERTY(EditAnywhere, Category = "特效设置")
	UParticleSystem* ExplosionEffect;

	// 特效组件的引用
	UPROPERTY()
	UParticleSystemComponent* ActiveExplosionEffect;

	//辅助函数 帮助销毁
	void DelayedDestroy();

	//特效设置
	UPROPERTY(EditAnywhere, Category = "特效设置")
	UParticleSystem* DeadExplosion;

	//设置生命
	float health;

	// 计时器句柄
	FTimerHandle TimerHandle;
	
	// 定时器句柄
	FTimerHandle DestroyTimerHandle;

	void DeadExplosionFunction();

public:	
	
	UFUNCTION(BlueprintCallable)
	void TakeDamage(float Amount);

	bool ishurt = false;
	bool Dead = false;
	bool isDead = false;


};
