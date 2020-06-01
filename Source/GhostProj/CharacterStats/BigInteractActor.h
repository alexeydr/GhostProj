// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterStats/InteractActor.h"
#include "BigInteractActor.generated.h"

/**
 * 
 */
UCLASS()
class GHOSTPROJ_API ABigInteractActor : public AInteractActor
{
	GENERATED_BODY()

public:

	virtual void UseItem();


	virtual void TakeItem();
	
};
