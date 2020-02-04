// Fill out your copyright notice in the Description page of Project Settings.


#include "Fishing.h"

AFishing::AFishing()
{
	
}

FFish AFishing::CreateFish(const int FishCost)
{
	return FFish(FishNames[FMath::FRandRange(0,FishNames.Num()-1)],FishCost);
}

void AFishing::ActionOnInteract()
{
	
}
