// Fill out your copyright notice in the Description page of Project Settings.


#include "myWheeledVehiclePawn.h"

//�����������ͷ�ļ�
#include "HealthComponent.h"
//��������ϵͳͷ�ļ�
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include"Components/SphereComponent.h"

AmyWheeledVehiclePawn::AmyWheeledVehiclePawn()
{

	

	//�������������
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

}


// by �� �������� �ӳٴݻ�̹��
void AmyWheeledVehiclePawn::DelayedDestroy()
{
	if (ActiveExplosionEffect)
	{
		ActiveExplosionEffect->Deactivate();
		ActiveExplosionEffect->DestroyComponent();
	}
	// ����̹��
	Destroy();
}

//by ��
//������ը��Ч
void AmyWheeledVehiclePawn::DeadExplosionFunction()
{
	if (DeadExplosion)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeadExplosion, GetActorLocation());
	}
}


void AmyWheeledVehiclePawn::TakeDamage(float Amount)
{
	if (HealthComponent)
	{
		HealthComponent->TakeDamage(Amount);
		if (HealthComponent->GetHealth() <= HealthComponent->MaxHealth / 2 && !ishurt)
		{
			ishurt = true;
			// ����������Ч�������������Ч���������
			ActiveExplosionEffect = UGameplayStatics::SpawnEmitterAttached(ExplosionEffect, GetRootComponent());
		}

		if (isDead && !Dead)
		{
			Dead = true;

			//�������������ڣ�������ַ���
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("菜 就多练 玩不起 就别玩"));
			}

			//播放特效
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AmyWheeledVehiclePawn::DeadExplosionFunction, 0.0f, false);
			//销毁角色
			DelayedDestroy();
		}
	}
}
