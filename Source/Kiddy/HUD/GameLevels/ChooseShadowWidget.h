﻿// © 2023 Evstigneev Daniil. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/DataTable.h"
#include "ChooseShadowWidget.generated.h"

class UButton;
class UFruitVegeListEntry;
class UImage;
class UListView;
class UBaseGameInstance;

struct FFruitVege;

class UHorizontalBox;

/**
 * 
 */
UCLASS()
class KIDDY_API UChooseShadowWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void CreateGamePhase();
	
protected:
	virtual bool Initialize() override;

private:
	
	UPROPERTY()
	UBaseGameInstance* GameInstance;
	
	UPROPERTY(EditAnywhere)
	UDataTable* DTFruitVege;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UFruitVegeListEntry> FruitVegeEntry;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (
		BindWidget,
		AllowPrivateAccess = true))
	UListView* ListViewDark;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (
		BindWidget,
		AllowPrivateAccess = true))
	UListView* ListViewLight;

	UPROPERTY(meta = (BindWidget))
	UButton* BtnExit;
	
	UPROPERTY()
	TArray<int> ImagesDarkID;

	UPROPERTY()
	TArray<int> ImagesLightID;

	UPROPERTY()
	int ChooseDarkId = 0;

	UPROPERTY()
	UFruitVegeListEntry* ListEntryDark;
	
	UPROPERTY()
	int ChooseLightId = 0;

	UPROPERTY()
	UFruitVegeListEntry* ListEntryLight;
	
	UPROPERTY(EditDefaultsOnly)
	int CountElementsView = 7;

	UFUNCTION()
	void SetCheckBtn(int ID, bool IsDark, UObject* Object);

	UFUNCTION()
	void GoToMenu();

	template<typename Type>
	static void ShuffleArray(FRandomStream& Stream, TArray<Type>& Array) {
		const int32 LastIndex = Array.Num() - 1;
 
		for (int32 i = 0; i <= LastIndex; i += 1) {
			const int32 Index = Stream.RandRange(i, LastIndex);
			if (i == Index) {
				continue;
			}
 
			Array.Swap(i, Index);
		}
	}
	
	UFUNCTION()
	void GenerateBtnsFruitVege(bool IsDark, TArray<FName> RowNames);

	UFUNCTION()
	void RemoveBtnsFruitVege(TArray<int> &Images, UListView* ListView, int ID);

	UFUNCTION()
	void ClearListBtnPairActive();
	
};
