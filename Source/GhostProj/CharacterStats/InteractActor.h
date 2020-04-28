// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorWithTrigger.h"
#include "Structs\ItemStruct.h"
#include "InteractActor.generated.h"

/**
 * 
 */
UCLASS()
class GHOSTPROJ_API AInteractActor : public AActorWithTrigger
{
	GENERATED_BODY()

protected:
	
	AInteractActor();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
		void CreateInteractWidget();

	UFUNCTION(BlueprintImplementableEvent)
		void PlayEffect();

	UPROPERTY(EditAnywhere)
		FItemParams ItemParam;

	UPROPERTY(EditAnywhere)
		bool NeedDestroy = false;

public:

	UFUNCTION(BlueprintCallable)
		void UseItem(FItemParams ParamForUse);

	UFUNCTION(BlueprintCallable)
		void TakeItem();
		
	UFUNCTION(BlueprintCallable)
		FItemParams GetItemParam()
	{
		return ItemParam;
	};

	void ActionOnInteract() override;
};
