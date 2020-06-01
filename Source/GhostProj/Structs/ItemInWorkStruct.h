// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemStruct.h"
#include "ItemInWorkStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FItemInWorkStruct : public FItemParams
{
	GENERATED_USTRUCT_BODY()

protected:

	UPROPERTY(EditAnywhere)
		float Price;

public:

	FItemInWorkStruct(FString Name = "", class UTexture2D* Texture = nullptr,float NewPrice = 0)
		:FItemParams(Name,Texture)
	{
		this->Price = NewPrice;
	}

	void AddPrice(float NewPrice)
	{
		this->Price = NewPrice;
	}

	int GetPrice()
	{
		return Price;
	}
	
};
