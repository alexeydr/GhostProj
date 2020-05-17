// Fill out your copyright notice in the Description page of Project Settings.


#include "Client.h"
#include "Engine\World.h"
#include "Kismet\GameplayStatics.h"
#include "AIController.h"

// Sets default values
AClient::AClient()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FastFoodComp = CreateDefaultSubobject<UFastfoodComp>(FName("FastFoodComp"));
}

// Called when the game starts or when spawned
void AClient::BeginPlay()
{
	Super::BeginPlay();
	
	for (size_t i = 0; i < FMath::RandRange(1,4); i++)
	{
		if (this->FastFoodComp->GetMenu().Num() > 0)
		{
			this->DesiredFood.Add(this->FastFoodComp->GetMenu()[FMath::RandRange(0, this->FastFoodComp->GetMenu().Num() - 1)]);

		}
	}

}

bool AClient::CreateInteractWidget()
{
	if (WidgetObj)
	{
		WidgetRef = CreateWidget<UInteractWithClient>(GetWorld(), WidgetObj);

		if (WidgetRef)
			WidgetRef->AddToViewport();
		else
			return false;

		UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
		return true;
	}
	return false;
}

void AClient::SetWidgetProperty()
{
	for (FFood Elem: DesiredFood)
	{
		WidgetRef->SetTextInDesiredFood(Elem.GetFoodName());
	}

}

// Called every frame
void AClient::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AClient::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AClient::ActionOnInteract()
{
	if (this->CreateInteractWidget())
	{
		this->SetWidgetProperty();
	}

}