// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientAIController.h"
#include "Client.h"
#include "Engine\World.h"
#include "Kismet\GameplayStatics.h"


void AClientAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	ControlledPawn = Cast<AClient>(InPawn);
	if (ControlledPawn)
	{
		this->MoveToLocation(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Error"));
	}

}

void AClientAIController::OnUnPossess()
{
	Super::OnUnPossess();
}
