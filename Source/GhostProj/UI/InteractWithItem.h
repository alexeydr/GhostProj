// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractWithItem.generated.h"

/**
 * 
 */
UCLASS()
class GHOSTPROJ_API UInteractWithItem : public UUserWidget
{
	GENERATED_BODY()

public:

	FORCEINLINE void SetItem(class AInteractActor* Item) { ItemForInteract = Item; };

protected:

	class AInteractActor* ItemForInteract;

	void SynchronizeProperties() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* Use;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* Take;

	UFUNCTION()
		void OnClickUse();

	UFUNCTION()
		void OnClickTake();
	
};
