// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.h"
#include "EnemySpawner.generated.h"

UCLASS()
class TUTDROME_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

	UPROPERTY(EditAnywhere)
	class UBoxComponent * SpawnerBounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemySpawner")
	TSubclassOf<AEnemy> EnemyType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemySpawner")
	float SpawnSpan=2.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void SpawnerEnemy();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FTimerHandle SpawnHandle;

};
