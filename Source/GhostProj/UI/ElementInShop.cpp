// Fill out your copyright notice in the Description page of Project Settings.


#include "ElementInShop.h"
#include "Components\Image.h"
#include "Components\TextBlock.h"

void UElementInShop::SetParams(FItemParams Param)
{
	ItemImage->SetBrushFromTexture(Param.GetTexture());
	ItemName->SetText(FText::FromString(Param.GetName()));
	if (Price)
	{
		Price->SetText(FText::FromString(FString::FromInt(Param.GetPrice())));
	}
	ElemetStat = Param;
}
