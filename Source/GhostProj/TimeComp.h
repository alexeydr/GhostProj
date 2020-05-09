// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TimeComp.generated.h"


USTRUCT(BlueprintType)
struct FMyDateTime
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
		int32 Days;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 Hours;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 Minutes;

	FMyDateTime(int32 D = 0, int32 H = 0, int32 M = 0)
	{
		Days = D;
		Hours = H;
		Minutes = M;
	}

	bool operator>(FMyDateTime FirstDate)
	{
		if (this->Hours > FirstDate.Hours)
		{
			return true;
		}
		if (this->Hours == FirstDate.Hours)
		{
			if (this->Minutes > FirstDate.Minutes)
			{
				return true;
			}

		}
		return false;
	}

	bool operator<(FMyDateTime FirstDate)
	{
		if (this->Hours < FirstDate.Hours)
		{
			return true;
		}
		if (this->Hours == FirstDate.Hours)
		{
			if (this->Minutes < FirstDate.Minutes)
			{
				return true;
			}

		}
		return false;
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GHOSTPROJ_API UTimeComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTimeComp();

	int32 Modifier = 10;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	FMyDateTime CurrentTime = FMyDateTime(1,0,0);

	void TimeFlow();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//«адает новое игровое врем€
	inline void SetTime(FMyDateTime Time) {
		CurrentTime = Time;
	};
	
	//¬озвращает текущее игровое врем€
	inline FMyDateTime GetTime() {
		return CurrentTime;
	};

	//ƒобавл€ет значение к текущему времени и возвращает новое значение
	FMyDateTime AddTime(int32 Days = 0, int32 Hours = 0, int32 Minutes = 0);
	

};
