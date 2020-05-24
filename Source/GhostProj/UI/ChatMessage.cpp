// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatMessage.h"
#include "Components\TextBlock.h"

void UChatMessage::SetMessage(FString Message)
{
	if (MessageTextBlock)
	{
		//FSlateColor Color = FLinearColor(245, 229, 27, 1);
		MessageTextBlock->SetColorAndOpacity(FSlateColor(FColor::Blue));
		MessageTextBlock->SetText(FText::FromString(Message));
	}
}

void UChatMessage::SetReplic(FString Name, FString Text)
{
	if (MessageTextBlock)
	{
		FString Row = Name +": "+ Text;

		MessageTextBlock->SetText(FText::FromString(Row));
	}
}
