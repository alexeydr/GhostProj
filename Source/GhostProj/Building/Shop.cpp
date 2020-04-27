// Fill out your copyright notice in the Description page of Project Settings.


#include "Shop.h"
#include "Structs\ItemStruct.h"
#include "Kismet\GameplayStatics.h"

void AShop::ActionOnInteract()
{
	Super::ActionOnInteract();

	this->CreateShopWidget();
	this->RefreshItems(4);
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

	for (size_t i = 0; i < ItemsInShop; i++)
	{
		FItemParams* Row = DBItems->FindRow<FItemParams>(AllRows[FMath::RandRange(0,AllRows.Num()-1)], FString(""), false);
		this->AddItemInShop(Row);
		
	}

	for (auto Elem:this->GetItemsInShop())
	{
		UE_LOG(LogTemp, Warning, TEXT("Name: %s"), *Elem->GetName());
	}
}
