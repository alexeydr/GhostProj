// Fill out your copyright notice in the Description page of Project Settings.


#include "BankCardWidget.h"
#include "Engine/World.h"
#include "Kismet\GameplayStatics.h"
#include "GhostProjCharacter.h"
#include "Components\TextBlock.h"
#include "Components\SpinBox.h"
#include "Components\Button.h"

void UBankCardWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	MainChar = Cast<AGhostProjCharacter>(UGameplayStatics::GetPlayerCharacter(this->GetWorld(),0));

	if (MainChar && CurrentBalance && CurrentBalanceInBankAccount && OperationStatus && AddAmountInBankAccount && SubstractAmountInBankAccount && SumSpinBox)
	{
		AddAmountInBankAccount->OnClicked.AddDynamic(this, &UBankCardWidget::ClickAdd);
		SubstractAmountInBankAccount->OnClicked.AddDynamic(this, &UBankCardWidget::ClickSubstract);
		
		this->SetParam();
	}

}

void UBankCardWidget::SetParam()
{
	MainChar->GetBankCard()->UpdateBankAccount();
	CurrentBalance->SetText(FText::FromString(FString::FromInt((int)MainChar->GetBankCard()->GetMoneyOnCard())));
	CurrentBalanceInBankAccount->SetText(FText::FromString(FString::FromInt((int)MainChar->GetBankCard()->GetBankAccount().GetAmount())));
}

void UBankCardWidget::ClickAdd()
{
	float Str = SumSpinBox->GetValue();
	
	if (Str > 0)
	{
		MainChar->GetBankCard()->AddMoneyToBankAccount(Str);
	}

	this->SetParam();
}

void UBankCardWidget::ClickSubstract()
{
	float Str = SumSpinBox->GetValue();

	if (Str > 0)
	{
		MainChar->GetBankCard()->SubstractMoneyFromBankAccount(Str);
	}

	this->SetParam();

}
