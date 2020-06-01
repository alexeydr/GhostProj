// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemInWork.h"
#include "Components\TextBlock.h"
#include "UI\InteractWithClient.h"
#include "Components\Button.h"


void UItemInWork::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if (AddToBasket)
	{
		AddToBasket->OnClicked.AddDynamic(this, &UItemInWork::ClickAddToBasketButton);
	}

}

void UItemInWork::ClickAddToBasketButton()
{
	if (OwnerWiget)
	{
		OwnerWiget->ClickOnValInBasket(ParamsElement.GetName(),ParamsElement.GetPrice());
	}

}

void UItemInWork::SetParams(FItemInWorkStruct Param)
{
	UBaseElementInStorage::SetParams(Param);

	this->ParamsElement = Param;

	if (PriceText)
	{
		this->PriceText->SetText(FText::FromString(FString::FromInt(Param.GetPrice())));
	}

}

