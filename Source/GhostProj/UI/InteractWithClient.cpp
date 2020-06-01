// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractWithClient.h"
#include "Components\TextBlock.h"
#include "Components\VerticalBox.h"
#include "Components\HorizontalBox.h"
#include "Components/ScrollBox.h"
#include "Components/EditableTextBox.h"
#include "Components\VerticalBoxSlot.h"
#include "Components\HorizontalBoxSlot.h"
#include "Components\Button.h"
#include "Work\Client.h"
#include "Work\Work.h"
#include "GhostProjCharacter.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "Kismet\GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void UInteractWithClient::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if (CloseButton)
	{
		CloseButton->OnClicked.AddDynamic(this, &UInteractWithClient::ClickCloseButton);
	}

	if (CheckBoxButton)
	{
		CheckBoxButton->OnClicked.AddDynamic(this, &UInteractWithClient::ClickCheckCashBox);
	}

	if (ClearOrderButton)
	{
		ClearOrderButton->OnClicked.AddDynamic(this, &UInteractWithClient::ClickClearOrderButton);
	}
	
	if (ApplyOrderButton)
	{
		ApplyOrderButton->OnClicked.AddDynamic(this, &UInteractWithClient::ClickApplyOrderButton);
	}

	if (SendTextToChatButton)
	{
		SendTextToChatButton->OnClicked.AddDynamic(this, &UInteractWithClient::ClickSendMessageButton);
	}

	if (DesiredFoodTextBlock)
	{
		DesiredFoodTextBlock->SetRenderOpacity(0);
		DesiredFoodTextBlock->SetOpacity(0);
	}
	
	if (ChatMessage && PlayerMessageTextBlock && ChatScrollBox)
	{
		UChatMessage* ChatMessageRef = CreateWidget<UChatMessage>(GetWorld(), ChatMessage);
		ChatMessageRef->SetMessage("Please communicate politely, customers are also living people with feelings!");
		ChatScrollBox->AddChild(ChatMessageRef);
	}

	this->CancelCompleteOrder();

}

void UInteractWithClient::ClickCloseButton()
{
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = false;
	this->RemoveFromParent();
}

void UInteractWithClient::ClickClearOrderButton()
{
	AmountElements = 0;

	if (CurrentOrderTextBlock)
	{
		CurrentOrderTextBlock->SetText(FText());

	}
	if (TotalAmountTextBlock)
	{
		TotalAmountTextBlock->SetText(FText::FromString("0 florians"));
	}

}

void UInteractWithClient::ClickApplyOrderButton()
{
	if (this->CheckOrder())
	{
		if (AmountPrice > OwnerClient->GetReallyPrice())
		{
			Cast<AGhostProjCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->Money += AmountPrice - OwnerClient->GetReallyPrice();
			Cast<AGhostProjCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->UpdateUI();
		}

		CashBox->AddMoney(OwnerClient->GetReallyPrice());
	}
	else
	{
		this->Punishment(20,"Mistake in order");
	}
	OwnerClient->CompleteOrder(true);

	UE_LOG(LogTemp, Warning, TEXT("Current cash: %s"), *FString::SanitizeFloat(CashBox->GetMoney()));

	UE_LOG(LogTemp, Warning, TEXT("Current cash in char: %s"), *FString::SanitizeFloat(Cast<AGhostProjCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->Money));


	this->RemoveFromParent();


}

void UInteractWithClient::ClickSendMessageButton()
{
	if (ChatMessage && PlayerMessageTextBlock)
	{
		if (PlayerMessageTextBlock->GetText().ToString().Len() > 0)
		{
			UChatMessage* ChatMessageRef = CreateWidget<UChatMessage>(GetWorld(), ChatMessage);

			if (ChatMessageRef)
			{
				ChatMessageRef->SetReplic("Hero",PlayerMessageTextBlock->GetText().ToString());

				if (ChatScrollBox)
				{
					ChatScrollBox->AddChild(ChatMessageRef);
					this->AIAnswerOnPlayerMessage(PlayerMessageTextBlock->GetText().ToString());
					PlayerMessageTextBlock->SetText(FText());

				}

			}
		}

	}

}

void UInteractWithClient::ClickCheckCashBox()
{
	if (ChatMessage && CashBox)
	{
		UChatMessage* ChatMessageRef = CreateWidget<UChatMessage>(GetWorld(), ChatMessage);
		FString Message = FString("Cash box balance: " + FString::FromInt((int)CashBox->GetMoney())+ " money");
		ChatMessageRef->SetMessage(Message);
		ChatScrollBox->AddChild(ChatMessageRef);
	}

}

void UInteractWithClient::AIAnswerOnPlayerMessage(FString Message)
{
	if (this->CheckHarrasmentInChat(Message))
	{	
		UChatMessage* ChatMessageRef = CreateWidget<UChatMessage>(GetWorld(), ChatMessage);
		FString Answer = this->GetRandomBotAnswer("...","...","...","...","...");
		ChatMessageRef->SetReplic("Client", Answer);
		ChatScrollBox->AddChild(ChatMessageRef);
		return;
	}
	if (this->CheckGreetings(Message))
	{
		UChatMessage* ChatMessageRef = CreateWidget<UChatMessage>(GetWorld(), ChatMessage);
		if (NumberOfGreetings > 1)
		{
			FString Answer = this->GetRandomBotAnswer("...", "We already greeted", "Hi...", "Hello...", "Wazzap MAAAAANN!!!");
			ChatMessageRef->SetReplic("Client", Answer);
		}
		else
		{
			FString Answer = this->GetRandomBotAnswer("Hello", "Hello", "Hello", "Hi", "Hi");
			ChatMessageRef->SetReplic("Client", Answer);
			ChatScrollBox->AddChild(ChatMessageRef);
		}

	}
	if (this->CheckMustShowDesiredOrder(Message) != "false" && DesiredFoodTextBlock->GetRenderOpacity() == 0)
	{
		UChatMessage* ChatMessageRef = CreateWidget<UChatMessage>(GetWorld(), ChatMessage);
		ChatMessageRef->SetReplic("Client", this->CheckMustShowDesiredOrder(Message));
		ChatScrollBox->AddChild(ChatMessageRef);
		if (this->CheckMustShowDesiredOrder(Message).Contains("OK"))
		{
			UChatMessage* ChatMessageRef = CreateWidget<UChatMessage>(GetWorld(), ChatMessage);
			ChatMessageRef->SetMessage("Sales order available");
			ChatScrollBox->AddChild(ChatMessageRef);
			DesiredFoodTextBlock->SetRenderOpacity(1);
			this->DesiredFoodTextBlock->SetOpacity(1);
		}
	}

	this->CheckOrderPriceInMessage(Message);

	this->TalkMistake(Message);

}

bool UInteractWithClient::CheckHarrasmentInChat(FString Message)
{
	Message.ToLower();

	if (Message.Contains("fuck") || Message.Contains("shit") || Message.Contains("whore") || Message.Contains("retard") || Message.Contains("idiot") || Message.Contains("bitch"))
	{
		return true;
	}

	return false;
}

bool UInteractWithClient::CheckGreetings(FString Message)
{
	Message.ToLower();

	if (Message.Contains("hello") || Message.Contains("hi") || Message.Contains("greeting"))
	{
		NumberOfGreetings++;
		return true;
	}

	return false;
}

void UInteractWithClient::CheckOrderPriceInMessage(FString Message)
{
	Message.ToLower();
	

	int MidSymbol = 0;

	for (auto Ch: Message)
	{

		if (FCString::Atoi(&Ch) != 0)
		{
			break;
		}
		MidSymbol++;
	}

	AmountPrice = FCString::Atoi(*Message.Mid(MidSymbol));

	if (Message.Contains("Price") && AmountPrice > 0 && OwnerClient)
	{
		if (this->CheckDeception())
		{
			this->OnTrueAnswer();

		}
		else
		{
			if (this->CheckDifference(OwnerClient->GetReallyPrice() - AmountPrice))
			{
				this->OnTrueAnswer();
			}
			else
			{
				this->OnFalseAnswer();
			}
		}
	}
	
}

void UInteractWithClient::TalkMistake(FString Message)
{
	Message.ToLower();
	if (Message.Contains("sorry") && Message.Contains("mistake"))
	{
		this->CancelCompleteOrder();
		this->AddMistake();
	}
}

void UInteractWithClient::DontUnderstand()
{
	this->CreateAnswer("I dont understand", "I dont understand", "I dont understand", "I dont understand", "I dont understand");
}

FString UInteractWithClient::CheckMustShowDesiredOrder(FString Message)
{
	Message.ToLower();

	if (Message.Contains("please") && Message.Contains("order"))
	{
		return FString("OK, thanks");
	}


	if ((Message.Contains("your") || Message.Contains("yours")) && Message.Contains("order"))
	{
		return FString("OK");
	}

	if (Message.Contains("order"))
	{
		return FString("More respect, please");
	}


	return FString("false");
}

FString UInteractWithClient::GetRandomBotAnswer(FString First, FString Second, FString Third, FString Fourth, FString Fifth)
{
	switch (FMath::RandRange(1, 5))
	{
	case 1:
		return First;
		break;
	case 2:
		return Second;
		break;
	case 3:
		return Third;
		break;
	case 4:
		return Fourth;
		break;
	case 5:
		return Fifth;
		break;

	}
	return FString("Error");
}

bool UInteractWithClient::CheckDeception()
{
	int Diff = OwnerClient->GetReallyPrice() - AmountPrice;

	if (Diff >= 0 && Diff < 50)
	{
		return true;
	}
	return false;

}

bool UInteractWithClient::CheckDifference(int Difference)
{
	if (Difference > 0)
	{
		this->CreateAnswer("The amount is too big, you were mistaken", "The amount is too big, you were mistaken", "The amount is too big, you were mistaken", "The amount is too big, you were mistaken", "The amount is too big, you were mistaken");
		return true;
	}
	else
	{
		if (FMath::RandRange(1, 100) < FGenericPlatformMath::Pow(3,(Difference *-1)))
		{
			return false;
		}
		else
		{
			return true;
		}
		
	}

}

void UInteractWithClient::OnTrueAnswer()
{
	if (AmountPrice > OwnerClient->GetClientMoney() && CashBox)
	{
		this->CreateAnswer("Sorry, I want to change the order", "Sorry, I want to change the order", "Sorry, I want to change the order", "Sorry, I want to change the order", "Sorry, I want to change the order");
		
		OwnerClient->SetFoodPreferences();
		UChatMessage* ChatMessageRef = CreateWidget<UChatMessage>(GetWorld(), ChatMessage);

		ChatMessageRef->SetMessage("Client changed order");
		ChatScrollBox->AddChild(ChatMessageRef);

	}
	else
	{
		this->ReadyToCompleteOrder();
		this->CreateAnswer("Thanks, wait my check", "Thanks, wait my check", "Thanks, wait my check", "Thanks, wait my check", "Thanks, wait my check");
	}
}

void UInteractWithClient::OnFalseAnswer()
{
	this->Punishment(30,"Lie to customer");
	OwnerClient->CompleteOrder(false);
	this->RemoveFromParent();

}

int UInteractWithClient::GetTotalAmountVal()
{
	if (TotalAmountTextBlock)
	{
		return FCString::Atoi(*TotalAmountTextBlock->GetText().ToString());
	}

	return -1;
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
				UItemInWork* Item = CreateWidget<UItemInWork>(GetWorld(), MenuElem);

				Item->SetOwnerWidget(this);
				
				Item->SetParams(Elem);


				if (HorizontBoxRef)
				{
					HorizontBoxRef->HorizonBox->AddChildToHorizontalBox(Item)->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
					
					
				}
			}
		}
	}
}

void UInteractWithClient::CreateAnswer(FString FirstAnswer, FString SecondAnswer, FString ThirdAnswer, FString FouthAnswer, FString FifthAnswer)
{
	UChatMessage* ChatMessageRef = CreateWidget<UChatMessage>(GetWorld(), ChatMessage);
	FString Answer = this->GetRandomBotAnswer(FirstAnswer, SecondAnswer, ThirdAnswer, FouthAnswer, FifthAnswer);
	ChatMessageRef->SetReplic("Client", Answer);
	ChatScrollBox->AddChild(ChatMessageRef);
}

void UInteractWithClient::ReadyToCompleteOrder()
{
	if (ApplyOrderButton && ClearOrderButton)
	{
		ClearOrderButton->SetVisibility(ESlateVisibility::Hidden);
		ApplyOrderButton->SetVisibility(ESlateVisibility::Visible);
	}
}

void UInteractWithClient::CancelCompleteOrder()
{
	if (ApplyOrderButton && ClearOrderButton)
	{
		ApplyOrderButton->SetVisibility(ESlateVisibility::Hidden);
		ClearOrderButton->SetVisibility(ESlateVisibility::Visible);
	}
}

void UInteractWithClient::Punishment(float Percent, FString Reason)
{
	if (CashBox)
	{
		float Val = CashBox->GetMoney() * (Percent / 100);

		CashBox->CreateInfoWidget(FString(Reason+" "+FString::SanitizeFloat(Percent)+"%"));
		CashBox->SubstractMoney(Val);

	}
}

bool UInteractWithClient::CheckOrder()
{
	for (FItemInWorkStruct Elem: OwnerClient->GetDesiredFood())
	{
		if (!this->CurrentOrderTextBlock->GetText().ToString().Contains(Elem.GetName()))
		{
			return false;
		}
	}
	return true;
}

void UInteractWithClient::ChangeTextInDesiredFood(TArray<FItemInWorkStruct> ClientDesire)
{
	if (this->DesiredFoodTextBlock)
	{
		FString Name;
		for (FItemInWorkStruct Elem : ClientDesire)
		{
			Name += " " + Elem.GetName();
		}
		this->DesiredFoodTextBlock->SetText(FText::FromString(Name));

	}
}

void UInteractWithClient::ClickOnValInBasket(const FString Name, int Val)
{
	if (AmountElements < 8)
	{
		AmountElements++;

		int CurrentVal = this->GetTotalAmountVal();

		if (CurrentVal >= 0)
		{
			CurrentVal += Val;

			FString FinalString = FString::FromInt(CurrentVal) + " florians";

			this->TotalAmountTextBlock->SetText(FText::FromString(FinalString));
		}

		if (CurrentOrderTextBlock)
		{
			FString FinalRow = CurrentOrderTextBlock->GetText().ToString() + " " + Name;

			CurrentOrderTextBlock->SetText(FText::FromString(FinalRow));
		}
	}
}
