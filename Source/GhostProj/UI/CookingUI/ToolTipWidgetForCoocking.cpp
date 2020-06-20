// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolTipWidgetForCoocking.h"
#include "Components\TextBlock.h"
#include "Components\VerticalBox.h"

void UToolTipWidgetForCoocking::SetResult(FString Result)
{
	
}

void UToolTipWidgetForCoocking::SetIngredients(FString Ing)
{
	UTextBlock* TextBlock = NewObject<UTextBlock>(UTextBlock::StaticClass());
	if (!TextBlock)
	{
		UE_LOG(LogTemp, Warning, TEXT("Ne sozdan"));
	}
	if (TextBlock && IngredientsBox)
	{
		TextBlock->SetText(FText::FromString(Ing));
		IngredientsBox->AddChildToVerticalBox(TextBlock);
	}
}
