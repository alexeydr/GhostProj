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
	UPROPERTY()
		FString Name;
	UPROPERTY()
		float Cost;
	UPROPERTY()
		class UTexture2D* Texture;

public:
	FFood(FString N, float C, class UTexture2D* T)
	{
		Name = N;
		Cost = C;
		Texture = T;
	}

	FFood()
	{

	}


};
