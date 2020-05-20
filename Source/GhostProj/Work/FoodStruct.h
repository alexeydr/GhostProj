// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "FoodStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FFood:public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

private:
	UPROPERTY(EditAnywhere)
		FString Name;
	UPROPERTY(EditAnywhere)
		float Cost;
	UPROPERTY(EditAnywhere)
		class UTexture2D* Texture;

public:

	FORCEINLINE FString GetFoodName() { return Name; };

	FORCEINLINE float GetFoodCost() { return Cost; };

	FORCEINLINE class UTexture2D* GetFoodTexture() { return Texture; };


	FFood(FString N, float C, class UTexture2D* T)
	{
		Name = N;
		Cost = C;
		Texture = T;
	}

	FFood(FString N, float C)
	{
		Name = N;
		Cost = C;
	}


	FFood()
	{

	}


};
