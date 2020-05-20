// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractWithClient.h"
#include "Components\TextBlock.h"
#include "Components\VerticalBox.h"
#include "Components\HorizontalBox.h"
#include "Components\VerticalBoxSlot.h"
#include "Components\HorizontalBoxSlot.h"
#include "Components\Button.h"
#include "Kismet\GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void UInteractWithClient::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if (CloseButton)
	{
		CloseButton->OnClicked.AddDynamic(this, &UInteractWithClient::ClickCloseButton);
	}
	
}

void UInteractWithClient::ClickCloseButton()
{
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = false;
	this->RemoveFromParent();
}

void UInteractWithClient::FormMenu(UFastfoodComp * FastFoodComp)
{
	if (VertBox && HorizontalWidgetObj)
	{
		UHorizontalBoxWidget* HorizontBoxRef = NULL;

		for (auto Elem : FastFoodComp->GetMenu())
		{
			if (!HorizontBoxRef)
			{
				HorizontBoxRef = CreateWidget<UHorizontalBoxWidget>(GetWorld(), HorizontalWidgetObj);

				if (HorizontBoxRef)
				{
					VertBox->AddChildToVerticalBox(HorizontBoxRef)->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
					
				}
			}
			else if(HorizontBoxRef->HorizonBox->GetAllChildren().Num() > 4)
			{
				HorizontBoxRef = CreateWidget<UHorizontalBoxWidget>(GetWorld(), HorizontalWidgetObj);

				if (HorizontBoxRef)
				{
					VertBox->AddChildToVerticalBox(HorizontBoxRef)->SetSize(FSlateChildSize(ESlateSizeRule::Fill));

				}
			}
			if (MenuElem)
			{
				UElementInShop* Item = CreateWidget<UElementInShop>(GetWorld(), MenuElem);
				
				FItemParams ParamItem(Elem.GetFoodName(),EStats::None, 0);
				ParamItem.AddTexture(Elem.GetFoodTexture());
				ParamItem.AddPrice(Elem.GetFoodCost());

				Item->SetParams(ParamItem);

				Item->SetOwnerWidget(this);

				if (HorizontBoxRef)
				{
					HorizontBoxRef->HorizonBox->AddChildToHorizontalBox(Item)->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
					
					
				}
			}
		}
	}
}

void UInteractWithClient::ClickOnValInBasket(const FString Name, int Val)
{
	if (TotalAmountTextBlock)
	{
		int CurrentVal = FCString::Atoi(*TotalAmountTextBlock->GetText().ToString());

		CurrentVal += Val;
		
		FString FinalString = FString::FromInt(CurrentVal) + " florians";

		this->TotalAmountTextBlock->SetText(FText::FromString(FinalString));
	}
}

void UInteractWithClient::AddElementInDesiredFood(const FString Name)
{
	if (DesiredFoodTextBlock)
	{
		DesiredFoodTextBlock->SetText(FText::FromString(Name));
	}

}

