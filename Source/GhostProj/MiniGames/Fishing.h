// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorWithTrigger.h"
#include "UI\FishingUserWidget.h"
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

	TArray<FString> UniqNames = { "UF","US","UT" };

	TArray<FFish> Fishpond;

	UFUNCTION()
	void StartFishing();

	void SetSide();

	UFUNCTION()
	void CheckResult(bool Result, const FFish ResultFish);

	void AfterFishing();


	bool bFishBite;

	int32 SizeX;

	APlayerController* PC;

	//—сылка на виджет
	UFishingUserWidget* WidgetRef;

	float BottomLine;

	float TopLine;

public:

	AFishing();

	UPROPERTY(EditDefaultsOnly, Category = "UI")
		TSubclassOf<UFishingUserWidget> WidgetObj;
	
	FORCEINLINE FFish CreateFish(const int FishCost = 0, const FString &UniqName = "") { 
		if(UniqName.Len()==0) 
			return FFish(FishNames[FMath::FRandRange(0, FishNames.Num() - 1)], FishCost);
		else
			return FFish(UniqName, FishCost);
	};

	void ActionOnInteract() override;
	

	virtual void Tick(float DeltaTime) override;
};
