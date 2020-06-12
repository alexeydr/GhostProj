// Fill out your copyright notice in the Description page of Project Settings.


#include "Shop.h"
#include "CharacterStats\SmallInteractActor.h"
#include "Structs\InteractActorInShop.h"
#include "Structs\ItemStruct.h"
#include "Kismet\GameplayStatics.h"

#define AMOUNT_MERCHANDISE 20

void AShop::ActionOnInteract()
{
	Super::ActionOnInteract();

	this->CreateShopWidget();
	this->RefreshItems(AMOUNT_MERCHANDISE);
}

void AShop::CreateShopWidget()
{
	if (WidgetObj)
	{

		WidgetRef = CreateWidget<UShopUserWidget>(GetWorld(), WidgetObj);

		if (WidgetRef)
			WidgetRef->AddToViewport();
		else
			return;

		UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
		
	}
}

void AShop::RefreshItems(uint8 ItemsInShop)
{
	TArray<FName> AllRows = DBItems->GetRowNames();

	if (WidgetRef)
	{
		
		for (int i = 0; i < ItemsInShop; i++)
		{
			if (ActForSpawn)
			{
				FInteractActorInShop* RowInShop = DBItems->FindRow<FInteractActorInShop>(AllRows[FMath::RandRange(0, AllRows.Num() - 1)], FString(""), false);
				auto Act = ActForSpawn.GetDefaultObject();
				if (RowInShop && Act)
				{
					if (ASmallInteractActor* Small = Cast<ASmallInteractActor>(Act))
					{
							Small->ModernizeObject(Small, RowInShop, Cast<AGhostProjCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)),ActForSpawn);
							Small->InteractWidget = this->InteractWithItemWidget;
							this->AddItemInShop(RowInShop);
							WidgetRef->CreateElements(*RowInShop, ClassElementInShop, Small, RowInShop);

					
					}

				}

			}
			
		}
	}

}
