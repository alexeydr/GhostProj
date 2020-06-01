// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs\ItemStruct.h"
#include "BaseElementInStorage.generated.h"

/**
 * 
 */
UCLASS()
class GHOSTPROJ_API UBaseElementInStorage : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void SynchronizeProperties() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UImage* ItemImage;

	class AGhostProjCharacter* MainChar;

public:

	void SetParams(FItemParams Param);
	
};
