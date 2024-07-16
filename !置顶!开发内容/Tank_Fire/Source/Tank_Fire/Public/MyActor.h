// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

//设置碰撞体
class USphereComponent;

UCLASS()
class TANK_FIRE_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//初始化碰撞体
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* SphereCollision;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
