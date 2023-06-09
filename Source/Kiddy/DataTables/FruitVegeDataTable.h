﻿// © 2023 Evstigneev Daniil. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "FruitVegeDataTable.generated.h"

USTRUCT(BlueprintType)
struct FFruitVege : public FTableRowBase
{
	GENERATED_BODY()
	
	FFruitVege(): ID(1), IsDark(false), Light(nullptr), Dark(nullptr)
	{
	}

	FFruitVege(int ID, bool IsDark, UTexture2D* Light, UTexture2D* Dark)
	{
		this->ID = ID;
		this->IsDark = IsDark;
		this->Light = Light;
		this->Dark = Dark;
	}

	UPROPERTY(EditAnywhere)
	int ID;

	UPROPERTY()
	bool IsDark;
	
	UPROPERTY(EditAnywhere)
	UTexture2D* Light;

	UPROPERTY(EditAnywhere)
	UTexture2D* Dark;
};

UCLASS()
class KIDDY_API AFruitVegeDataTable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFruitVegeDataTable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UDataTable* FruitVegeDataTable;

	FFruitVege* SFruitVegeData;
	
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
