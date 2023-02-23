// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameController.generated.h"

class ATarget;
/**
 * 
 */
UCLASS()
class TA2FEB23_API AGameController : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGameController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	TArray<float> WaveDifficulty;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	TArray<int> WaveSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	TArray<int> WaveSpawnFrequency;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	float MinX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	float MaxX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	float MinY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	float MaxY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	int CurrentWave;

	/** Blueprints: we set these in our blueprint */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	TSubclassOf<ATarget> Target_BP;

private:
	int LeftToSpawn;
	float Clock;
	bool GameWon;


	void ChangeWave(int wave);
	
};
