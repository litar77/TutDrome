// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Missle.generated.h"

UCLASS()
class TUTDROME_API AMissle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMissle();

	//UPROPERTY(VisibleAnywhere)
	//class UBoxComponent * OutCollision;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent * Mesh;

	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent * MovementComp;

	UPROPERTY(EditAnywhere)
	class UParticleSystem * FireParticle;
	UPROPERTY(EditAnywhere)
	class USoundBase * FireSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OverlapHandler(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
