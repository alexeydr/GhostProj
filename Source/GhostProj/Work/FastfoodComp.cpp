// Fill out your copyright notice in the Description page of Project Settings.


#include "FastfoodComp.h"

// Sets default values for this component's properties
UFastfoodComp::UFastfoodComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFastfoodComp::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UFastfoodComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

TArray<FFood> UFastfoodComp::GetMenu()
{
	TArray<FFood> Items;

	TArray<FName> AllRows = Menu->GetRowNames();

	for (FName NameRow: AllRows)
	{
		FFood* Elem = Menu->FindRow<FFood>(NameRow, FString(""), false);
		
		Items.Add(*Elem);

	}


	return Items;
}

