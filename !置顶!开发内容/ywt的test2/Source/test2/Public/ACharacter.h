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

UCLASS()
class TEST2_API AACharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AACharacter();

	

protected:

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


	//开火
	UFUNCTION(BlueprintCallable)
	void Fire();

	
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
