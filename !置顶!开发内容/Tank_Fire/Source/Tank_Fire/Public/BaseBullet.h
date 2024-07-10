// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseBullet.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class TANK_FIRE_API ABaseBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseBullet();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Sphere设置
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* SphereCollision;

	//特效设置
	UPROPERTY(EditAnywhere, Category = "特效设置")
	UParticleSystem* ExplosionEffect;

	//移动组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UProjectileMovementComponent* MovementComponent;

	//碰撞设置
	UFUNCTION()
	void OnBulletBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//声音设置
	UPROPERTY(EditAnywhere, Category = "命中音效设置")
	USoundBase* ExplosionSound;

	//子弹生命周期设置
	UPROPERTY(EditDefaultsOnly, Category = "生命周期")
	float LifeSpan = 20.0f;	

	//子弹伤害
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "子弹伤害")
	float HeatHealth = 20.0f;



public:	
	

};
