// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UI Items In Storage/BaseElementInStorage.h"
#include "Structs\InteractActorInShop.h"
#include "ItemInShop.generated.h"

/**
 * 
 */
UCLASS()
class GHOSTPROJ_API UItemInShop : public UBaseElementInStorage
{
	GENERATED_BODY()

protected:


	class AInteractActor* ObjToAdd;

	FInteractActorInShop ParamItem;

	virtual void SynchronizeProperties() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* PriceText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* Buy;

	UFUNCTION()
		void ClickBuy();

public:

	void SetObj(class AInteractActor* Obj) { ObjToAdd = Obj; };

	void SetParams(FInteractActorInShop Param);
	
};
