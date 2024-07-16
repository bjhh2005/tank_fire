// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseWeapon.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
	// 关闭Tick函数
	//  Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// 创建武器组件的静态Mesh组件
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");

	// 设置根组件
	SetRootComponent(WeaponMesh);
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseWeapon::Fire()
{
	// 打印日志
	UE_LOG(LogTemp, Display, TEXT("running fire"));
}
