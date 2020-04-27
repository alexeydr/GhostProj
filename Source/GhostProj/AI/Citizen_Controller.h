// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Citizen_Controller.generated.h"

/**
 * 
 */
UCLASS()
class GHOSTPROJ_API ACitizen_Controller : public AAIController
{
	GENERATED_BODY()
	
protected:
	
	ACitizen_Controller();

	void BeginPlay() override;

	void Tick(float DeltaSeconds) override;

	void OnPossess(APawn* InPawn) override;

	UFUNCTION()
		void OnActorDetected(const TArray<AActor*> &DetectedActors);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UAISenseConfig_Sight* SightConfig;

public:

};
