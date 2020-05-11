// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FastfoodComp.h"
#include "Client.generated.h"

UCLASS()
class GHOSTPROJ_API AClient : public ACharacter
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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE TArray<FFood> GetDesiredFood() { return DesiredFood;  };

};
