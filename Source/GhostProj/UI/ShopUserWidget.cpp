// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopUserWidget.h"
#include "UI\UI Items In Storage\ItemInInventory.h"
#include "CharacterStats\InteractActor.h"
#include "Components\VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components\HorizontalBox.h"

#define AMOUNT_ELEMENTS 5

void UShopUserWidget::CreateElements(FItemParams ParamsItem, TSubclassOf<UBaseElementInStorage> WidgetObj, class AInteractActor* Act)
{
	if (WidgetObj && HorizontalWidgetObj)
	{
		if (HorizontBoxWidget)
		{
			if (HorizontBoxWidget->HorizonBox->GetChildrenCount() < AMOUNT_ELEMENTS)
			{
				
				if (MainBox->GetChildIndex(HorizontBoxWidget) >= 0)
				{
					UBaseElementInStorage* ProductWidget = CreateWidget<UBaseElementInStorage>(GetWorld(), WidgetObj);
					if (ProductWidget)
					{

						UHorizontalBoxSlot* Slot = HorizontBoxWidget->HorizonBox->AddChildToHorizontalBox(ProductWidget);


						FSlateChildSize Size;

						Size.SizeRule = ESlateSizeRule::Automatic;

						Slot->SetPadding(FMargin(30, 30, 30, 30));
						Slot->SetSize(Size);

						ProductWidget->SetParams(ParamsItem);
						

						if (Cast<UItemInInventory>(ProductWidget))
						{
							Cast<UItemInInventory>(ProductWidget)->ActForInteract = Act;
						}
						

						return;
					}
				}
			}
			
		}
		HorizontBoxWidget = CreateWidget<UHorizontalBoxWidget>(GetWorld(), HorizontalWidgetObj);

		if (HorizontBoxWidget)
		{
			
			MainBox->AddChildToVerticalBox(HorizontBoxWidget)->SetSize(FSlateChildSize(ESlateSizeRule::Automatic));
			this->CreateElements(ParamsItem,WidgetObj,Act);
		}

	}
}


void UShopUserWidget::RemoveAllElements()
{
	MainBox->ClearChildren();
	
}
