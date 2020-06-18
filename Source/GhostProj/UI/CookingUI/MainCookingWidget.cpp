// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCookingWidget.h"
#include "Kismet\GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components\Button.h"
#include "Components\SizeBox.h"
#include "Components\ScrollBox.h"
#include "RecipeElement.h"

void UMainCookingWidget::SetStat(URecipeElement* ElementWidget)
{
	if (MainContainer)
	{
		MainContainer->AddChild(ElementWidget);
	}
}

void UMainCookingWidget::SetCookingFood(URecipeElement * ElementWidget)
{
	if (CookingFood)
	{
		CookingFood->AddChild(ElementWidget);
	}
}

void UMainCookingWidget::OnCloseClicked()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = false;
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	this->RemoveFromParent();
}

void UMainCookingWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if (Close)
	{
		Close->OnClicked.AddDynamic(this, &UMainCookingWidget::OnCloseClicked);
	}
}
