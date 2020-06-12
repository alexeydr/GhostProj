// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemInShop.h"
#include "CharacterStats\SmallInteractActor.h"
#include "Components\Button.h"
#include "GhostProjCharacter.h"

void UItemInShop::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if (Buy)
	{
		Buy->OnClicked.AddDynamic(this, &UItemInShop::ClickBuy);
	}
}

void UItemInShop::ClickBuy()
{
	if (MainChar->Money >= ParamItem.GetPrice())
	{
		MainChar->Money -= ParamItem.GetPrice();

		MainChar->UpdateUI();

		MainChar->UpdateInventory(ObjToAdd,EActionWithItem::Add);

		this->RemoveFromParent();
	}
}


void UItemInShop::SetParams(FInteractActorInShop Param)
{
	UBaseElementInStorage::SetParams(Param);

	this->ParamItem = Param;
	
	this->PriceText->SetText(FText::FromString(FString::SanitizeFloat(Param.GetPrice())));
	

}
