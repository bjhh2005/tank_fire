// Fill out your copyright notice in the Description page of Project Settings.


#include "TankHead1.h"
#include"BaseWeapon.h"
#include"ACharacter.h"

// Sets default values
ATankHead1::ATankHead1()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

//函数名称：Equipgun
//函数功能：将武器装备到角色身上
//参数描述：weapon：要装备的武器 WeaponClass：要装备的武器的类

void ATankHead1::Equipgun(ABaseWeapon* weapon, TSubclassOf<ABaseWeapon> WeaponClass)
{
	//创建武器
	weapon = GetWorld()->SpawnActor<ABaseWeapon>(WeaponClass);

	//判断是否有武器 
	if (weapon) {
		//将武器挂到角色的Mesh上
		FAttachmentTransformRules attachrules(EAttachmentRule::SnapToTarget, false);
		weapon->AttachToComponent(GetMesh(), attachrules, FName("headsocket"));

		//设置武器的拥有者
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

