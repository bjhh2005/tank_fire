// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponLaucher.h"
#include"WeaponBullet.h"


//开火函数
void AWeaponLaucher::Fire()
{
	//获取枪口位置
	FVector location = WeaponMesh->GetSocketLocation("bulletsocket");

	//获取枪口旋转
	FRotator rotator = WeaponMesh->GetSocketRotation("bulletsocket");

	//根据位置与旋转 创建一个变换
	FTransform transform(rotator,location);

	//创建子弹
	AWeaponBullet* bullet=GetWorld()->SpawnActorDeferred<AWeaponBullet>(WeaponBulletClass,transform);

	if (bullet)
	{
		//启动子弹 调用变换
		bullet->FinishSpawning(transform);
	}
}
