// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBullet.generated.h"

//导入碰撞组件类
class USphereComponent;
//导入运动组件类
class UProjectileMovementComponent;

UCLASS()
class TANK_FIRE_API AWeaponBullet : public AActor
{
	GENERATED_BODY()


public:	


	/*
	*	系统函数
	*/

	// Sets default values for this actor's properties
	AWeaponBullet();


	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	/*
	*	自定义函数
	*/

	//碰撞函数
	UFUNCTION()
	void OnABeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	/*
	*	导入组件
	*/

protected:

	//碰撞体积
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	USphereComponent* SphereCollision;

	//子弹运动组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UProjectileMovementComponent* MovementComponent;
	
	//特效组件
	UPROPERTY(EditAnywhere, Category = "Bu_EmitterComponent")
	UParticleSystemComponent* Bu_EmitterComponent;
	
	/*
	*	参数设置
	*/

	//声音设置
	UPROPERTY(EditAnywhere, Category = "命中音效设置")
	USoundBase* ExplosionSound;

public:	

	//子弹伤害
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthComponent")
	float HeatHealth = 20.0f;

};
