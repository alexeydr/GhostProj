// Fill out your copyright notice in the Description page of Project Settings.


#include "BankCardComp.h"
#include "Kismet\GameplayStatics.h"
#include "GhostProjCharacter.h"

// Sets default values for this component's properties
UBankCardComp::UBankCardComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBankCardComp::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UBankCardComp::UpdateBankAccount()
{
	AGhostProjCharacter* Char = Cast<AGhostProjCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Char)
	{
		int Diff = BankAccount.GetDifferenceDate(Char->HeroTime->GetTime().Days);
		for (int i = 0; i < Diff; i++)
		{
			float Sum = BankAccount.GetAmount() * BankAccount.GetRate();
			BankAccount.AddAmount(Sum);
			BankAccount.SetNewDate(Char->HeroTime->GetTime().Days);
		}

	}
}

void UBankCardComp::AddMoneyToBankAccount(float Money)
{
	if (Money > this->MoneyOnCard)
	{
		BankAccount.AddAmount(this->MoneyOnCard);
	}
	else
	{
		BankAccount.AddAmount(Money);
	}
	this->SubstractMoneyOnCard(Money);
}

void UBankCardComp::SubstractMoneyFromBankAccount(float Money)
{
	if (Money > BankAccount.GetAmount())
	{
		this->MoneyOnCard += BankAccount.GetAmount();
	}
	else
	{
		this->MoneyOnCard += Money;
	}
	BankAccount.SubstractAmount(Money);
}


// Called every frame
void UBankCardComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

