// Fill out your copyright notice in the Description page of Project Settings.

#include "ACharacter.h"

// 系统头文件

// 导入粒子系统头文件
#include "Particles/ParticleSystem.h"
// 导入游戏系统头文件
#include "Kismet/GameplayStatics.h"
// 导入静态网格体头文件
#include "Components/StaticMeshComponent.h"
// 导入粒子系统组件头文件
#include "Particles/ParticleSystemComponent.h"
// 导入碰撞的头文件
#include "Components/SphereComponent.h"
// AI组件
#include "AIController.h"
// 包含清除行为树的组件
#include "BrainComponent.h"
// 引入弹簧臂头文件
#include "GameFramework/SpringArmComponent.h"
// 引入摄像机头
#include "Camera/CameraComponent.h"
// 引入增强输入组件头文件
#include "EnhancedInputComponent.h"
// 引入增强输入系统头文件
#include "EnhancedInputSubsystems.h"
// 引入输入动作值头文件
#include "InputActionValue.h"
// 引入玩家控制器头文件
#include "GameFramework/PlayerController.h"
// 导入行为树头文件
#include "BehaviorTree/BehaviorTree.h"

// 自定义头文件

// 导入生命组件头文件
#include "HealthComponent.h"
// 引入枪支
#include "BaseWeapon.h"
// 引入坦克头部
#include "TankHead1.h"

/*
 *	构造函数
 *	功能：实习了弹簧臂组件 摄像机组件的初始化
 *		  生命组件的导入
 */
AACharacter::AACharacter()
{
	// 弹簧臂组件创建
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	// 弹簧臂组件设置在根组件下
	SpringArmComp->SetupAttachment(RootComponent);
	// 长度初始化
	SpringArmComp->TargetArmLength = 900;
	// 设置弹簧臂使用玩家的旋转控制开启
	SpringArmComp->bUsePawnControlRotation = true;

	// 创建摄像机组件
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	// 摄像机组件设置在弹簧臂组件下
	CameraComp->SetupAttachment(SpringArmComp);
	// 设置摄像头使用玩家的旋转控制关闭
	CameraComp->bUsePawnControlRotation = false;

	// 导入生命组件
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

/*
 *	延迟死亡函数
 *	功能：延迟销毁坦克 调用死亡爆炸特效
 *	注意：需要在销毁坦克主体的同时消除坦克头部和武器
 *		  需要加上对空指针的判断以防程序调用空指针引起程序崩溃
 */
void AACharacter::DelayedDestroy()
{
	// 检查特效组件指针是否为空
	if (ActiveExplosionEffect)
	{
		// 关闭特效
		ActiveExplosionEffect->Deactivate();
		// 销毁临时特效组件
		ActiveExplosionEffect->DestroyComponent();
	}

	// 销毁坦克
	Destroy();

	// 销毁坦克头和武器
	if (tankhead1)
	{
		tankhead1->Destroy();
	}
	// 检查 weapon 是否为空
	if (weapon)
	{
		weapon->Destroy();
	}
}

// 死亡爆炸函数
// 功能：创建死亡爆炸特效
void AACharacter::DeadExplosionFunction()
{
	// 判断死亡爆炸特效指针是否为空
	if (DeadExplosion)
	{
		// 获取当前世界位置 在当前世界位置创建特效
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeadExplosion, GetActorLocation());
	}
}

/*
 *	装备武器函数
 *	功能：创建武器，将武器挂载到坦克头部
 *	注意：需要加上对空指针的判断以防程序调用空指针引起程序崩溃
 *		  需要注意枪管的碰撞设计
 */
void AACharacter::EquipWeapon()
{
	// 根据当前的世界位置 获取武器的接口
	weapon = GetWorld()->SpawnActor<ABaseWeapon>(WeaponClass);

	// 检查武器是否为空
	if (weapon)
	{
		// 挂载到坦克头部
		FAttachmentTransformRules attachrules(EAttachmentRule::SnapToTarget, false);
		weapon->AttachToComponent(GetMesh(), attachrules, FName("headsocket"));
		// 设置武器拥有者为当前坦克
		weapon->SetOwner(this);
	}
}

// 射击函数
void AACharacter::Fire()
{
	if (weapon)
	{
		weapon->Fire();
	}
}

// 角色移动函数
void AACharacter::Move(const FInputActionValue &Value)
{
	// 测试使用 函数调用是否有效
	// UE_LOG(LogTemp, Display, TEXT("move  run"));

	// 获取向量 移动方向
	FVector2D moveDir = Value.Get<FVector2D>();

	// 检查控制器是否为空
	if (Controller != nullptr)
	{
		// 获取角色的旋转
		FRotator rotation = GetActorRotation();
		// 根据角色的旋转获取朝向向量
		FRotator yawrotation(0, rotation.Yaw, 0);
		// 获取朝向向量的单位向量
		FVector forward = FRotationMatrix(yawrotation).GetUnitAxis(EAxis::X);
		// 获取旋转的单位向量
		FVector right = FRotationMatrix(yawrotation).GetUnitAxis(EAxis::Y);
		// 设置角色的移动方向的输入
		AddMovementInput(forward, moveDir.Y);
		// 设置角色的旋转方向的输入
		AddMovementInput(right, moveDir.X);
	}
}

// 角色视角旋转函数
void AACharacter::Look(const FInputActionValue &Value)
{
	// 获取向量 移动方向
	FVector2D lookDir = Value.Get<FVector2D>();

	// 检查控制器是否为空
	if (Controller != nullptr)
	{
		// 设置角色的移动与旋转方向的输入
		AddControllerPitchInput(lookDir.Y);
		AddControllerYawInput(lookDir.X);
	}
}

// 开始时调用函数
void AACharacter::BeginPlay()
{
	Super::BeginPlay();

	// 角色创建时生成武器
	EquipWeapon();

	// 获取玩家控制器
	APlayerController *playerController = Cast<APlayerController>(Controller);

	// 判断控制器是否为空
	if (playerController)
	{
		// 获取当前世界的玩家增强输入组件
		UEnhancedInputLocalPlayerSubsystem *subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());
		if (subsystem)
		{
			// 使得坦克朝向始终指向玩家位置
			subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

// 每帧调用
void AACharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// 设置玩家输入组件
void AACharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	// 调用父类设置玩家输入组件
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 获取玩家输入组件
	UEnhancedInputComponent *myInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	// 判断玩家输入组件是否为空
	if (myInputComponent)
	{
		// 绑定玩家移动输入组件
		myInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AACharacter::Move);

		// 绑定玩家跳跃输入组件
		myInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AACharacter::Jump);
		myInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AACharacter::StopJumping);
		
		/// 绑定玩家视角旋转输入组件
		myInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AACharacter::Look);
		myInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &AACharacter::Fire);
	}
}

/*
 *	核心功能
 *	功能：当坦克被攻击时，调用TakeDamage函数，当坦克血量小于等于最大血量的一半时，播放粒子特效，当坦克血量小于等于0时，销毁坦克
 *	      同时设置击中击事件广播，并且设置死亡事件广播 便于实现游戏的胜负逻辑判断 实现游戏得分逻辑的实现
 *		  设置对应的赋值变量避免函数重复调用引起BUG
 *	注意：需要加上对空指针的判断以防程序调用空指针引起程序崩溃
 */
void AACharacter::TakeDamage(float Amount)
{
	// 判断是否存在生命组件
	if (HealthComponent)
	{
		// 通过调生命组件的TakeDamage函数，传入伤害值
		HealthComponent->TakeDamage(Amount);

		// 判断血量是否小于等于0
		if (HealthComponent != 0)
		{
			// 触发击中击事件
			OnHit.Broadcast();
		}

		// 判断血量是否小于等于最大血量的一半
		if (HealthComponent->GetHealth() <= HealthComponent->MaxHealth / 2 && !ishurt)
		{
			// 设置受伤事件 避免重复调用
			ishurt = true;
			// 播放粒子特效并保存对粒子特效组件的引用
			// 调用attacheed让粒子特效跟随玩家移动
			ActiveExplosionEffect = UGameplayStatics::SpawnEmitterAttached(ExplosionEffect, GetRootComponent());
		}

		// 判断血量是否小于等于0
		// isDead在健康组件中实现
		// Dead避免重复触发
		if (isDead && !Dead)
		{
			// 设置参数 避免重复调用
			Dead = true;

			// 触发死亡事件
			OnDeath.Broadcast();

			// 死亡以后断开行为树
			StopMove();

			// 如果引擎组件存在，则输出字符串
			// if (GEngine)
			//{
			//	//测试用
			//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("你杀死了一名敌人"));
			// }

			// 设置定时器，6秒后触发爆炸粒子特效
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AACharacter::DeadExplosionFunction, 6.0f, false);

			// 设置定时器，10秒后销毁坦克
			GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, this, &AACharacter::DelayedDestroy, 10.0f, false); // !!!!}
		}
	}
}

// 死亡时调用 断开行为树
void AACharacter::StopMove()
{
	// 获取AI控制器
	AAIController *controller = Cast<AAIController>(GetController());

	if (controller)
	{
		// 清除行为树
		controller->BrainComponent->Cleanup();
	}
}