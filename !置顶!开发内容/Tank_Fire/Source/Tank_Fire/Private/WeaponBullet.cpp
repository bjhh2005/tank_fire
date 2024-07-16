// Fill out your copyright notice in the Description page of Project Settings.


/*
*	系统头文件
*/

//碰撞组件
#include"Components/SphereComponent.h"
//移动组件
#include"GameFramework/ProjectileMovementComponent.h"
//特效组件
#include"Particles/ParticleSystemComponent.h"
//音效组件
#include"Runtime/Engine/Classes/Kismet/GameplayStatics.h"

/*
*	自定义的头文件
*/

#include "WeaponBullet.h"
//玩家测试文件
#include"MyActor.h" 
//玩家头文件
#include"myWheeledVehiclePawn.h"


// Sets default values
AWeaponBullet::AWeaponBullet()
{
	//关闭移动	Tick函数
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	/*
	*	创建碰撞组件
	*/
	//创建碰撞组件
	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	//初始化碰撞半径
	SphereCollision->InitSphereRadius(5.0f);
	//设置碰撞组件为根组件
	SetRootComponent(SphereCollision);

	//设置移动组件
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");

	//设置特效组件
	Bu_EmitterComponent = CreateDefaultSubobject<UParticleSystemComponent>("Bu_EffectComponent");
	//设置特效组件为根组件
	Bu_EmitterComponent->SetupAttachment(RootComponent);

	// 设置初始状态为不激活
	Bu_EmitterComponent->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AWeaponBullet::BeginPlay()
{
	Super::BeginPlay();

	// 设置移动组件初始速度
	MovementComponent->Velocity = GetActorForwardVector() * MovementComponent->InitialSpeed;
	
	// 绑定碰撞事件
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AWeaponBullet::OnABeginOverlap);
}

// 碰撞事件
void AWeaponBullet::OnABeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//获取玩家
	AmyWheeledVehiclePawn* Player = Cast<AmyWheeledVehiclePawn>(OtherActor);

	if (Player) {
		//玩家被攻击测试
		//UE_LOG(LogTemp, Display, TEXT("destroy~~~~~~~~~~~"));
		
		//玩家被攻击
		Player->TakeDamage(HeatHealth);
		
		//命中位置生成音效
		UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation());

		// 在命中位置生成特效
		if (Bu_EmitterComponent && Bu_EmitterComponent->Template) {
			// 创建临时特效组件
			UParticleSystemComponent* TempEmitter = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Bu_EmitterComponent->Template, GetActorTransform());
			if (TempEmitter) {
				// 复制蓝图中的特效调整
				TempEmitter->SetTemplate(Bu_EmitterComponent->Template);
				// 激活特效
				TempEmitter->Activate(true);
			}
		}
		//击中后摧毁子弹
		Destroy();
	}
}

//关闭Tick函数
// Called every frame
void AWeaponBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

