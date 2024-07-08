// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponLaucher.h"
#include"WeaponBullet.h"


void AWeaponLaucher::Fire()
{
	FVector location = WeaponMesh->GetSocketLocation("bulletsocket");

	FRotator rotator = WeaponMesh->GetSocketRotation("bulletsocket");

	FTransform transform(rotator,location);

	AWeaponBullet* bullet=GetWorld()->SpawnActorDeferred<AWeaponBullet>(WeaponBulletClass,transform);

	if (bullet)
	{
		bullet->FinishSpawning(transform);
	}
}
