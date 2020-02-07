// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FishingUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class GHOSTPROJ_API UFishingUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	class AFishing* CurrentFishing;

public:

	UFishingUserWidget(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* Left;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* Centr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* Right;
	
	void SetSideColor(uint8 Side = 0);

	void SynchronizeProperties() override;

	FORCEINLINE void SetFishing(class AFishing* Actor) { CurrentFishing = Actor; };
};
