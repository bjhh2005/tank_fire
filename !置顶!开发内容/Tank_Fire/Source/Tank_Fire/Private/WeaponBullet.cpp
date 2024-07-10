// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBullet.h"
#include"Components/SphereComponent.h"
#include"GameFramework/ProjectileMovementComponent.h"
#include"MyActor.h" 
#include"myWheeledVehiclePawn.h"
#include"Particles/ParticleSystemComponent.h"
#include"Runtime/Engine/Classes/Kismet/GameplayStatics.h"

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

// Called when the game starts or when spawned
void AWeaponBullet::BeginPlay()
{
	Super::BeginPlay();

	MovementComponent->Velocity = GetActorForwardVector() * MovementComponent->InitialSpeed;
	
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AWeaponBullet::OnABeginOverlap);
}

void AWeaponBullet::OnABeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AmyWheeledVehiclePawn* bbb = Cast<AmyWheeledVehiclePawn>(OtherActor);
	
	if (bbb) {
		//UE_LOG(LogTemp, Display, TEXT("destroy~~~~~~~~~~~"));
		bbb->TakeDamage(HeatHealth);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Bu_Emitter, this->GetActorTransform());
		Destroy();
	}
}

// Called every frame
void AWeaponBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	

}

