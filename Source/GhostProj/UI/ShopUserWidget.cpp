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
				
				if (MainBox->GetChildIndex(HorizontBoxWidget) >= 0)
				{
					UElementInShop* ProductWidget = CreateWidget<UElementInShop>(GetWorld(), WidgetObj);
					if (ProductWidget)
					{
						//UE_LOG(LogTemp, Warning, TEXT("name it: %s"),*ParamsItem.GetName());
						//ProductWidget->SetOwnerWidget(this);

						UHorizontalBoxSlot* Slot = HorizontBoxWidget->HorizonBox->AddChildToHorizontalBox(ProductWidget);

						//UE_LOG(LogTemp, Warning, TEXT("name it: %s"), *Slot->GetName());

						FSlateChildSize Size;

						Size.SizeRule = ESlateSizeRule::Automatic;

						Slot->SetPadding(FMargin(30, 30, 30, 30));
						Slot->SetSize(Size);

						ProductWidget->SetParams(ParamsItem);



						return;
					}
				}
			}
			
		}
		HorizontBoxWidget = CreateWidget<UHorizontalBoxWidget>(GetWorld(), HorizontalWidgetObj);

		if (HorizontBoxWidget)
		{
			
			MainBox->AddChildToVerticalBox(HorizontBoxWidget)->SetSize(FSlateChildSize(ESlateSizeRule::Automatic));
			this->CreateElements(ParamsItem,WidgetObj);
		}

	}
}

void UShopUserWidget::RemoveAllElements()
{
	MainBox->ClearChildren();
	

}
