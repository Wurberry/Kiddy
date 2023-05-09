// © 2023 Evstigneev Daniil. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/DataTable.h"
#include "ChooseShadowWidget.generated.h"

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

	UFUNCTION(BlueprintNativeEvent)
	void BPSetCheckBtn(UImage* Image);

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

	UPROPERTY()
	TArray<int> ImagesDarkID;

	UPROPERTY()
	TArray<int> ImagesLightID;

	UPROPERTY()
	int ChooseDarkId;

	UPROPERTY()
	int ChooseLightId;

	UFUNCTION()
	void SetCheckBtn(int ID, bool IsDark);
};
