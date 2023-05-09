// © 2023 Evstigneev Daniil. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "KiddyMenuInterface.h"
#include "Engine/GameInstance.h"
#include "BaseGameInstance.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnListItemFruitVegeClick, int, ID, bool, IsDark);
DECLARE_LOG_CATEGORY_EXTERN(LogKiddy, Log, All);

class UImage;
class UKiddyMainMenu;
class AGamePlayerHUD;
class UBaseMenuWidget;
class USettingsWidget;
class UKiddyMenuWidget;

/**
 *  Kiddy Game Instance
 */
UCLASS()
class KIDDY_API UBaseGameInstance : public UGameInstance, public IKiddyMenuInterface
{
	GENERATED_BODY()

public:

	virtual void Init() override;

	// Menu interface implementation
	
	virtual void StartGame() override;
	virtual void LoadGameHUD() override;
	virtual void LoadMainMenu() override;

	/////////////////
	// UI Creation

	UFUNCTION(BlueprintCallable, Category = "KiddyGameInstance|UI")
	void LoadMainMenuWidget();
	
	/////////////////
	// Blueprint references, to be set in editor on defaults

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI class set")
	TSubclassOf<UBaseMenuWidget> MainMenuClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI class set")
	TSubclassOf<UUserWidget> GameHUDClass;
	
	
	/////////////////
	// UI Getters

	AGamePlayerHUD* GetGameHUD() const { return GamePlayerHUD; }

	/////////////////
	// Delegates

	FOnListItemFruitVegeClick OnListItemFruitVegeClick;
	
protected:

	/////////////////
	// UI Pointer

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI settings")
	UKiddyMainMenu* MenuWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI settings")
	AGamePlayerHUD* GamePlayerHUD;
	
};
