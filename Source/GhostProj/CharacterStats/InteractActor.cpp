// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractActor.h"

AInteractActor::AInteractActor()
{
	ItemParam.AddClass(AInteractActor::StaticClass());
}

void AInteractActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AInteractActor::UseItem(FItemParams ParamForUse)
{

	this->PlayEffect();

	switch (ParamForUse.GetType())
	{
	case EStats::Thirst:
		MainChar->Thirst = FMath::Clamp(MainChar->Thirst + ParamForUse.GetValue(), 1.f, 100.f);
		break;
	case EStats::Hunger:
		MainChar->Hunger = FMath::Clamp(MainChar->Hunger + ParamForUse.GetValue(), 1.f, 100.f);
		break;
	case EStats::Sleepiness:
		MainChar->Sleepiness = FMath::Clamp(MainChar->Sleepiness + ParamForUse.GetValue(), 1.f, 100.f);
		break;
	}
	MainChar->UpdateUI();

	if (NeedDestroy)
	{
		MainChar->InteractActor = NULL;
		this->Destroy();
	}
}

void AInteractActor::TakeItem()
{
	if (NeedDestroy)
	{
		MainChar->AddItemToInventory(this->ItemParam);
		MainChar->InteractActor = NULL;
		this->Destroy();
	}
}

void AInteractActor::ActionOnInteract()
{
	this->CreateInteractWidget();
}
