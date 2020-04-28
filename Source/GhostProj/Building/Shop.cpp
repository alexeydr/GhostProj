// Fill out your copyright notice in the Description page of Project Settings.


#include "Shop.h"
#include "Structs\ItemStruct.h"
#include "Kismet\GameplayStatics.h"

#define AMOUNT_MERCHANDISE 7

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
		for (size_t i = 0; i < ItemsInShop; i++)
		{
			FItemParams* Row = DBItems->FindRow<FItemParams>(AllRows[FMath::RandRange(0, AllRows.Num() - 1)], FString(""), false);
			this->AddItemInShop(Row);
			WidgetRef->CreateElements(*Row, ClassElementInShop);
		}
	}

}
