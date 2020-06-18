// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RecipeElement.generated.h"

/**
 * 
 */
UCLASS()
class GHOSTPROJ_API URecipeElement : public UUserWidget
{
	GENERATED_BODY()

protected:

	void SetWigdetStats(struct FRecipeStruct* RecipeElement);

	class ACooking* OwnerActor;

	struct FRecipeStruct* CurrentRecipe;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* CookingTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* StartCooking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* TakeCooking;

	UFUNCTION()
		void OnTakeCookingClicked();

	UFUNCTION()
		void OnStartCookingClicked();

	FTimerHandle RemainingTimerHandle;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:

	void SetRemainingTime(FTimerHandle TimerHandle);

	void SetWidgetParam(struct FRecipeStruct* RecipeElement, class ACooking* Owner, bool SelectedFood);
	
};
