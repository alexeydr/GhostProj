// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UI\InteractWithClient.h"
#include "InteractI.h"
#include "FastfoodComp.h"
#include "Client.generated.h"

UCLASS()
class GHOSTPROJ_API AClient : public ACharacter, public IInteractI
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AClient();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
		UFastfoodComp* FastFoodComp;

	TArray<FFood> DesiredFood;

	bool TypeOrder = FMath::RandBool();

	UPROPERTY(EditDefaultsOnly, Category = "UI")
		TSubclassOf<UInteractWithClient> WidgetObj;


	UInteractWithClient* WidgetRef;

	bool CreateInteractWidget();

	void SetWidgetProperty();

public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE TArray<FFood> GetDesiredFood() { return DesiredFood;  };

	void ActionOnInteract();

};
