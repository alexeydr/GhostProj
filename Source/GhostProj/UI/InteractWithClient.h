// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractWithClient.generated.h"

/**
 * 
 */
UCLASS()
class GHOSTPROJ_API UInteractWithClient : public UUserWidget
{
	GENERATED_BODY()

protected:

	void SynchronizeProperties() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* DesiredFoodTextBlock;


public:

	void SetTextInDesiredFood(const FString Text);

	
};
