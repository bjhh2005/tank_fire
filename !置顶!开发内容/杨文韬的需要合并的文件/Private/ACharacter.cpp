// Fill out your copyright notice in the Description page of Project Settings.


#include "ACharacter.h"
#include"GameFramework/SpringArmComponent.h"
#include"Camera/CameraComponent.h"
#include"EnhancedInputComponent.h"
#include"EnhancedInputSubsystems.h"
#include"InputActionValue.h"
#include"GameFramework/PlayerController.h"
#include"BaseWeapon.h"
#include"TankHead1.h"
#include"HealthComponent.h"
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

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("Health");

}

void AACharacter::TakeDamage(float amount)
{
	HealthComponent->TakeDamage(amount);
}

void AACharacter::EquipWeapon()
{

	tankhead1 = GetWorld()->SpawnActor<ATankHead1>(TankHeadClass);
	
	if (tankhead1) {
		//UE_LOG(LogTemp, Display, TEXT("XXXXXXX"));
		FAttachmentTransformRules attachrules(EAttachmentRule::SnapToTarget, false);
		tankhead1->AttachToComponent(GetMesh(), attachrules, FName("bodysocket"));

		tankhead1->SetOwner(this);

	}

	weapon = GetWorld()->SpawnActor<ABaseWeapon>(WeaponClass);

	if (weapon) {
		FAttachmentTransformRules attachrules(EAttachmentRule::SnapToTarget, false);
		weapon->AttachToComponent(tankhead1->GetMesh(), attachrules, FName("headsocket"));

		weapon->SetOwner(this);

	}

	//weapon = GetWorld()->SpawnActor<ABaseWeapon>(WeaponClass);

	//if (weapon) {
	//	FAttachmentTransformRules attachrules(EAttachmentRule::SnapToTarget, false);
	//	weapon->AttachToComponent(GetMesh(), attachrules, FName("headsocket"));

	//	weapon->SetOwner(this);

	//}


}

//开火

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
		//拿到角色旋转后的正前方
		FVector forward = FRotationMatrix(yawrotation).GetUnitAxis(EAxis::X);
		//拿到角色旋转后的正右方
		FVector right = FRotationMatrix(yawrotation).GetUnitAxis(EAxis::Y);
		//添加移动输入
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

