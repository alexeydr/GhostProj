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

	FFish(const FString &N,const int C)
	{
		FishName = N;
		Cost = C;
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
