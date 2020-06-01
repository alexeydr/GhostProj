// Fill out your copyright notice in the Description page of Project Settings.


#include "FastfoodComp.h"

// Sets default values for this component's properties
UFastfoodComp::UFastfoodComp()
{

	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UFastfoodComp::BeginPlay()
{
	Super::BeginPlay();

	
}


// Called every frame
void UFastfoodComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

TArray<FItemInWorkStruct> UFastfoodComp::GetMenu()
{
	TArray<FItemInWorkStruct> Items;

	TArray<FName> AllRows = Menu->GetRowNames();

	for (FName NameRow: AllRows)
	{
		FItemInWorkStruct* Elem = Menu->FindRow<FItemInWorkStruct>(NameRow, FString(""), false);
		
		Items.Add(*Elem);

	}


	return Items;
}

