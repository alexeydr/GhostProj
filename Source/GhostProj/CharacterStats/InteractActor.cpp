// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractActor.h"
#include "Components\StaticMeshComponent.h"
#include "Engine\World.h"
#include "Components\StaticMeshComponent.h"
#include "Components\SceneComponent.h"
#include "GhostProjCharacter.h"
#include "Kismet\GameplayStatics.h"

AInteractActor::AInteractActor()
{
	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	RootComponent = Root;
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("MeshComp"));
	StaticMesh->AttachTo(Root);
}

void AInteractActor::BeginPlay()
{
	Super::BeginPlay();

	MainChar = Cast<AGhostProjCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	
}

void AInteractActor::EffectItem(FItemParams ParamForUse, AGhostProjCharacter * MainCharater)
{
	switch (ParamForUse.GetType())
	{
	case EStats::Thirst:
		MainCharater->Thirst = FMath::Clamp(MainCharater->Thirst + ParamForUse.GetValue(), 1.f, 100.f);
		break;
	case EStats::Hunger:
		MainCharater->Hunger = FMath::Clamp(MainCharater->Hunger + ParamForUse.GetValue(), 1.f, 100.f);
		break;
	case EStats::Sleepiness:
		MainCharater->Sleepiness = FMath::Clamp(MainCharater->Sleepiness + ParamForUse.GetValue(), 1.f, 100.f);
		break;
	}
	MainCharater->UpdateUI();

}

void AInteractActor::UseItem(FItemParams ParamForUse)
{

	this->PlayEffect();

	this->EffectItem(ParamForUse, MainChar);

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
