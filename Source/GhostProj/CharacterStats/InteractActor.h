// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structs\ItemStruct.h"
#include "UI\InfoInteractWidget.h"
#include "UI\InteractWithItem.h"
#include "InteractI.h"
#include "InteractActor.generated.h"

/**
 * 
 */
UCLASS()
class GHOSTPROJ_API AInteractActor : public AActor, public IInteractI
{
	GENERATED_BODY()

protected:
	
	AInteractActor();

	virtual void BeginPlay() override;

	UFUNCTION()
		void CreateInteractWidget();

	/*UFUNCTION(BlueprintImplementableEvent)
		void PlayEffect();*/

	UPROPERTY(EditAnywhere)
		FItemParams ItemParam;

	class AGhostProjCharacter* MainChar;

	UPROPERTY(EditDefaultsOnly)
		class UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UInteractWithItem> InteractWidget;
public:
 
	FORCEINLINE void SetItemParam(FItemParams NewParam) { this->ItemParam = NewParam; };
	
	virtual void UseItem() {};
	
	virtual void TakeItem() {};

	virtual void CreateItem() {};
		
	UFUNCTION(BlueprintCallable)
		FItemParams GetItemParam()
	{
		return ItemParam;
	};

	virtual void ActionOnInteract();
};
