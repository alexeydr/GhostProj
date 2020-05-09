// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ClientAIController.generated.h"

/**
 * 
 */
UCLASS()
class GHOSTPROJ_API AClientAIController : public AAIController
{
	GENERATED_BODY()


protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	
	class AClient* ControlledPawn;
};
