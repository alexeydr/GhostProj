// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorWithTrigger.h"
#include "GhostProjCharacter.h"
#include "Components\StaticMeshComponent.h"
#include "Kismet\GameplayStatics.h"
#include "Components\BoxComponent.h"

// Sets default values
AActorWithTrigger::AActorWithTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComp = CreateDefaultSubobject<UBoxComponent>(FName("BoxComp"));
	BoxComp->AttachTo(GetRootComponent());
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("MeshComp"));
	StaticMesh->AttachTo(GetRootComponent());
}

// Called when the game starts or when spawned
void AActorWithTrigger::BeginPlay()
{
	Super::BeginPlay();
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AActorWithTrigger::OnBegin);
	BoxComp->OnComponentEndOverlap.AddDynamic(this, &AActorWithTrigger::OnEnd);
	MainChar = Cast<AGhostProjCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

// Called every frame
void AActorWithTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AActorWithTrigger::OnBoxBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor == MainChar)
	{
		MainChar->InteractActor = this;
	}
}

void AActorWithTrigger::OnBoxEndOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == MainChar)
	{
		MainChar->InteractActor = NULL;
	}
}

