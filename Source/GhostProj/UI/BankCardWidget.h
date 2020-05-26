// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BankCardWidget.generated.h"

/**
 * 
 */
UCLASS()
class GHOSTPROJ_API UBankCardWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* CurrentBalance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* CurrentBalanceInBankAccount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* OperationStatus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* AddAmountInBankAccount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* SubstractAmountInBankAccount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class USpinBox* SumSpinBox;

	class AGhostProjCharacter* MainChar;

	void SynchronizeProperties() override;

	void SetParam();

	UFUNCTION()
		void ClickAdd();

	UFUNCTION()
		void ClickSubstract();

	

};
