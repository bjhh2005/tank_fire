// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ACharacter.generated.h"




class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class ABaseWeapon;
class ATankHead1;
class UHealthComponent;


UCLASS()
class TANK_FIRE_API AACharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AACharacter();

	//开火
	UFUNCTION(BlueprintCallable)
	void Fire();

	//by寮?
//浼ゅ鍑芥暟
	UFUNCTION(BlueprintCallable)
	void TakeDamage(float Amount);

	//杈呭姪鍙橀噺
	bool ishurt = false;
	bool Dead = false;
	bool isDead = false;




	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	class UBehaviorTree* BehaviorTreeAsset;
protected:


	//生命组件
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HealthComponent")
	UHealthComponent* HealthComponent;


	//鐗规晥璁剧疆
	UPROPERTY(EditAnywhere, Category = "Emitter")
	UParticleSystem* ExplosionEffect;

	// 鐗规晥缁勪欢鐨勫紩鐢?
	UPROPERTY()
	UParticleSystemComponent* ActiveExplosionEffect;

	//杈呭姪鍑芥暟 甯姪閿�姣?
	void DelayedDestroy();

	//鐗规晥璁剧疆
	UPROPERTY(EditAnywhere, Category = "Emitter")
	UParticleSystem* DeadExplosion;

	//璁剧疆鐢熷懡
	float health;

	// 璁℃椂鍣ㄥ彞鏌?
	FTimerHandle TimerHandle;

	// 瀹氭椂鍣ㄥ彞鏌?
	FTimerHandle DestroyTimerHandle;

	//姝讳骸鐖嗙偢
	void DeadExplosionFunction();


	//行为树
	



	//武器

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponClass")
	TSubclassOf<ABaseWeapon> WeaponClass;

	ABaseWeapon* weapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TankHead1Class")
	TSubclassOf<ATankHead1> TankHeadClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TankHeadComponent")
	USkeletalMeshComponent* TankHeadMesh;

	ATankHead1* tankhead1;

	void EquipWeapon();


	

	
	//摄像机
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	UCameraComponent* CameraComp;

	//定义用于持有相关模块的成员
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MyInput")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MyInput")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MyInput")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MyInput")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MyInput")
	UInputAction* FireAction;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	USkeletalMeshComponent* CharacterMesh;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
