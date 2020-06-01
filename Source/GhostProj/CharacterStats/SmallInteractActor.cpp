// Fill out your copyright notice in the Description page of Project Settings.


#include "SmallInteractActor.h"
#include "GhostProjCharacter.h"
#include "Components\StaticMeshComponent.h"
#include "Kismet\GameplayStatics.h"

void ASmallInteractActor::TakeItem()
{
	Super::TakeItem();


	auto Test = NewObject<ASmallInteractActor>(MainChar,ASmallInteractActor::StaticClass());
	
	if (Test)
	{
		Test->SetItemParam(this->ItemParam);
		Test->ItemStruct = this->ItemStruct;
		Test->StaticMesh = this->StaticMesh;
		Test->MainChar = this->MainChar;
		Test->ClassForSpawn = this->ClassForSpawn;
		MainChar->UpdateInventory(Test, EActionWithItem::Add);
	}

	this->Destroy();

}

void ASmallInteractActor::BeginPlay()
{
	Super::BeginPlay();

	this->ItemParam = FItemParams(ItemStruct.GetName(), ItemStruct.GetTexture());

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
			MainChar->Hunger += Elem.Value;
			break;
		case EStats::Thirst:
			MainChar->Thirst += Elem.Value;
			break;
		default:
			break;
		}

	}	
	
	MainChar->UpdateUI();
	MainChar->UpdateInventory(this, EActionWithItem::Remove);
	
	this->Destroy();


}

void ASmallInteractActor::CreateItem()
{
	Super::CreateItem();

	FActorSpawnParameters Params;

	Params.Owner = MainChar;

	auto Item = GetWorld()->SpawnActor<ASmallInteractActor>(ClassForSpawn , MainChar->GetActorLocation() + FVector(100, 0, 0), FRotator::ZeroRotator, Params);
	

	if (Item)
	{
		Item->SetItemParam(this->ItemParam);
		Item->ItemStruct = this->ItemStruct;
		Item->StaticMesh->SetStaticMesh(this->StaticMesh->GetStaticMesh());
		Item->MainChar = this->MainChar;


		MainChar->UpdateInventory(this, EActionWithItem::Remove);

		UE_LOG(LogTemp, Warning, TEXT("Name: %s"), *Item->GetName());
	}


}
