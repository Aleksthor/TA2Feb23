// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Bullet.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputTriggers.h"

// Sets default values
AMyPlayer::AMyPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMesh);
	StaticMesh->SetRelativeLocation(FVector(0, 0, 0));
	StaticMesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 400.f;
	SpringArm->SetRelativeRotation(FRotator(-15.f, 0.f, 0.f));
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 15.f;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	Ammo = 10;
	MaxAmmo = 10;
    MovementSpeed = 1000;
	Lives = 5;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	

	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController) 
	{
		UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (subsystem) 
		{
			subsystem->AddMappingContext(MappingContext, 0);

		}
	}
}

// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector ForwardVector = FVector(XInput, YInput, 0.f);
	ForwardVector.Normalize();

	FVector NewLocation = GetActorLocation() + (ForwardVector * MovementSpeed * DeltaTime);
	SetActorLocation(NewLocation);
}

// Called to bind functionality to input
void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Get the player controller
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (UEnhancedInputComponent* EnhanceInputCom = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhanceInputCom->BindAction(ForwardInput, ETriggerEvent::Triggered, this, &AMyPlayer::Forward);
		EnhanceInputCom->BindAction(RightInput, ETriggerEvent::Triggered, this, &AMyPlayer::Right);
		EnhanceInputCom->BindAction(ForwardInput, ETriggerEvent::Completed, this, &AMyPlayer::Forward);
		EnhanceInputCom->BindAction(RightInput, ETriggerEvent::Completed, this, &AMyPlayer::Right);
		//EnhanceInputCom->BindAction(MouseX, ETriggerEvent::Started, this, &APawn::AddControllerYawInput);
		//EnhanceInputCom->BindAction(MouseY, ETriggerEvent::Started, this, &APawn::AddControllerPitchInput);
		EnhanceInputCom->BindAction(ShootInput, ETriggerEvent::Started, this, &AMyPlayer::Shoot);
		EnhanceInputCom->BindAction(ReloadInput, ETriggerEvent::Started, this, &AMyPlayer::Reload);
	}
}


void AMyPlayer::Forward(const FInputActionValue& input)
{
	XInput = input.Get<float>();
}
void AMyPlayer::Right(const FInputActionValue& input)
{
	YInput = input.Get<float>();
}

void AMyPlayer::HitByTarget()
{
	Lives--;
	if (Lives <= 0)
	{
		// TODO GAME OVER
	}
}

void AMyPlayer::Shoot(const FInputActionValue& input)
{
	if (Ammo > 0)
	{
		Ammo--;

		GetWorld()->SpawnActor<AActor>(Bullet_BP,									// What to spawn
										GetActorLocation() + FVector(30.f,0.f,0.f), // Location
										GetActorRotation());						// Rotation
	}
}
void AMyPlayer::Reload(const FInputActionValue& input)
{
	Ammo = MaxAmmo;
}
