// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Missle.h"
#include "Drome.generated.h"

UCLASS()
class TUTDROME_API ADrome : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADrome();

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent * OutCollision;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent * Mesh;


	UPROPERTY(EditAnywhere)
	TSubclassOf<AMissle> Bullet;


	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent * Paddle1;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent * Paddle2;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent * Paddle3;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent * Paddle4;

	UPROPERTY(VisibleAnywhere)
	class UPhysicsThrusterComponent * UpThruster;
	UPROPERTY(VisibleAnywhere)
	class UPhysicsThrusterComponent * ForwardThruster;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Init")
	float LiftAcc = 10000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Init")
	float LiftThrustMax = 2000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Init")
	float ForwardAcc = 1000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Init")
	float ForwardThrustMax = 2000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Init")
	float TurnStrength = 5000000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Init")
	float PaddleRotateSpeed=2000.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void Lift(float val);

	UFUNCTION()
	void Forward(float val);

	UFUNCTION()
	void Turn(float val);

	UFUNCTION()
	void Firing();

	void RotatePaddle(float DeltaSeconds);

	TArray<UStaticMeshComponent *> Paddles;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
