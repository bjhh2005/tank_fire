// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include"Components/SphereComponent.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 设置胶囊体组件
	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	// 设置胶囊体半径为5
	SphereCollision->InitSphereRadius(5.0f);
	// 设置胶囊体为根组件
	SetRootComponent(SphereCollision);
}


// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}