// © 2023 Evstigneev Daniil. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BaseHUDWidget.h"
#include "SettingsWidget.generated.h"


class UComboBoxString;
class UCheckBox;

/**
 * 
 */
UCLASS()
class KIDDY_API USettingsWidget : public UBaseHUDWidget
{
	GENERATED_BODY()

public:
	
	UFUNCTION()
	void SetDarkModeInstance(bool IsChecked);

	UFUNCTION()
	void SetEyeProtectInstance(bool IsChecked);
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UCheckBox* ChBEyeProtect;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UCheckBox* ChBDarkMode;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UComboBoxString* CBColorBlinding;

protected:
	
	UFUNCTION()
	virtual void NativeConstruct() override;


};
