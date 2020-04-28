// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HorizontalBoxWidget.h"
#include "ElementInShop.h"
#include "Structs\ItemStruct.h"	
#include "ShopUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class GHOSTPROJ_API UShopUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, Category = "UI")
		TSubclassOf<UHorizontalBoxWidget> HorizontalWidgetObj;

	void CreateElements(FItemParams ParamsItem, TSubclassOf<UElementInShop> WidgetObj);

protected:

	UHorizontalBoxWidget* HorizontBoxWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UVerticalBox* MainBox;


};
