// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterStats/InteractActor.h"
#include "IngredientItem.generated.h"

/**
 * 
 */
UCLASS()
class GHOSTPROJ_API AIngredientItem : public AInteractActor
{
	GENERATED_BODY()

protected:

public:

	void ActionOnInteract() override;
	
};
