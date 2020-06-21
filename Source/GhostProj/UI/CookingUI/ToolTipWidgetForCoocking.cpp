// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolTipWidgetForCoocking.h"
#include "Components\TextBlock.h"
#include "Components\VerticalBox.h"

void UToolTipWidgetForCoocking::SetResult(FString Result)
{
	{
		UTextBlock* TextBlock = NewObject<UTextBlock>(UTextBlock::StaticClass());

		if (TextBlock && IngredientsBox)
		{
			TextBlock->SetText(FText::FromString(Result));
			ResultBox->AddChildToVerticalBox(TextBlock);
		}
	}
}

void UToolTipWidgetForCoocking::SetIngredients(FString Ing)
{
	UTextBlock* TextBlock = NewObject<UTextBlock>(UTextBlock::StaticClass());

	if (TextBlock && IngredientsBox)
	{
		TextBlock->SetText(FText::FromString(Ing));
		IngredientsBox->AddChildToVerticalBox(TextBlock);
	}
}
