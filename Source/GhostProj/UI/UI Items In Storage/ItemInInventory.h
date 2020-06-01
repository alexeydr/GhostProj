// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UI Items In Storage/BaseElementInStorage.h"
#include "ItemInInventory.generated.h"

/**
 * 
 */
UCLASS()
class GHOSTPROJ_API UItemInInventory : public UBaseElementInStorage
{
	GENERATED_BODY()

protected:


	virtual void SynchronizeProperties() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* Drop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* Use;

	UFUNCTION()
		void ClickDropButton();

	UFUNCTION()
		void ClickUseButton();

public:

	class AInteractActor* ActForInteract;
	//FORCEINLINE void SetIntåractActorInWidget(class AInteractActor* Act) { this->ActForInteract = Act; };


};
