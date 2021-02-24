// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include <Components/BoxComponent.h>
#include <Kismet/KismetMathLibrary.h>

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnerBounds = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnerBounds"));
	SpawnerBounds->SetBoxExtent(FVector(2000.0f, 2000.0f, 1500.0f));
	RootComponent = SpawnerBounds;
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(SpawnHandle, this, &AEnemySpawner::SpawnerEnemy, SpawnSpan,true);
}

void AEnemySpawner::SpawnerEnemy()
{
	FVector Origin;
	FVector Extends;
	GetActorBounds(false, Origin, Extends);
	FVector SpawnPoint= UKismetMathLibrary::RandomPointInBoundingBox(Origin, Extends);
	GetWorld()->SpawnActor<AEnemy>(EnemyType, SpawnPoint,FRotator::ZeroRotator);
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

