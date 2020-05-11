// Fill out your copyright notice in the Description page of Project Settings.


#include "ElementInShop.h"
#include "Components\Image.h"
#include "GhostProjCharacter.h"
#include "Kismet\GameplayStatics.h"
#include "CharacterStats\InteractActor.h"
#include "Components\Button.h"
#include "Components\TextBlock.h"

void UElementInShop::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if (Drop)
	{
		Drop->OnClicked.AddDynamic(this, &UElementInShop::ClickDropButton);
	}

	if (Use)
	{
		Use->OnClicked.AddDynamic(this, &UElementInShop::ClickUseButton);
	}

	if (Buy)
	{
		Buy->OnClicked.AddDynamic(this, &UElementInShop::ClickBuyButton);
	}

}

void UElementInShop::ClickDropButton()
{
	AInteractActor* Item = GetWorld()->SpawnActor<AInteractActor>(ElementStat.GetClass(), UGameplayStatics::GetPlayerCharacter(GetWorld(),0)->GetActorLocation() + FVector(100,0,0), FRotator::ZeroRotator);

	Item->SetItemParam(ElementStat);

	UE_LOG(LogTemp, Warning, TEXT("Name: %s"),*Item->GetName());
}

void UElementInShop::ClickBuyButton()
{
	AGhostProjCharacter* MainChar = Cast<AGhostProjCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (MainChar->Money >= ElementStat.GetPrice())
	{
		MainChar->Money -= ElementStat.GetPrice();

		MainChar->AddItemToInventory(ElementStat);
	}
}

void UElementInShop::ClickUseButton()
{
	AInteractActor::EffectItem(ElementStat, Cast<AGhostProjCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)));
}

void UElementInShop::SetParams(FItemParams Param)
{
	ItemImage->SetBrushFromTexture(Param.GetTexture());
	ItemName->SetText(FText::FromString(Param.GetName()));
	if (Price)
	{
		Price->SetText(FText::FromString(FString::FromInt(Param.GetPrice())));
	}
	ElementStat = Param;
}
