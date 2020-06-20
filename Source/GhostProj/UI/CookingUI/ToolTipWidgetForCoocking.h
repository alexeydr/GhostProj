// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ToolTipWidgetForCoocking.generated.h"

/**
 * 
 */
UCLASS()
class GHOSTPROJ_API UToolTipWidgetForCoocking : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UVerticalBox* IngredientsBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UVerticalBox* ResultBox;

	void SetIngredients(FString Ing);

	void SetResult(FString Result);
	
};
