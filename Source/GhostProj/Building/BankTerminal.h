// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorWithTrigger.h"
#include "BankTerminal.generated.h"

/**
 * 
 */
UCLASS()
class GHOSTPROJ_API ABankTerminal : public AActorWithTrigger
{
	GENERATED_BODY()

public:

	virtual void ActionOnInteract();
	
};
