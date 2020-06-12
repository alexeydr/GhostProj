// Fill out your copyright notice in the Description page of Project Settings.


#include "SmallInteractActor.h"
#include "GhostProjCharacter.h"
#include "Structs\InteractActorInShop.h"
#include "Components\StaticMeshComponent.h"
#include "Kismet\GameplayStatics.h"

void ASmallInteractActor::TakeItem()
{
	Super::TakeItem();


	auto Item = NewObject<ASmallInteractActor>(MainChar,ASmallInteractActor::StaticClass());
	
	if (Item)
	{
		Item->SetItemParam(this->ItemParam);
		Item->ItemStruct = this->ItemStruct;
		Item->StaticMesh = this->StaticMesh;
		Item->MainChar = this->MainChar;
		Item->ClassForSpawn = this->ClassForSpawn;
		MainChar->UpdateInventory(Item, EActionWithItem::Add);
	}

	this->Destroy();

}

void ASmallInteractActor::BeginPlay()
{
	Super::BeginPlay();

	this->ItemParam = FItemParams(ItemStruct.GetName(), ItemStruct.GetTexture());

}

void ASmallInteractActor::ModernizeObject(ASmallInteractActor *& Act, FInteractActorInShop * Params,AGhostProjCharacter* Char, TSubclassOf<AInteractActor> Class)
{
	Act->ClassForSpawn = Class;
	Act->SetItemParam(*Params);
	Act->ItemStruct = *Params;
	Act->MainChar = Char;
	Act->StaticMesh->SetStaticMesh(Params->GetMesh());
}

void ASmallInteractActor::UseItem()
{
	Super::UseItem();

	for (auto Elem : this->ItemStruct.GetEffect())
	{
		switch (Elem.Key)
		{
		case EStats::None:
			break;
		case EStats::Sleepiness:
			MainChar->Sleepiness = FMath::Clamp(MainChar->Sleepiness + Elem.Value, 1.f, 100.f);
			break;
		case EStats::Hunger:
			MainChar->Hunger += FMath::Clamp(MainChar->Hunger + Elem.Value, 1.f, 100.f);
			break;
		case EStats::Thirst:
			MainChar->Thirst += FMath::Clamp(MainChar->Thirst + Elem.Value, 1.f, 100.f);
			break;
		default:
			break;
		}

	}	
	
	MainChar->UpdateTime(MainChar->HeroTime->AddTime(0,0,ItemStruct.GetInteractionTime()));
	MainChar->UpdateUI();
	MainChar->UpdateInventory(this, EActionWithItem::Remove);
	
	this->Destroy();


}

void ASmallInteractActor::CreateItem()
{
	Super::CreateItem();

	FActorSpawnParameters Params;

	Params.Owner = MainChar;

	ASmallInteractActor* Item = MainChar->GetWorld()->SpawnActor<ASmallInteractActor>(ClassForSpawn, MainChar->GetActorLocation() + FVector(100, 0, 0), FRotator::ZeroRotator, Params);
	
	if (Item)
	{
		Item->SetItemParam(this->ItemParam);
		Item->ItemStruct = this->ItemStruct;
		Item->StaticMesh->SetStaticMesh(this->StaticMesh->GetStaticMesh());
		Item->MainChar = this->MainChar;


		MainChar->UpdateInventory(this, EActionWithItem::Remove);

	}
	

}
