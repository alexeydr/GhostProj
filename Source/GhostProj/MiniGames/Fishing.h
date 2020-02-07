// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorWithTrigger.h"
#include "Fishing.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FFish
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Fish")
		FString FishName;
	UPROPERTY(BlueprintReadWrite, Category = "Fish")
		int Cost;

	FFish(const FString &N = "None",const int C = 0)
	{
		FishName = N;
		Cost = C;
	}

	FORCEINLINE bool operator ==(const FFish &Fish) const
	{
		if (Fish.FishName == Fish.FishName)
		{
			return true;
		}

		return false;
	}

};


UCLASS()
class GHOSTPROJ_API AFishing : public AActorWithTrigger
{
	GENERATED_BODY()
	
protected:

	TArray<FString> FishNames = { "F","S","T" };

	TArray<FFish> Fishpond;

public:

	AFishing();
	
	FFish CreateFish(const int FishCost);

	void ActionOnInteract() override;
};
