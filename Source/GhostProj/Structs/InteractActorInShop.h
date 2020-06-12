// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractItemStruct.h"
#include "InteractActorInShop.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FInteractActorInShop : public FInteractItemStruct
{
	GENERATED_USTRUCT_BODY()


protected:

	UPROPERTY(EditAnywhere)
		float Price;

	UPROPERTY(EditAnywhere)
		class UStaticMesh* Mesh;
public:

	FInteractActorInShop(FString Name = "", class UTexture2D* Texture = nullptr, TMap<EStats, float> Effects = {}, float InteractionTime = 0.f, float ItemPrice = 0, class UStaticMesh* ItemMesh = nullptr)
		:FInteractItemStruct(Name, Texture,Effects,InteractionTime)
	{
		this->Price = ItemPrice;
		this->Mesh = ItemMesh;
	}

	FORCEINLINE float GetPrice() { return Price; };

	FORCEINLINE class UStaticMesh* GetMesh() { return Mesh; };
};
