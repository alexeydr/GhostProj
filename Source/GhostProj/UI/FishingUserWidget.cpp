// Fill out your copyright notice in the Description page of Project Settings.


#include "FishingUserWidget.h"
#include "Components\TextBlock.h"

UFishingUserWidget::UFishingUserWidget(const FObjectInitializer& ObjectInitializer) 
	:UUserWidget(ObjectInitializer)
{
	bIsFocusable = true;
}


void UFishingUserWidget::SetSideColor(uint8 Side)
{
	FLinearColor NewColor = FLinearColor(0, 0, 255, 1);
	FLinearColor BasicColor = FLinearColor(255, 255, 255, 1);
	switch (Side)
	{
	case 1:
		Left->SetColorAndOpacity(NewColor);
		break;
	case 2:
		Centr->SetColorAndOpacity(NewColor);
		break;
	case 3:
		Right->SetColorAndOpacity(NewColor);
		break;
	default:
		Left->SetColorAndOpacity(BasicColor);
		Right->SetColorAndOpacity(BasicColor);
		Centr->SetColorAndOpacity(BasicColor);
		break;
	}
}

void UFishingUserWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();
	Left->SetText(FText::FromString("Left"));
	Centr->SetText(FText::FromString("Centr"));
	Right->SetText(FText::FromString("Right"));
}
