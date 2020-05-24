// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeComp.h"
#include "TimerManager.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UTimeComp::UTimeComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTimeComp::BeginPlay()
{
	Super::BeginPlay();
	

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle,this,&UTimeComp::TimeFlow ,1.f , true);
	
	
}

void UTimeComp::TimeFlow()
{
	AddTime(0, 0, Modifier);
}


// Called every frame
void UTimeComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FMyDateTime UTimeComp::AddTime(int32 Days, int32 Hours, int32 Minutes)
{
	
	if (CurrentTime.Minutes + Minutes >= 60)
	{

		CurrentTime.Hours++;
		CurrentTime.Minutes += Minutes - 60;
	}
	else
	{
		CurrentTime.Minutes += Minutes;
	}
	if (CurrentTime.Hours + Hours >= 24)
	{
		CurrentTime.Days++;
		CurrentTime.Hours += Hours - 24;
	}
	else
	{
		CurrentTime.Hours += Hours;
	}

	CurrentTime.Days += Days;

	return CurrentTime;
}

