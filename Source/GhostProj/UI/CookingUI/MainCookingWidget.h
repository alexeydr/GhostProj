// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainCookingWidget.generated.h"

/**
 * 
 */
UCLASS()
class GHOSTPROJ_API UMainCookingWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetStat(class URecipeElement* ElementWidget);

	void SetCookingFood(class URecipeElement* ElementWidget);

protected:

	UFUNCTION()
		void OnCloseClicked();

	void SynchronizeProperties() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class USizeBox* CookingFood;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UScrollBox* MainContainer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* Close;
	
};
