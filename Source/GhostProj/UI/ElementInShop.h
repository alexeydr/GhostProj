// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structs\ItemStruct.h"
#include "Blueprint/UserWidget.h"
#include "ElementInShop.generated.h"

/**
 * 
 */
UCLASS()
class GHOSTPROJ_API UElementInShop : public UUserWidget
{
	GENERATED_BODY()

protected:

	FItemParams ElementStat;

	void SynchronizeProperties() override;

	UFUNCTION()
		void ClickDropButton();

	UFUNCTION()
		void ClickBuyButton();

	UFUNCTION()
		void ClickUseButton();

	UFUNCTION()
		void ClickAddToBasketButton();

	class UInteractWithClient* WidgetOwner;

	class AGhostProjCharacter* MainChar;

public:

	FORCEINLINE void SetOwnerWidget(class UInteractWithClient* Own) { this->WidgetOwner = Own; };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* ItemImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional))
	class UButton* Drop;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional))
	class UButton* Use;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional))
		class UButton* Buy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional))
		class UButton* AddToBasket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional))
		class UTextBlock* Price;

	void SetParams(FItemParams Param);
};
