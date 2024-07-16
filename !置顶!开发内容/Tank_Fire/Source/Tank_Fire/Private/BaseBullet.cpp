// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseBullet.h"

// 系统头文件
// 碰撞头文件
#include "Components/SphereComponent.h"
// 移动组件头文件
#include "GameFramework/ProjectileMovementComponent.h"
// 音效头文件
#include "Kismet/GameplayStatics.h"

// 自定义头文件
// 测试头文件
#include "BaseCharacter.h"
// 敌人头文件
#include "ACharacter.h"

/*
 * 构造函数
 * 创建发射物
 * 创建碰撞组件
 * 设置碰撞体积
 * 设置移动组件
 * 设置生命周期
 */
ABaseBullet::ABaseBullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// 设置组件SphereCollision
	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");

	// 作为根组件存在
	SetRootComponent(SphereCollision);

	// 碰撞体积的初始化
	SphereCollision->InitSphereRadius(5.0f);

	// 发射物移动组件
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");

	// 设置生命周期为LifSpan
	InitialLifeSpan = LifeSpan;
}

/*
 *   BeginPlay
 *   创建发射物
 *   初始化发射速度
 *   绑定OnComponentBeginOverlap事件 将子弹类 碰撞组件与OnBulletBeginOverlap函数绑定
 */
void ABaseBullet::BeginPlay()
{
	Super::BeginPlay();

	// 移动速度 设置一个正前方的向量
	MovementComponent->Velocity = GetActorForwardVector() * MovementComponent->InitialSpeed;

	// 通过spheresphere组件的OnComponentBeginOverlap事件绑定一个函数
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ABaseBullet::OnBulletBeginOverlap);
}

/*
 *	OnBulletBeginOverlap
 *   获取OtherActor 设定为character 和 charecter2
 *	如果OtherActor是BaseCharacter类 则调用TakeDamage函数
 *	如果OtherActor是AACharacter类 则调用TakeDamage函数
 *	播放爆炸特效
 *	销毁子弹
 */
void ABaseBullet::OnBulletBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	// 如果是BaseCharacter类
	ABaseCharacter *character = Cast<ABaseCharacter>(OtherActor);

	// 如果时AACharacter类
	AACharacter *character2 = Cast<AACharacter>(OtherActor);

	// 判断角色类型
	if (character)
	{

		// 如果角色死亡 则不再播放音效
		if (!character->isDead)
		{
			// 爆炸的时候播放声音
			UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation());
		}
		// 调用角色的TakeDamage函数 造成伤害
		character->TakeDamage(HeatHealth);
		// 播放粒子特效
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());
		// 销毁子弹
		Destroy();
	}

	if (character2)
	{

		// 如果角色死亡 则不再播放音效
		if (!character2->isDead)
		{
			// 爆炸的时候播放声音
			UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation());
		}

		character2->TakeDamage(HeatHealth);

		// 播放粒子特效
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());

		// 获取玩家控制器
		APlayerController *PlayerController = GetWorld()->GetFirstPlayerController();

		Destroy();
	}
}

// Called every frame
void ABaseBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
