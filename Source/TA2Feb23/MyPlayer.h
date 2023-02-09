// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class ABullet;

UCLASS()
class TA2FEB23_API AMyPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Components */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;


	/** Blueprints: we set these in our blueprint */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	TSubclassOf<ABullet> Bullet_BP;

	/** Public Variables */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	int Ammo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	int MaxAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	float MovementSpeed;

	/** Private Variables */
private:

	float XInput;
	float YInput;


private:
	/** Private Functions */

	void Forward(float input);
	void Right(float input);

	void Shoot();
	void Reload();



};
