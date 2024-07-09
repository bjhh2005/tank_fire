// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "HealthComponent.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//生命组件的设置
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}


// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	

}

void ABaseCharacter::DeadExplosionFunction()
{
	if (DeadExplosion)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeadExplosion, GetActorLocation());
	}
}

void ABaseCharacter::TakeDamage(float Amount)
{
	if (HealthComponent)
	{
		HealthComponent->TakeDamage(Amount);

		if (HealthComponent->GetHealth() <= HealthComponent->MaxHealth  / 2 &&  !ishurt)
		{
			ishurt = true;
			// 播放粒子特效并保存对粒子特效组件的引用
			ActiveExplosionEffect = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());
		}

		if (isDead && !Dead)
		{
			Dead = true;
			
			//如果引擎组件存在，则输出字符串
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("你杀死了一名敌人"));
			}


			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABaseCharacter::DeadExplosionFunction, 2.5f, false);

			// 设置定时器，5秒后销毁坦克
			GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, this, &ABaseCharacter::DelayedDestroy, 5.0f, false); // !!!!}
		}

	}
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// 辅助函数：延迟销毁坦克
void ABaseCharacter::DelayedDestroy()
{

	if (ActiveExplosionEffect)
	{
		ActiveExplosionEffect->Deactivate();
		ActiveExplosionEffect->DestroyComponent();
	}

	// 销毁坦克
	Destroy();
}