// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components\TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "InfoInteractWidget.generated.h"

/**
 * 
 */
UCLASS()
class GHOSTPROJ_API UInfoInteractWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* Name;

public:
	
	FORCEINLINE void SetInteractActorName(FString ActorName) {
		if (Name)
		{
			Name->SetText(FText::FromString(ActorName));

		}
	};
	
};
