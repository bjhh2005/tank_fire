// Fill out your copyright notice in the Description page of Project Settings.


#include "ACharacter.h"

//导入生命组件头文件
#include "HealthComponent.h"
//导入粒子系统头文件
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
//导入碰撞的头文件
#include"Components/SphereComponent.h"
//AI组件
#include "AIController.h"
//包含清除行为树的组件
#include "BrainComponent.h"


//其他
#include"GameFramework/SpringArmComponent.h"
#include"Camera/CameraComponent.h"
#include"EnhancedInputComponent.h"
#include"EnhancedInputSubsystems.h"
#include"InputActionValue.h"
#include"GameFramework/PlayerController.h"
#include"BaseWeapon.h"
#include"TankHead1.h"
#include"BehaviorTree/BehaviorTree.h"

AACharacter::AACharacter()
{
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 900;
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);
	CameraComp->bUsePawnControlRotation = false;

	// by张
	//生命组件的设置
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

}

// by 张 辅助函数 延迟摧毁坦克
void AACharacter::DelayedDestroy()
{
	if (ActiveExplosionEffect)
	{
		ActiveExplosionEffect->Deactivate();
		ActiveExplosionEffect->DestroyComponent();
	}
	// 销毁坦克
	Destroy();
	tankhead1->Destroy();
	weapon->Destroy();
}

//by 张
//死亡爆炸特效
void AACharacter::DeadExplosionFunction()
{
	if (DeadExplosion)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeadExplosion, GetActorLocation());
	}
}

void AACharacter::EquipWeapon()
{

	//tankhead1 = GetWorld()->SpawnActor<ATankHead1>(TankHeadClass);
	//
	//if (tankhead1) {
	//	//UE_LOG(LogTemp, Display, TEXT("XXXXXXX"));
	//	FAttachmentTransformRules attachrules(EAttachmentRule::SnapToTarget, false);
	//	tankhead1->AttachToComponent(GetMesh(), attachrules, FName("bodysocket"));

	//	tankhead1->SetOwner(this);

	//}

	weapon = GetWorld()->SpawnActor<ABaseWeapon>(WeaponClass);

	if (weapon) {
		FAttachmentTransformRules attachrules(EAttachmentRule::SnapToTarget, false);
		weapon->AttachToComponent(GetMesh(), attachrules, FName("headsocket"));

		weapon->SetOwner(this);

	}

	//weapon = GetWorld()->SpawnActor<ABaseWeapon>(WeaponClass);

	//if (weapon) {
	//	FAttachmentTransformRules attachrules(EAttachmentRule::SnapToTarget, false);
	//	weapon->AttachToComponent(GetMesh(), attachrules, FName("headsocket"));

	//	weapon->SetOwner(this);

	//}
}

//����

void AACharacter::Fire()
{
	if (weapon)
	{
		weapon->Fire();
	}
}

void AACharacter::Move(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp, Display, TEXT("move  run"));

	FVector2D moveDir = Value.Get<FVector2D>();

	if (Controller!=nullptr)
	{
		FRotator rotation = GetActorRotation();
		FRotator yawrotation(0, rotation.Yaw, 0);
		//�õ���ɫ��ת�����ǰ��
		FVector forward = FRotationMatrix(yawrotation).GetUnitAxis(EAxis::X);
		//�õ���ɫ��ת������ҷ�
		FVector right = FRotationMatrix(yawrotation).GetUnitAxis(EAxis::Y);
		//����ƶ�����
		AddMovementInput(forward, moveDir.Y);
		AddMovementInput(right, moveDir.X);

	}
}

void AACharacter::Look(const FInputActionValue& Value)
{
	FVector2D lookDir = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerPitchInput(lookDir.Y);
		AddControllerYawInput(lookDir.X);

	}
}

// Called when the game starts or when spawned
void AACharacter::BeginPlay()
{
	Super::BeginPlay();

	EquipWeapon();

	

	APlayerController* playerController = Cast<APlayerController>(Controller);

	if (playerController)
	{
		UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());
		if (subsystem)
		{
			subsystem->AddMappingContext(DefaultMappingContext, 0);
		}

	}
	
}

// Called every frame
void AACharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AACharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* myInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (myInputComponent)
	{
		myInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AACharacter::Move);

		myInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AACharacter::Jump);
		myInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AACharacter::StopJumping);

		myInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AACharacter::Look);
		myInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &AACharacter::Fire);
	}

}

void AACharacter::TakeDamage(float Amount)
{
	if (HealthComponent)
	{
		HealthComponent->TakeDamage(Amount);
		if (HealthComponent->GetHealth() <= HealthComponent->MaxHealth / 2 && !ishurt)
		{
			ishurt = true;
			// 播放粒子特效并保存对粒子特效组件的引用
			//调用attacheed让粒子特效跟随玩家移动
			ActiveExplosionEffect = UGameplayStatics::SpawnEmitterAttached(ExplosionEffect, GetRootComponent());
		}

		if (isDead && !Dead)
		{
			Dead = true;

			//死亡以后断开行为树
			StopMove();

			//如果引擎组件存在，则输出字符串
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("你杀死了一名敌人"));
			}


			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AACharacter::DeadExplosionFunction, 0.5f, false);
			
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AACharacter::DeadExplosionFunction, 2.0f, false);
			
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AACharacter::DeadExplosionFunction, 4.5f, false);
			
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AACharacter::DeadExplosionFunction, 6.0f, false);


			// 设置定时器，30秒后销毁坦克
			GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, this, &AACharacter::DelayedDestroy,30.0f, false); // !!!!}
		}
	}
}

void AACharacter::StopMove()
{
	AAIController* controller = Cast<AAIController>(GetController());
	
	if (controller){
		//清除行为树
		controller->BrainComponent->Cleanup();
	}

}