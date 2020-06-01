// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UI Items In Storage/BaseElementInStorage.h"
#include "Structs\ItemInWorkStruct.h"
#include "ItemInWork.generated.h"

/**
 * 
 */
UCLASS()
class GHOSTPROJ_API UItemInWork : public UBaseElementInStorage
{
	GENERATED_BODY()
	

protected:

	FItemInWorkStruct ParamsElement;

	class UInteractWithClient* OwnerWiget;

	virtual void SynchronizeProperties() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* PriceText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* AddToBasket;

	UFUNCTION()
		void ClickAddToBasketButton();

public:

	FORCEINLINE void SetOwnerWidget(class UInteractWithClient* Widget) {
		if (Widget)
		{
			this->OwnerWiget = Widget;
		}
	};

	void SetParams(FItemInWorkStruct Param);

};
