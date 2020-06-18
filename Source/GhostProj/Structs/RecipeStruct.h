// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CharacterStats\InteractActor.h"
#include "Structs\InteractItemStruct.h"
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
		FString IngredientName;
	UPROPERTY(EditAnywhere)
		TEnumAsByte<ECookingMetods>	CoockingMetod;

};

USTRUCT(BlueprintType)
struct FRecipeStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

private:
	UPROPERTY(EditAnywhere)
		TArray<FInteractItemStruct> Result;

	UPROPERTY(EditAnywhere)
		TArray<FIngredients> Ingredients;
	
	UPROPERTY(EditAnywhere)
		float CookingTime;

public:

	FORCEINLINE TArray<FInteractItemStruct> GetResult() { return Result; };

	FORCEINLINE float GetCookingTime() { return CookingTime; };

	
	/*bool operator ==(FRecipeStruct Param)
	{
		if (this->Result == Param.Name && this->GetTexture() == Param.GetTexture())
		{
			return true;
		}
		return false;
	}*/

};


