// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientAIController.h"
#include "GameFramework/Character.h"
#include "Engine\World.h"
#include "Kismet\GameplayStatics.h"


void AClientAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ACharacter* ControlledPawn = Cast<ACharacter>(InPawn);
	if (ControlledPawn)
	{
		this->MoveToLocation(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation());
	}

}

void AClientAIController::OnUnPossess()
{
	Super::OnUnPossess();
}
