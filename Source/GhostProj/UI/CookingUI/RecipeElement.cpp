// Fill out your copyright notice in the Description page of Project Settings.


#include "RecipeElement.h"
#include "InteractI.h"
#include "Components\Button.h"
#include "TimerManager.h"
#include "Components\TextBlock.h"
#include "MiniGames\Cooking.h"
#include "Structs\RecipeStruct.h"

void URecipeElement::SetRemainingTime(FTimerHandle TimerHandle)
{
	this->RemainingTimerHandle = TimerHandle;	
}

void URecipeElement::SetWidgetParam(FRecipeStruct* RecipeElement, ACooking* Owner, bool SelectedFood)
{
	OwnerActor = Owner;
	CurrentRecipe = RecipeElement;

	if (StartCooking && TakeCooking)
	{
		this->SetWigdetStats(RecipeElement);
		

		if (SelectedFood)
		{
			TakeCooking->OnClicked.AddDynamic(this, &URecipeElement::OnTakeCookingClicked);
			StartCooking->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			TakeCooking->SetVisibility(ESlateVisibility::Hidden);
			StartCooking->OnClicked.AddDynamic(this, &URecipeElement::OnStartCookingClicked);
		}
	}

}


void URecipeElement::OnStartCookingClicked()
{
	OwnerActor->SetCurrentFood(CurrentRecipe);

}

void URecipeElement::NativeTick(const FGeometry & MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (GetWorld()->GetTimerManager().GetTimerRemaining(RemainingTimerHandle) > 0 && CookingTime)
	{
		this->CookingTime->SetText(FText::FromString(FString::FromInt((int32)GetWorld()->GetTimerManager().GetTimerRemaining(RemainingTimerHandle))));
	}

}

void URecipeElement::OnTakeCookingClicked()
{
	for (FInteractItemStruct Item: CurrentRecipe->GetResult())
	{
		OwnerActor->TakeFood(&Item);
	}
}


void URecipeElement::SetWigdetStats(FRecipeStruct* RecipeElement)
{
	for (auto Result :RecipeElement->GetResult())
	{
		this->Name->SetText(FText::FromString(Result.GetName() + " "));
	}
	this->CookingTime->SetText(FText::FromString(FString::FromInt((int32)RecipeElement->GetCookingTime())));

}