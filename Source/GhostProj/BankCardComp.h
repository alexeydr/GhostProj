// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BankCardComp.generated.h"

USTRUCT(BlueprintType)
struct FBankAccount
{
	GENERATED_USTRUCT_BODY()

private:
	UPROPERTY(EditAnywhere)
		float Amount;
	UPROPERTY(EditAnywhere)
		float Rate;
	UPROPERTY(EditAnywhere)
		int Date;

public:

	FORCEINLINE void AddAmount(float AddSum) { this->Amount += AddSum; };

	FORCEINLINE void SubstractAmount(float SubAm) {
		this->Amount -= SubAm;
		if (this->Amount < 0)
			this->Amount = 0;
	};

	FORCEINLINE float GetAmount() { return Amount; };

	FORCEINLINE float GetRate() { return Rate; };

	FORCEINLINE	 int GetDate() { return Date; };

	FORCEINLINE	 void SetNewDate(int NewDate) { Date = NewDate; };

	FORCEINLINE	 int GetDifferenceDate(int IncomingDate) { return IncomingDate - Date; };


	FBankAccount(float A, float R, int D)
	{
		Amount = A;
		Rate = R;
		Date = D;
	}


	FBankAccount()
	{

	}


};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GHOSTPROJ_API UBankCardComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBankCardComp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	float MoneyOnCard = 0;

	UPROPERTY()
		FBankAccount BankAccount = FBankAccount(200.f,0.03f,0);

public:

	void UpdateBankAccount();

	void AddMoneyToBankAccount(float Money);

	void SubstractMoneyFromBankAccount(float Money);

	FORCEINLINE float GetMoneyOnCard() { return MoneyOnCard; };

	FORCEINLINE void AddMoneyOnCard(float AddSum) { MoneyOnCard += AddSum; };

	FORCEINLINE void SubstractMoneyOnCard(float SubAmount) { 
		if (MoneyOnCard > SubAmount)
			MoneyOnCard -= SubAmount;
		else
			MoneyOnCard = 0;
	};

	UFUNCTION(BlueprintCallable)
		FBankAccount GetBankAccount() { return BankAccount; };

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
