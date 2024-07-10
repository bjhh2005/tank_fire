// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ACharacter.generated.h"


//---------------------------------------------------------------------------

//导入生命组件
class UHealthComponent;

//---------------------------------------------------------------------------

//其他组件
class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class ABaseWeapon;
class ATankHead1;


UCLASS()
class TANK_FIRE_API AACharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AACharacter();


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	class UBehaviorTree* BehaviorTreeAsset;
protected:
	//---------------------------------------------------------------------------

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

	//死亡爆炸
	void DeadExplosionFunction();

	//---------------------------------------------------------------------------




	//����

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponClass")
	TSubclassOf<ABaseWeapon> WeaponClass;

	ABaseWeapon* weapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TankHead1Class")
	TSubclassOf<ATankHead1> TankHeadClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TankHeadComponent")
	USkeletalMeshComponent* TankHeadMesh;

	ATankHead1* tankhead1;

	void EquipWeapon();


	//����
	UFUNCTION(BlueprintCallable)
	void Fire();


	//�����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	UCameraComponent* CameraComp;

	//�������ڳ������ģ��ĳ�Ա
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

	//---------------------------------------------------------------------------
	//by张
	//伤害函数
	UFUNCTION(BlueprintCallable)
	void TakeDamage(float Amount);

	//辅助变量
	bool ishurt = false;
	bool Dead = false;
	bool isDead = false;

	//死亡断开行为树
	UFUNCTION(BlueprintCallable)
	virtual void StopMove();
	//---------------------------------------------------------------------------

};
