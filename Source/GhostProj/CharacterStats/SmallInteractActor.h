// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structs\InteractItemStruct.h"
#include "CharacterStats/InteractActor.h"
#include "SmallInteractActor.generated.h"

/**
 * 
 */
UCLASS()
class GHOSTPROJ_API ASmallInteractActor : public AInteractActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere)
	FInteractItemStruct ItemStruct;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ASmallInteractActor> ClassForSpawn;

	virtual void BeginPlay() override;

public:


	FInteractItemStruct GetItemStruct() { return ItemStruct; };

	void ModernizeObject(ASmallInteractActor* &Act, struct FInteractActorInShop* Params, class AGhostProjCharacter* Char, TSubclassOf<AInteractActor> Class);

	virtual void UseItem();

	virtual void CreateItem();

	virtual void TakeItem();
	
};