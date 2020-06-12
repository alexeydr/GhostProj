// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorWithTrigger.h"
#include "UI\InteractWithItem.h"
#include "CharacterStats\InteractActor.h"
#include "UI\ShopUserWidget.h"
#include "Shop.generated.h"

/**
 * 
 */
UCLASS()
class GHOSTPROJ_API AShop : public AActorWithTrigger
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UInteractWithItem> InteractWithItemWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AInteractActor> ActForSpawn;

	TArray<struct FItemParams*> Items;

	UShopUserWidget* WidgetRef;

	UPROPERTY(EditDefaultsOnly)
	class UDataTable* DBItems;

	void CreateShopWidget();

	void RefreshItems(uint8 ItemsInShop);

public:
	void ActionOnInteract() override;


	FORCEINLINE TArray<struct FItemParams*> GetItemsInShop()
	{
		return Items;
	}


	FORCEINLINE void AddItemInShop(struct FItemParams* NewItem)
	{
		Items.Add(NewItem);
	}


	UPROPERTY(EditDefaultsOnly, Category = "UI")
		TSubclassOf<UShopUserWidget> WidgetObj;


	UPROPERTY(EditDefaultsOnly, Category = "UI")
		TSubclassOf<UBaseElementInStorage> ClassElementInShop;

};
