// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractWithClient.h"
#include "Components\TextBlock.h"

void UInteractWithClient::SynchronizeProperties()
{
	Super::SynchronizeProperties();


}

void UInteractWithClient::SetTextInDesiredFood(const FString Text)
{
	if (DesiredFoodTextBlock)
	{
		DesiredFoodTextBlock->SetText(FText::FromString(Text));
	}

}
