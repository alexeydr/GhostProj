// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI\HorizontalBoxWidget.h"
#include "UI\ElementInShop.h"
#include "Work/FastfoodComp.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* CloseButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UVerticalBox* VertBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* TotalAmountTextBlock;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
		TSubclassOf<UHorizontalBoxWidget> HorizontalWidgetObj;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
		TSubclassOf<UElementInShop> MenuElem;

	UFUNCTION()
		void ClickCloseButton();


public:

	void ClickOnValInBasket(const FString Name,int Val);

	void AddElementInDesiredFood(const FString Name);

	void FormMenu(UFastfoodComp* FastFoodComp);
	
};
