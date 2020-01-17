// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorWithTrigger.h"
#include "InteractActor.generated.h"

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

UCLASS()
class GHOSTPROJ_API AInteractActor : public AActorWithTrigger
{
	GENERATED_BODY()

protected:
	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void PlayEffect();

public:
	UPROPERTY(EditAnywhere)
		EStats TypeActor = EStats::None;
	UPROPERTY(EditAnywhere)
		float Value = 0;
	UPROPERTY(EditAnywhere)
		bool NeedDestroy = false;
	
	void ActionOnInteract() override;
};
