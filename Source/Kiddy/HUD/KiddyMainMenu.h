﻿// © 2023 Evstigneev Daniil. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BaseMenuWidget.h"
#include "KiddyMainMenu.generated.h"

class UButton;
class UBaseMenuWidget;
class USettingsWidget;

/**
 *  Main menu
 */
UCLASS()
class KIDDY_API UKiddyMainMenu : public UBaseMenuWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;

private:

	/** Callback functions*/
	
	UFUNCTION()
	void OpenMainMenu();

	UFUNCTION()
	void OpenSettings();

	UFUNCTION()
	void ChangeSettingsVisibility();

	UFUNCTION()
	void OpenLevel1();
	
	UFUNCTION()
	void OpenLevel2();

	/** Main menu buttons */
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	UButton* SettingsButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	UButton* Levels1Button;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	UButton* Levels2Button;

	/** Main menu widgets */

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UUserWidget* SettingsWidget;
};
