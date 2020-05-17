// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractI.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractI : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GHOSTPROJ_API IInteractI
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void OnInteract(const FString& Name);

	
};
