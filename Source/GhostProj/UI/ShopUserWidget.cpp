// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopUserWidget.h"
#include "Components\VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components\HorizontalBox.h"

#define AMOUNT_ELEMENTS 5

void UShopUserWidget::CreateElements(FItemParams ParamsItem, TSubclassOf<UElementInShop> WidgetObj)
{
	if (WidgetObj && HorizontalWidgetObj)
	{
		if (HorizontBoxWidget)
		{
			if (HorizontBoxWidget->HorizonBox->GetChildrenCount() < AMOUNT_ELEMENTS)
			{
				UElementInShop* ProductWidget = CreateWidget<UElementInShop>(GetWorld(), WidgetObj);
				if (ProductWidget)
				{
					UHorizontalBoxSlot* Slot = HorizontBoxWidget->HorizonBox->AddChildToHorizontalBox(ProductWidget);
					
					FSlateChildSize Size;

					Size.SizeRule = ESlateSizeRule::Fill;
					Size.Value = 0.2;

					Slot->SetPadding(FMargin(50, 50, 50, 50));
					//Slot->SetSize(Size);

					ProductWidget->SetParams(ParamsItem);

					

					return;
				}
			}
			
		}
		HorizontBoxWidget = CreateWidget<UHorizontalBoxWidget>(GetWorld(), HorizontalWidgetObj);

		if (HorizontBoxWidget)
		{
			MainBox->AddChildToVerticalBox(HorizontBoxWidget)->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
			this->CreateElements(ParamsItem,WidgetObj);
		}

	}
}
