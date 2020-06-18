// Fill out your copyright notice in the Description page of Project Settings.


#include "Cooking.h"
#include "TimerManager.h"
#include "CharacterStats\SmallInteractActor.h"
#include "Engine/World.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet\GameplayStatics.h"
#include "UI\CookingUI\MainCookingWidget.h"
#include "UI\CookingUI\RecipeElement.h"
#include "Structs\RecipeStruct.h"

void ACooking::ActionOnInteract()
{
	Super::ActionOnInteract();

	if (MainWidget && RecipeElem && RecipesDT)
	{
		MainWidgetRef = CreateWidget<UMainCookingWidget>(GetWorld(), MainWidget);

		if (MainWidgetRef)
		{
			
			MainWidgetRef->AddToViewport();
			APlayerController* Control = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			if (Control)
			{
				Control->bShowMouseCursor = true;
				UWidgetBlueprintLibrary::SetInputMode_UIOnly(Control, MainWidgetRef);
			}

			this->SetRecipeElements();
			this->SetCurrentFood(this->FoodElement);
		}
	}

}

void ACooking::SetCurrentFood(FRecipeStruct * Struct)
{
	if (Struct)
	{
		URecipeElement* RecipeWidgetRef = CreateWidget<URecipeElement>(GetWorld(), RecipeElem);

		if (RecipeWidgetRef)
		{
			if (!this->FoodElement)
			{
				this->FoodElement = Struct;

				FTimerHandle CompleteFoodTimerHandle;
				GetWorld()->GetTimerManager().SetTimer(CompleteFoodTimerHandle, this, &ACooking::StartCooking, this->FoodElement->GetCookingTime(), false);
				RecipeWidgetRef->SetRemainingTime(CompleteFoodTimerHandle);
			}
			
			MainWidgetRef->SetCookingFood(RecipeWidgetRef);
			RecipeWidgetRef->SetWidgetParam(this->FoodElement, this, true);
		}
	}
}

void ACooking::TakeFood(FInteractItemStruct * Struct)
{

	ASmallInteractActor* Item = NewObject<ASmallInteractActor>(MainChar, ASmallInteractActor::StaticClass());
	if (Item)
	{
		Item->SetItemParam(*Struct);
		Item->SetItemStruct(*Struct);
		Item->SetStaticMeshInActor(Struct->GetStaticMesh());
		Item->SetMainChar(this->MainChar);
		Item->SetClassForSpawn(this->SpawnItemClass);

		MainChar->UpdateInventory(Item, EActionWithItem::Add);
	}

}

void ACooking::StartCooking()
{
	UE_LOG(LogTemp, Warning, TEXT("Food complete"));
}

void ACooking::SetRecipeElements()
{
	TArray<FName> AllRows = RecipesDT->GetRowNames();

	for (FName Row : AllRows)
	{
		FRecipeStruct* RowInRecipes = RecipesDT->FindRow<FRecipeStruct>(Row, FString(""), false);

		URecipeElement* RecipeWidgetRef = CreateWidget<URecipeElement>(GetWorld(), RecipeElem);

		if (RecipeWidgetRef)
		{
			MainWidgetRef->SetStat(RecipeWidgetRef);
			RecipeWidgetRef->SetWidgetParam(RowInRecipes,this,false);
		}

	}

	

}
