// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChatMessage.generated.h"

/**
 * 
 */
UCLASS()
class GHOSTPROJ_API UChatMessage : public UUserWidget
{
	GENERATED_BODY()

protected:


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* MessageTextBlock;

public:

	void SetMessage(FString Message);

	void SetReplic(FString Name, FString Text);

	
};
