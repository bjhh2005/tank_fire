// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBullet.h"
#include"Components/SphereComponent.h"
#include"GameFramework/ProjectileMovementComponent.h"
#include"MyActor.h" 

// Sets default values
AWeaponBullet::AWeaponBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereCollision->InitSphereRadius(5.0f);
	SetRootComponent(SphereCollision);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");



}

void AWeaponBullet::BulletBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMyActor* myactor = Cast<AMyActor>(OtherActor);

	if (myactor)
	{
		myactor->TakeDamege(20);

		Destroy();
	}

}

// Called when the game starts or when spawned
void AWeaponBullet::BeginPlay()
{
	Super::BeginPlay();

	MovementComponent->Velocity = GetActorForwardVector() * MovementComponent->InitialSpeed;
	
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AWeaponBullet::BulletBeginOverlap);

}

// Called every frame
void AWeaponBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

