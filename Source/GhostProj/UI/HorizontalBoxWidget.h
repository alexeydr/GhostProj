// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HorizontalBoxWidget.generated.h"

/**
 * 
 */
UCLASS()
class GHOSTPROJ_API UHorizontalBoxWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UHorizontalBox* HorizonBox;
	
};
