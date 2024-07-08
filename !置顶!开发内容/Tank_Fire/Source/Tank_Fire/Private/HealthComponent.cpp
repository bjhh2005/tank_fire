// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	health = MaxHealth;
	
}

void UHealthComponent::TakeDamage(float Amount)
{
	if (health  >  0){
		health -= HeatHealth;
		UE_LOG(LogTemp, Display, TEXT("Character Damage Amout = %f, Health = %f"), Amount, health);
		if (health <= 0)
		{
			//获取组件的拥有者
			ABaseCharacter* character = Cast<ABaseCharacter>(GetOwner());
			//血量设置为0
			health = 0;
			//播报
			UE_LOG(LogTemp, Display, TEXT("Character Death"));
			//角色死亡
			character->isDead = true;
		}
	}

}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

