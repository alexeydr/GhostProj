// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractActor.h"

void AInteractActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AInteractActor::ActionOnInteract()
{
	PlayEffect();
	switch (TypeActor)
	{
	case EStats::Thirst:
		MainChar->Thirst = FMath::Clamp(MainChar->Thirst + Value, 1.f, 100.f);
		break;
	case EStats::Hunger:
		
		MainChar->Hunger = FMath::Clamp(MainChar->Hunger + Value, 1.f, 100.f);
		break;
	case EStats::Sleepiness:
		MainChar->Sleepiness = FMath::Clamp(MainChar->Sleepiness + Value, 1.f, 100.f);
		break;
	}
	MainChar->UpdateUI();
	
	if (NeedDestroy)
	{
		MainChar->InteractActor = NULL;
		this->Destroy();
	}
}
