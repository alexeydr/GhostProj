// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "ItemStruct.generated.h"

/**
 * 
 */
/*
UENUM()
enum class EStats : uint8
{
	None 	UMETA(DisplayName = "None"),
	Sleepiness 	UMETA(DisplayName = "Sleepiness"),
	Hunger	UMETA(DisplayName = "Hunger"),
	Thirst	UMETA(DisplayName = "Thirst")
};*/


USTRUCT()
struct FItemParams : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

protected:

	UPROPERTY(EditAnywhere)
		FString Name;
	//UPROPERTY(EditAnywhere)
		//EStats TypeActor;
	//UPROPERTY(EditAnywhere)
		//int Value;
	UPROPERTY(EditAnywhere)
		class UTexture2D* Texture;
	//UPROPERTY(EditAnywhere)
		//UClass* ItemClass;
	//UPROPERTY(EditAnywhere)
		//class UStaticMesh* Mesh;
//	UPROPERTY(EditAnywhere)
	//	int Price;
	//UPROPERTY(EditAnywhere)
		//bool NeedDestroy;
public:
	
	FItemParams(FString NewName = "", class UTexture2D* Texture = nullptr)
	{
		this->Name = NewName;
		this->Texture = Texture;

	}


	/*void AddClass(UClass* Cl)
	{
		this->ItemClass = Cl;
	}

	void AddMesh(class UStaticMesh* M)
	{
		this->Mesh = M;
	}*/

	void AddTexture(class UTexture2D* Texture2D)
	{
		this->Texture = Texture2D;
	}


	void AddName(FString N)
	{
		this->Name = N;
	}


	/*void AddDestroySettings(bool N)
	{
		this->NeedDestroy = N;
	}*/


	/*void AddType(EStats TA)
	{
		this->TypeActor = TA;
	}

	void AddValue(int V)
	{
		this->Value = V;
	}*/


	/*void AddPrice(int Pr)
	{
		this->Price = Pr;
	}*/


	/*EStats GetType()
	{
		return this->TypeActor;
	}

	int GetValue()
	{
		return this->Value;
	}


	int GetPrice()
	{
		return this->Price;
	}

	bool GetNeedDestroy()
	{
		return this->NeedDestroy;
	}*/

	FString GetName()
	{
		return this->Name;
	}

	class UTexture2D* GetTexture()
	{
		return this->Texture;
	}

	/*UClass* GetClass()
	{
		return this->ItemClass;
	}

	class UStaticMesh* GetMesh()
	{
		return this->Mesh;
	}*/

	bool operator ==(FItemParams Param)
	{
		if (this->GetName() == Param.GetName() && 
			this->GetTexture() == Param.GetTexture())
		{
			return true;
		}
		return false;
	}

};
