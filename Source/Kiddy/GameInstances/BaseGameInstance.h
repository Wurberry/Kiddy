// © 2023 Evstigneev Daniil. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "KiddyMenuInterface.h"
#include "Engine/GameInstance.h"
#include "BaseGameInstance.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnListItemFruitVegeClick, int, ID, bool, IsDark, UObject*, Object);
DECLARE_LOG_CATEGORY_EXTERN(LogKiddy, Log, All);

class UAttentionWidget;
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
	// Settings system

	UFUNCTION()
	void SetDarkMode(bool IsNeeded);

	UFUNCTION()
	void SetEyeProtect(bool IsChecked);

	UFUNCTION()
	void ShowAttention(FString NewText);
	
	/////////////////
	// Blueprint references, to be set in editor on defaults

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI class set")
	TSubclassOf<UBaseMenuWidget> MainMenuClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI class set")
	TSubclassOf<UUserWidget> GameHUDClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI class set")
	TSubclassOf<UAttentionWidget> AttentionClass;
	
	/////////////////
	// UI Getters

	AGamePlayerHUD* GetGameHUD() const { return GamePlayerHUD; }

	/////////////////
	// Delegates

	FOnListItemFruitVegeClick OnListItemFruitVegeClick;

	
	/////////////////
	// Getters

	bool GetIsEyeProtect() {return this->IsEyeProtectActive;}

	bool GetIsDarkMode() {return this->IsDarkModeActive;}
	
protected:

	/////////////////
	// UI Pointer

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI settings")
	UKiddyMainMenu* MenuWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI settings")
	AGamePlayerHUD* GamePlayerHUD;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI settings")
	UAttentionWidget* AttentionWidget;
	
private:
	
	/////////////////
	// Settings system

	UFUNCTION()
	void BlockEyeProtect();
	
	UFUNCTION()
	void ClearEyeProtect();

	UFUNCTION()
	void BlockDarkMode();

	UFUNCTION()
	void ClearDarkModeProtect();
	
	FTimerHandle TimerOnEyeProtect;
	
	FTimerHandle TimerDarkMode;

	bool IsEyeProtectActive = false;

	int EyeProtectRateDuration = 5;

	bool IsDarkModeActive = false;
	
};
