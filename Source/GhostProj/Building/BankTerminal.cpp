// Fill out your copyright notice in the Description page of Project Settings.


#include "BankTerminal.h"

void ABankTerminal::ActionOnInteract()
{
	Super::ActionOnInteract();

	MainChar->Money += MainChar->GetBankCard()->GetMoneyOnCard();

}