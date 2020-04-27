// Fill out your copyright notice in the Description page of Project Settings.


#include "Citizen_Controller.h"
#include "Perception\AIPerceptionComponent.h"
#include "GameFramework/Character.h"
#include "Perception\AISenseConfig_Sight.h"
#include "Kismet\GameplayStatics.h"

#define AI_SightRadius 500.f
#define AI_LoseSightRadius 550.f
#define AI_FieldOfView 90.f
#define AI_SightAge 5.f

ACitizen_Controller::ACitizen_Controller()
{
	PrimaryActorTick.bCanEverTick = true;

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	this->SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));

	SightConfig->SightRadius = AI_SightRadius;
	SightConfig->LoseSightRadius = AI_LoseSightRadius;
	SightConfig->PeripheralVisionAngleDegrees = AI_FieldOfView;
	SightConfig->SetMaxAge(AI_SightAge);
	
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	this->GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	this->GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &ACitizen_Controller::OnActorDetected);
	this->GetPerceptionComponent()->ConfigureSense(*SightConfig);
} 

void ACitizen_Controller::BeginPlay()
{
	Super::BeginPlay();
}

void ACitizen_Controller::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ACitizen_Controller::OnPossess(APawn * InPawn)
{
	Super::OnPossess(InPawn);
}

void ACitizen_Controller::OnActorDetected(const TArray<AActor*> &DetectedActors)
{
	for (auto& Act:DetectedActors)
	{
		if (Act->GetName() == UGameplayStatics::GetPlayerCharacter(GetWorld(),0)->GetName())
		{
			UE_LOG(LogTemp, Warning, TEXT("I see char!"));

		}

	}

}
