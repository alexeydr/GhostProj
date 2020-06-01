// Fill out your copyright notice in the Description page of Project Settings.

#pragma warning(disable: 4018)

#include "Client.h"
#include "Engine\World.h"
#include "Kismet\GameplayStatics.h"
#include "Work.h"
#include "AITypes.h"
#include "ClientAIController.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "AIController.h"

// Sets default values
AClient::AClient()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FastFoodComp = CreateDefaultSubobject<UFastfoodComp>(FName("FastFoodComp"));
	

}

AClient::~AClient()
{
	
}

// Called when the game starts or when spawned
void AClient::BeginPlay()
{
	Super::BeginPlay();
	
	AClientAIController* Contrl = Cast<AClientAIController>(this->Controller);
	if (Contrl)
	{
		MovementCompleteDelegate.BindUFunction(this, "Test");
		Contrl->ReceiveMoveCompleted.Add(MovementCompleteDelegate);
	}

	
	this->SetFoodPreferences();
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
		
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(UGameplayStatics::GetPlayerController(GetWorld(), 0), WidgetRef);
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
		return true;
	}
	return false;
}

void AClient::SetWidgetProperty()
{
	
	WidgetRef->FormMenu(this->FastFoodComp);
	WidgetRef->SetOwnerClient(this);
	WidgetRef->ChangeTextInDesiredFood(this->DesiredFood);
	WidgetRef->SetCashBox(Cast<AWork>(this->GetOwner()));
}

void AClient::ChangeClientBalance()
{
	if (FMath::RandRange(1, 100) <= 70)
	{
		this->ClientMoney += FMath::RandRange(0, 100);
	}
	else
	{
		this->ClientMoney -= FMath::RandRange(1, 20);
	}

}

void AClient::GoToNewPoint(EDestination Dest)
{
	AClientAIController* Contrl = Cast<AClientAIController>(this->Controller);
	if (Contrl)
	{
		switch (Dest)
		{
		case ToSpawnPoint:
			CurrentDest = ToSpawnPoint;
			Contrl->MoveToLocation(Cast<AWork>(this->GetOwner())->GetSpawnpoint());
			break;
		case ToOrder:
			CurrentDest = ToOrder;
			Contrl->MoveToLocation(Cast<AWork>(this->GetOwner())->GetOrderPoint());
			break;
		default:
			break;
		}
	}
}

void AClient::ActionOnMoveComplete()
{
	switch (CurrentDest)
	{
	case None:
		return;
		break;
	case ToSpawnPoint:
		this->BeforeDestroy();
		break;
	case ToOrder:
		this->GoToNewPoint(EDestination::ToSpawnPoint);
		break;
	default:
		break;
	}
}

void AClient::BeforeDestroy()
{
	AWork* Own = Cast<AWork>(this->GetOwner());
	if (Own)
	{
		Own->WorkProcess();
	}

	this->Destroy();
}

void AClient::Test(struct FAIRequestID RequestID,EPathFollowingResult::Type Result)
{
	this->ActionOnMoveComplete();

}

void AClient::SetFoodPreferences()
{
	this->ClientMoney = 0;
	DesiredFood.Empty();
	for (int i = 0; i < FMath::RandRange(3, 6); i++)
	{
		if (this->FastFoodComp->GetMenu().Num() > 0)
		{
			FItemInWorkStruct TempFood = this->FastFoodComp->GetMenu()[FMath::RandRange(0, this->FastFoodComp->GetMenu().Num() - 1)];
			this->DesiredFood.Add(TempFood);

			this->ClientMoney += TempFood.GetPrice();
		}
	}

	this->ChangeClientBalance();
	if (WidgetRef)
	{
		WidgetRef->ChangeTextInDesiredFood(this->DesiredFood);

	}
}

void AClient::CompleteOrder(bool Result)
{
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = false;
	if (Result)
	{
		this->GoToNewPoint(EDestination::ToOrder);
		return;
	}
	this->GoToNewPoint(EDestination::ToSpawnPoint);
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
