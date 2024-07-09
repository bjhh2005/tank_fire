// Fill out your copyright notice in the Description page of Project Settings.


#include "TankHead1.h"
#include"BaseWeapon.h"
#include"ACharacter.h"

// Sets default values
ATankHead1::ATankHead1()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//TankHead1Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("TankHead1Mesh");

	//SetRootComponent(TankHead1Mesh);

}

void ATankHead1::Equipgun(ABaseWeapon* weapon, TSubclassOf<ABaseWeapon> WeaponClass)
{
	weapon = GetWorld()->SpawnActor<ABaseWeapon>(WeaponClass);

	if (weapon) {
		FAttachmentTransformRules attachrules(EAttachmentRule::SnapToTarget, false);
		weapon->AttachToComponent(GetMesh(), attachrules, FName("headsocket"));

		weapon->SetOwner(this);

	}
}

// Called when the game starts or when spawned
void ATankHead1::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATankHead1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATankHead1::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

