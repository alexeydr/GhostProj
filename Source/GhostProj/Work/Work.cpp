// Fill out your copyright notice in the Description page of Project Settings.


#include "Work.h"
#include "Client.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

// Sets default values
AWork::AWork()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FFComp = CreateDefaultSubobject<UFastfoodComp>(FName("FastFoodComp"));
}

// Called when the game starts or when spawned
void AWork::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWork::ActionOnInteract()
{
	Super::ActionOnInteract();

	if (this->CheckWorkTime())
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(MainChar->GetController(), this->Workplacepoint);

		this->SpawnClient();
		MainChar->ActWithTrig = NULL;
	}
	else
	{
		this->CreateInfoWidget("Off-Work Time");
	}
	

}

bool AWork::CheckWorkTime()
{
	if (MainChar->HeroTime->GetTime() > FMyDateTime(0, 7, 59) && MainChar->HeroTime->GetTime() < FMyDateTime(0, 18, 59))
	{
		return true;
	}
	return false;
}

void AWork::SpawnClient()
{
	if (ClientClass)
	{
		FActorSpawnParameters Params;
		Params.Owner = this;
		AClient* Client = GetWorld()->SpawnActor<AClient>(ClientClass, Spawnpoint, FRotator::ZeroRotator, Params);
		
	}
}

