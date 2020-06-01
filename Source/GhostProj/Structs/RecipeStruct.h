// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CookingMetod.h"
#include "ItemStruct.h"
#include "UObject/NoExportTypes.h"
#include "RecipeStruct.generated.h"

/**
 * 
 */

USTRUCT()
struct FIngredients
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere)
		FString Name;
	UPROPERTY(EditAnywhere)
		TEnumAsByte<ECookingMetods> Metod;

};

USTRUCT(BlueprintType)
struct FRecipeStruct : public FItemParams
{
	GENERATED_USTRUCT_BODY()

private:

	UPROPERTY(EditAnywhere)
		TArray<FIngredients> Ingredients;
public:

	
	bool operator ==(FRecipeStruct Param)
	{
		if (true)
		{
			return true;
		}
		return false;
	}

};


