// Fill out your copyright notice in the Description page of Project Settings.


#include "Drome.h"
#include <Components/BoxComponent.h>
#include <PhysicsEngine/PhysicsThrusterComponent.h>
#include <Kismet/KismetMathLibrary.h>
#include <Components/InputComponent.h>

// Sets default values
ADrome::ADrome()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	OutCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("OutCollision"));
	RootComponent = OutCollision;
	OutCollision->SetBoxExtent(FVector(120.f,120.f,120.f));

	OutCollision->SetSimulatePhysics(true);
	OutCollision->BodyInstance.bLockXRotation = true;
	OutCollision->BodyInstance.bLockYRotation = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(OutCollision, TEXT("Mesh"));
	Paddle1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle1"));
	Paddle2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle2"));
	Paddle3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle3"));
	Paddle4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle4"));

	Paddle1->SetupAttachment(Mesh, TEXT("Paddle1"));
	Paddle2->SetupAttachment(Mesh, TEXT("Paddle2"));
	Paddle3->SetupAttachment(Mesh, TEXT("Paddle3"));
	Paddle4->SetupAttachment(Mesh, TEXT("Paddle4"));

	Paddles.Add(Paddle1);
	Paddles.Add(Paddle2);
	Paddles.Add(Paddle3);
	Paddles.Add(Paddle4);

	UpThruster = CreateDefaultSubobject<UPhysicsThrusterComponent>(TEXT("UpThruster"));
	UpThruster->SetupAttachment(RootComponent);
	UpThruster->SetWorldRotation(UKismetMathLibrary::MakeRotFromX(-this->GetActorUpVector()));
	//UpThruster->ThrustStrength = OutCollision->GetMass()*980.0f;
	UpThruster->ThrustStrength =980.0f;
	UpThruster->SetAutoActivate(true);

	ForwardThruster = CreateDefaultSubobject<UPhysicsThrusterComponent>(TEXT("ForwardThruster"));
	ForwardThruster->SetupAttachment(RootComponent);
	ForwardThruster->SetWorldRotation(UKismetMathLibrary::MakeRotFromX(-this->GetActorForwardVector()));
	ForwardThruster->ThrustStrength = 0.0f;
	ForwardThruster->SetAutoActivate(true);
	
}

void ADrome::Lift(float val)
{
	UpThruster->ThrustStrength += val * LiftAcc * GetWorld()->DeltaTimeSeconds;
	UpThruster->ThrustStrength = FMath::Clamp(UpThruster->ThrustStrength, -LiftThrustMax, LiftThrustMax);
}

void ADrome::Forward(float val)
{
	ForwardThruster->ThrustStrength += val * ForwardAcc * GetWorld()->DeltaTimeSeconds;
	ForwardThruster->ThrustStrength = FMath::Clamp(ForwardThruster->ThrustStrength, -ForwardThrustMax, ForwardThrustMax);

	float pitch = Mesh->GetRelativeRotation().Pitch;
	if (FMath::Abs(pitch) < 30.0f)
	{
		Mesh->AddRelativeRotation(FRotator(-100.0f*GetWorld()->DeltaTimeSeconds*val,0.f,0.f));
	}
}

void ADrome::Turn(float val)
{
	OutCollision->AddTorqueInDegrees(-this->GetActorUpVector()*val*TurnStrength);
}

void ADrome::Firing()
{
	FTransform firingPoint=Mesh->GetSocketTransform(TEXT("FiringSocket"));
	GetWorld()->SpawnActor<AMissle>(Bullet, firingPoint);
}

void ADrome::RotatePaddle(float DeltaSeconds)
{
	for (auto Paddle : Paddles)
	{
		Paddle->AddRelativeRotation(FRotator(0.0f, DeltaSeconds*PaddleRotateSpeed, 0.0f));
	}
}

// Called when the game starts or when spawned
void ADrome::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADrome::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//if (InputComponent->GetAxisValue(TEXT("Lift"))==0.0f)
	if (GetInputAxisValue(TEXT("Lift")) == 0.0f)
	{
		UpThruster->ThrustStrength = 980.0f;
	}
	//if (InputComponent->GetAxisValue(TEXT("Forward")) == 0.0f)
	if (GetInputAxisValue(TEXT("Forward")) == 0.0f)
	{
		ForwardThruster->ThrustStrength = 0.0f;

		float pitch = Mesh->GetRelativeRotation().Pitch;
		if (pitch != 0.0f)
		{
			Mesh->AddRelativeRotation(FRotator(-pitch * DeltaTime, 0.f, 0.f));
			if (FMath::Abs(Mesh->GetRelativeRotation().Pitch) < KINDA_SMALL_NUMBER)
			{
				Mesh->AddRelativeRotation(FRotator(0.f, 0.f, 0.f));
			}
		}
	}

	RotatePaddle(DeltaTime);
}

// Called to bind functionality to input
void ADrome::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Lift"), this, &ADrome::Lift);
	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &ADrome::Forward);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ADrome::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ADrome::Firing);
}

