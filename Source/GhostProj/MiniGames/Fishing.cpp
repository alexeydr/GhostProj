// Fill out your copyright notice in the Description page of Project Settings.


#include "Fishing.h"
#include "Engine\World.h"
#include "TimerManager.h"
#include "ConstructorHelpers.h"
#include "GameFramework\PlayerController.h"

#define CHANCE 80

AFishing::AFishing()
{
	bFishBite = false;
	
}

void AFishing::ActionOnInteract()
{
	PC = Cast<APlayerController>(MainChar->GetController());
	if (PC && WidgetObj)
	{

		WidgetRef = CreateWidget<UFishingUserWidget>(GetWorld(), WidgetObj);

		if (WidgetRef)
			WidgetRef->AddToViewport();
		else
			return;

		WidgetRef->SetFishing(this);
		PC->bShowMouseCursor = true;
		this->StartFishing();
	}
}

void AFishing::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bFishBite)
	{
		float PosX, PosY;
		PC->GetMousePosition(PosX, PosY);

		if (PosX<TopLine && PosX>BottomLine)
		{
			GetWorldTimerManager().ClearAllTimersForObject(this);
			if (CHANCE > FMath::RandRange(1, 100))
				this->CheckResult(true,this->CreateFish(FMath::RandRange(1, 10), FishNames[FMath::RandRange(0, FishNames.Num() - 1)]));
			else
				this->CheckResult(true, this->CreateFish(FMath::RandRange(40, 80), UniqNames[FMath::RandRange(0, UniqNames.Num() - 1)]));
		}
	}
}


void AFishing::StartFishing()
{

	int32 SizeY;
	PC->GetViewportSize(SizeX, SizeY);
	WidgetRef->SetUserFocus(PC);

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AFishing::SetSide, FMath::FRandRange(1.f, 3.f), false);
}

void AFishing::SetSide()
{
	int16 Side = FMath::RandRange(1, 3);
	FTimerDelegate TimerDel;
	FTimerHandle TimerHandle;
	WidgetRef->SetSideColor(Side);

	switch (Side)
	{
	case 1:
		TopLine = SizeX / 3;
		BottomLine = 0; 
		break;
	case 2:
		TopLine = SizeX - SizeX / 3;
		BottomLine = SizeX / 3;
		break;
	case 3:
		TopLine = SizeX;
		BottomLine = SizeX - SizeX / 3;
		break;
	}
	bFishBite = true;


	TimerDel.BindUFunction(this, FName("CheckResult"), false,this->CreateFish());
	GetWorldTimerManager().SetTimer(TimerHandle, TimerDel, 1.f, false);
}

void AFishing::CheckResult(bool Result, const FFish ResultFish)
{
	bFishBite = false;
	WidgetRef->SetSideColor();

	if (Result)
	{
		UE_LOG(LogTemp, Warning, TEXT("Name: %s,Cost: %i "),*ResultFish.FishName,ResultFish.Cost);
		this->StartFishing();
		Fishpond.Add(ResultFish);
	}
	else
	{
		this->AfterFishing();
		UE_LOG(LogTemp, Warning, TEXT("Ne Poymal"));
	}

}

void AFishing::AfterFishing()
{
	PC->bShowMouseCursor = false;
	for (FFish Elem:Fishpond)
	{
		MainChar->Money += Elem.Cost;
	}
	WidgetRef->SetFishing(nullptr);
	WidgetRef->RemoveFromParent();
	MainChar->UpdateUI();
}
