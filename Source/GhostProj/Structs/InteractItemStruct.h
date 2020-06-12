// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemStruct.h"
#include "InteractItemStruct.generated.h"

/**
 * 
 */

UENUM()
enum class EStats : uint8
{
	None 	UMETA(DisplayName = "None"),
	Sleepiness 	UMETA(DisplayName = "Sleepiness"),
	Hunger	UMETA(DisplayName = "Hunger"),
	Thirst	UMETA(DisplayName = "Thirst")
};



USTRUCT(BlueprintType)
struct FInteractItemStruct : public FItemParams
{
	GENERATED_USTRUCT_BODY()

protected:

	UPROPERTY(EditAnywhere)
		float InteractionTime;

	UPROPERTY(EditAnywhere)
		TMap<EStats, float> Effects;


public:

	FInteractItemStruct(FString Name = "", class UTexture2D* Texture = nullptr, TMap<EStats, float> Effects = {}, float InteractionTime = 0.f)
		:FItemParams(Name, Texture)
	{
		this->InteractionTime = InteractionTime;
		this->Effects = Effects;
	}


	FORCEINLINE float GetInteractionTime() { return InteractionTime; };

	FORCEINLINE TMap<EStats, float> GetEffect() { return Effects; };


};