// © 2023 Evstigneev Daniil. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BaseMenuWidget.h"
#include "KiddyMainMenu.generated.h"

class UButton;
class UBaseMenuWidget;

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

	UFUNCTION()
	void OpenLevel3();

	/** Main menu buttons */
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	UButton* SettingsButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	UButton* Levels1Button;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	UButton* Levels2Button;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	UButton* Levels3Button;

	/** Main menu widgets */

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	UWidget* SettingsMenu;
	
};
