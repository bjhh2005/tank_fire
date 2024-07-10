// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIPerceptionComponent.h"
#include"AIController.h"
#include"MyActor.h"
#include"ACharacter.h"
#include "myWheeledVehiclePawn.h"
#include"Perception/AISense_Sight.h"

AActor* UEnemyAIPerceptionComponent::GetPerceptionPlayer()
{
	TArray<AActor*>percptionActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), percptionActors);

	if (percptionActors.Num() == 0)return nullptr;

	AAIController* controller = Cast<AAIController>(GetOwner());
	if (!controller)return nullptr;

	APawn* pawn = controller->GetPawn();
	if (!pawn)return nullptr;

	float bastDistance = MAX_FLT;
	AActor* playerActor = nullptr;

	for (AActor* currentActor : percptionActors)
	{

		AWheeledVehiclePawn* player = Cast<AWheeledVehiclePawn>(currentActor);

		//AMyActor* player = Cast<AMyActor>(currentActor);
		//AMyActor* me = GetWorld()->SpawnActor<AMyActor>(MeClass);
		
		if (player)
		{
			
				UE_LOG(LogTemp, Display, TEXT("see you again"));
				float distance = (player->GetActorLocation() - pawn->GetActorLocation()).Size();
				if (distance < bastDistance)
					bastDistance = distance;

				playerActor = player;
				break;
			
		}
	}

	return playerActor;
}
