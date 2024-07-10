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

	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereCollision->InitSphereRadius(500.0f);
	SetRootComponent(SphereCollision);

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

			////�������������ڣ�������ַ���
			//if (GEngine)
			//{
			//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("��ɱ����һ������"));
			//}


			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AmyWheeledVehiclePawn::DeadExplosionFunction, 2.5f, false);

			// ���ö�ʱ����5�������̹��
			GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, this, &AmyWheeledVehiclePawn::DelayedDestroy, 5.0f, false); // !!!!}
		}
	}
}
