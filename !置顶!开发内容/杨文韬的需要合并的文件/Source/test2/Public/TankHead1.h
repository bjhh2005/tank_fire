// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TankHead1.generated.h"

class ABaseWeapon;

UCLASS()
class TEST2_API ATankHead1 : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATankHead1();
	void Equipgun(ABaseWeapon* weapon, TSubclassOf<ABaseWeapon> WeaponClass);

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TankHead1Component")
	//USkeletalMeshComponent* TankHead1Mesh;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	/*ABaseWeapon* weapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponClass")
	TSubclassOf<ABaseWeapon> WeaponClass;*/



public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

