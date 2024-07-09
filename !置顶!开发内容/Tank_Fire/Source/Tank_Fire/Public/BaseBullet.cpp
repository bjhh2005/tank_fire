// Fill out your copyright notice in the Description page of Project Settings.

#include "ACharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "BaseCharacter.h"
#include "BaseBullet.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABaseBullet::ABaseBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//设置组件SphereCollision
	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");

	//作为根组件存在
	SetRootComponent(SphereCollision);

	//碰撞体积的初始化
	SphereCollision->InitSphereRadius(5.0f);

	//发射物移动组件
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");

	//设置生命周期为LifSpan
	InitialLifeSpan = LifeSpan;
}

// Called when the game starts or when spawned
void ABaseBullet::BeginPlay()
{
	Super::BeginPlay();

	//移动速度 设置一个正前方的向量
	MovementComponent->Velocity = GetActorForwardVector() * MovementComponent->InitialSpeed;

	//通过spheresphere组件的OnComponentBeginOverlap事件绑定一个函数
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ABaseBullet::OnBulletBeginOverlap);

}

void ABaseBullet::OnBulletBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//如果是BaseCharacter类 
	ABaseCharacter* character = Cast<ABaseCharacter>(OtherActor);

	//如果时AACharacter类
	AACharacter* character2 = Cast<AACharacter>(OtherActor);

	

	if (character) {
		character->TakeDamage(HeatHealth);
		
		//播放粒子特效
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());

		//爆炸的时候播放声音
		UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation());

		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			APawn* PlayerPawn = PlayerController->GetPawn();
			if (PlayerPawn)
			{
				FVector PlayerLocation = PlayerPawn->GetActorLocation();
				if (ExplosionSound) //!!!!
				{
					UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, PlayerLocation); //!!!!
				}
			}
		}
		Destroy();
	}

	if (character2) {
		character2->TakeDamage(HeatHealth);

		//播放粒子特效
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());

		//爆炸的时候播放声音
		UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation());

		//获取玩家控制器
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		
		//如果获取玩家
		if (PlayerController)
		{
			//获取玩家
			APawn* PlayerPawn = PlayerController->GetPawn();
			if (PlayerPawn)
			{
				FVector PlayerLocation = PlayerPawn->GetActorLocation();
				if (ExplosionSound) //!!!!
				{
					//播放爆炸音效
					UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, PlayerLocation); //!!!!
				}
			}
		}
		Destroy();
	}

}

// Called every frame
void ABaseBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

