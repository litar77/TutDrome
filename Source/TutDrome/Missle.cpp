// Fill out your copyright notice in the Description page of Project Settings.


#include "Missle.h"
#include "GameFramework\ProjectileMovementComponent.h"
#include "Enemy.h"
#include "TutDromeGameModeBase.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AMissle::AMissle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	Mesh->SetGenerateOverlapEvents(true);
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AMissle::OverlapHandler);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	MovementComp->InitialSpeed = 3000.0f;
	

}

// Called when the game starts or when spawned
void AMissle::BeginPlay()
{
	SetLifeSpan(8.0f);
	Super::BeginPlay();
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FireParticle, this->GetActorLocation());
	//UGameplayStatics::PlaySoundAtLocation(this, FireSound, this->GetActorLocation(), 2.0f);
	UGameplayStatics::PlaySound2D(this, FireSound, 2.0f);
	
}

void AMissle::OverlapHandler(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->IsA<AEnemy>())
	{
		OtherActor->Destroy();
		ATutDromeGameModeBase* gm = Cast<ATutDromeGameModeBase>(GetWorld()->GetAuthGameMode());
		if (gm!=nullptr)
		{
			gm->points+=10;
		}
		this->Destroy();
	}
}

// Called every frame
void AMissle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

