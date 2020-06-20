// Fill out your copyright notice in the Description page of Project Settings.


#include "RecipeElement.h"
#include "Kismet\GameplayStatics.h"
#include "GhostProjCharacter.h"
#include "InteractI.h"
#include "ToolTipWidgetForCoocking.h"
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
			TakeCooking->SetIsEnabled(false);
			StartCooking->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			TakeCooking->SetVisibility(ESlateVisibility::Hidden);
			StartCooking->OnClicked.AddDynamic(this, &URecipeElement::OnStartCookingClicked);
			this->SetWidgetToolTipText(RecipeElement);
		}

		if (AGhostProjCharacter* MainChar = Cast<AGhostProjCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0)))
		{
			this->SetButtonEnabled(MainChar);
		}
	}

}


void URecipeElement::SetButtonEnabled(AGhostProjCharacter* MainChar)
{
	TArray<FString> IngrArr;
	for (auto Recipe : CurrentRecipe->GetIngredients())
	{
		for (int i = 0; i < Recipe.Count; i++)
		{
			IngrArr.Add(Recipe.IngredientName);
		}
	}
	TArray<FString> FinalArr;
	for (int i = 0; i < IngrArr.Num(); i++)
	{
		for (auto Item : MainChar->GetInventory())
		{

			if (Item->GetItemParam().GetName() == IngrArr[i])
			{
				FinalArr.Add(IngrArr[i]);
			}

		}
	}

	if (FinalArr != IngrArr)
	{
		StartCooking->SetIsEnabled(false);
	}

}


void URecipeElement::OnStartCookingClicked()
{
	if (AGhostProjCharacter* MainChar = Cast<AGhostProjCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		TArray<FString> IngrArr;
		for (auto Recipe : CurrentRecipe->GetIngredients())
		{
			for (int i = 0; i < Recipe.Count; i++)
			{
				IngrArr.Add(Recipe.IngredientName);
			}
		}
		for (auto IngrName: IngrArr)
		{
			for (int i = 0; i< MainChar->GetInventory().Num();i++)
			{
				if (MainChar->GetInventory()[i]->GetItemParam().GetName() == IngrName)
				{
					MainChar->UpdateInventory(nullptr, EActionWithItem::Remove, i);
				}

			}
		}

		OwnerActor->SetCurrentFood(CurrentRecipe);
	}
	
}

void URecipeElement::NativeTick(const FGeometry & MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (GetWorld()->GetTimerManager().GetTimerRemaining(RemainingTimerHandle) > 0 && CookingTime)
	{
		this->CookingTime->SetText(FText::FromString(FString::FromInt((int32)GetWorld()->GetTimerManager().GetTimerRemaining(RemainingTimerHandle))));
	}
	else if(GetWorld()->GetTimerManager().GetTimerRemaining(RemainingTimerHandle) <= 0.f)
	{
		TakeCooking->SetIsEnabled(true);
		
	}


}

void URecipeElement::OnTakeCookingClicked()
{
	for (FInteractItemStruct Item: CurrentRecipe->GetResult())
	{
		OwnerActor->TakeFood(&Item);
	}
	this->RemoveFromParent();
}


void URecipeElement::SetWigdetStats(FRecipeStruct* RecipeElement)
{
	for (auto Result :RecipeElement->GetResult())
	{
		this->Name->SetText(FText::FromString(Result.GetName() + " "));
	}
	this->CookingTime->SetText(FText::FromString(FString::FromInt((int32)RecipeElement->GetCookingTime())));

}

void URecipeElement::SetWidgetToolTipText(FRecipeStruct* RecipeElement)
{
	if (ToolTipWidgetClass)
	{
		UToolTipWidgetForCoocking* ToolTipWidgetRef = CreateWidget<UToolTipWidgetForCoocking>(this, ToolTipWidgetClass);
		if (ToolTipWidgetRef)
		{
			for (auto Ing:RecipeElement->GetIngredients())
			{
				FString ResultText = FString::FromInt(Ing.Count) +" "+ Ing.IngredientName;
				ToolTipWidgetRef->SetIngredients(ResultText);
			}
			this->SetToolTip(ToolTipWidgetRef);
		}
	}

}


