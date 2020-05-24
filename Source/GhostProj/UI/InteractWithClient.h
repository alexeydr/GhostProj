// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI\HorizontalBoxWidget.h"
#include "UI\ChatMessage.h"
#include "UI\ElementInShop.h"
#include "Work/FastfoodComp.h"
#include "InteractWithClient.generated.h"

/**
 * 
 */
UCLASS()
class GHOSTPROJ_API UInteractWithClient : public UUserWidget
{
	GENERATED_BODY()

protected:

	void SynchronizeProperties() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* DesiredFoodTextBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* CloseButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UVerticalBox* VertBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* TotalAmountTextBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* CurrentOrderTextBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UEditableTextBox* PlayerMessageTextBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UScrollBox* ChatScrollBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* ClearOrderButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* ApplyOrderButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* SendTextToChatButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* CheckBoxButton;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
		TSubclassOf<UHorizontalBoxWidget> HorizontalWidgetObj;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
		TSubclassOf<UElementInShop> MenuElem;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
		TSubclassOf<UChatMessage> ChatMessage;


	UFUNCTION()
		void ClickCloseButton();
	
	UFUNCTION()
		void ClickClearOrderButton();
	
	UFUNCTION()
		void ClickApplyOrderButton();

	UFUNCTION()
		void ClickSendMessageButton();

	UFUNCTION()
		void ClickCheckCashBox();


	int NumberOfGreetings = 0;

	void AIAnswerOnPlayerMessage(FString Message);

	bool CheckHarrasmentInChat(FString Message);

	bool CheckGreetings(FString Message);

	void CheckOrderPriceInMessage(FString Message);

	void TalkMistake(FString Message);

	void DontUnderstand();

	FString CheckMustShowDesiredOrder(FString Message);

	FString GetRandomBotAnswer(FString First, FString Second, FString Third, FString Fourth, FString Fifth);

	bool CheckDeception();

	bool CheckDifference(int Difference);

	int AmountElements = 0;

	int GetTotalAmountVal();

	void OnTrueAnswer();

	void OnFalseAnswer();

	class AClient* OwnerClient;

	int ReallyProfit = 0;

	void CreateAnswer(FString FirstAnswer, FString SecondAnswer, FString ThirdAnswer, FString FouthAnswer, FString FifthAnswer);

	void ReadyToCompleteOrder();

	void CancelCompleteOrder();

	int CounterMistakes = 0;

	void Punishment(float Percent, FString Reason);

	class AWork* CashBox;

	int AmountPrice = 0;

	bool CheckOrder();


public:

	void ChangeTextInDesiredFood(TArray<FFood> ClientDesire);

	FORCEINLINE void AddMistake(int CountMistakes = 1) {
		if (CounterMistakes + CountMistakes >= 3)
		{
			this->Punishment(10,"Too much small mistakes");
		}
		CounterMistakes++;
		
	};

	FORCEINLINE void SetOwnerClient(class AClient* Client) { OwnerClient = Client; };

	FORCEINLINE void SetCashBox(class AWork* CB) { CashBox = CB; };

	void ClickOnValInBasket(const FString Name,int Val);


	void FormMenu(UFastfoodComp* FastFoodComp);
	
};
