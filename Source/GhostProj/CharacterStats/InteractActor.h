// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structs\ItemStruct.h"
#include "InteractActor.generated.h"

/**
 * 
 */
UCLASS()
class GHOSTPROJ_API AInteractActor : public AActor
{
	GENERATED_BODY()

protected:
	
	AInteractActor();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
		void CreateInteractWidget();

	UFUNCTION(BlueprintImplementableEvent)
		void PlayEffect();

	UPROPERTY(EditAnywhere)
		FItemParams ItemParam;

	UPROPERTY(EditAnywhere)
		bool NeedDestroy = false;

	class AGhostProjCharacter* MainChar;

	UPROPERTY(EditDefaultsOnly)
		class UStaticMeshComponent* StaticMesh;
public:

	FORCEINLINE void SetItemParam(FItemParams NewParam) { this->ItemParam = NewParam; };

	static void EffectItem(FItemParams ParamForUse, class AGhostProjCharacter* MainCharater);

	UFUNCTION(BlueprintCallable)
	void UseItem(FItemParams ParamForUse);

	UFUNCTION(BlueprintCallable)
		void TakeItem();
		
	UFUNCTION(BlueprintCallable)
		FItemParams GetItemParam()
	{
		return ItemParam;
	};

	void ActionOnInteract();
};
