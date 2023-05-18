// © 2023 Evstigneev Daniil. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Kiddy/DataTables/FruitVegeDataTable.h"
#include "FindPairListEntry.generated.h"

struct FFruitVege;
class UBaseGameInstance;
class UButton;
class UImage;
class AFruitVegeDataTable;

/**
 * 
 */
UCLASS()
class KIDDY_API UFindPairListEntry : public UUserWidget, public IUserObjectListEntry
{

public:
	
	UPROPERTY(meta=(BindWidget))
	UImage* IconImage;

	UPROPERTY()
	int ID;

	UPROPERTY()
	bool IsDark;
	
	UPROPERTY()
	UTexture2D* Light;

	UPROPERTY()
	UTexture2D* Dark;

	UFUNCTION()
	void Init(FFruitVege FruitVege);

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* OpenImg;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* CloseImg;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UButton* BtnImage;
	
protected:
	
	GENERATED_BODY()
	virtual void NativeOnInitialized() override;
	
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

private:

	UFUNCTION()
	void SendItemEntry();
	
	UPROPERTY()
	UBaseGameInstance* GameInstance;
	
};
