// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponLaucher.h"
#include"WeaponBullet.h"
#include"Particles/ParticleSystemComponent.h"
#include"Runtime/Engine/Classes/Kismet/GameplayStatics.h"


void AWeaponLaucher::Fire()
{
	FVector location = WeaponMesh->GetSocketLocation("bulletsocket");

	FRotator rotator = WeaponMesh->GetSocketRotation("bulletsocket");

	FTransform transform(rotator,location);

	AWeaponBullet* bullet=GetWorld()->SpawnActorDeferred<AWeaponBullet>(WeaponBulletClass,transform);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FX_Emitter, WeaponMesh->GetSocketTransform("bulletsocket"));

	if (bullet)
	{
		bullet->FinishSpawning(transform);
	}

	

}
