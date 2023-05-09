// © 2023 Evstigneev Daniil. All Rights Reserved.


#include "Kiddy/GameInstances/BaseGameInstance.h"

#include "BaseMenuWidget.h"
#include "KiddyMainMenu.h"
#include "Blueprint/UserWidget.h"
#include "Chaos/ChaosPerfTest.h"
#include "GameFramework/GameUserSettings.h"

DEFINE_LOG_CATEGORY(LogKiddy);

void UBaseGameInstance::Init()
{
    Super::Init();

	// Setup default screen settings
	if(GEngine)
	{
		UGameUserSettings* UserSettings = GEngine->GetGameUserSettings();
		if(UserSettings)
		{
			UserSettings->SetScreenResolution(UserSettings->GetDesktopResolution());
			UserSettings->SetFullscreenMode(EWindowMode::WindowedFullscreen);

			UserSettings->LoadSettings(false);

			UserSettings->ApplySettings(false);
		}
		
	}
	
}

void UBaseGameInstance::StartGame()
{
	
	if(!ensure(MenuWidget)) return;

	const UEngine* Engine = GetEngine();
	if(!ensure(Engine)) return;

	UE_LOG(LogKiddy, Log, TEXT("Starting Game"))

	UWorld* World = GetWorld();
	if(!ensure(World)) return;
	
	
}

void UBaseGameInstance::LoadGameHUD()
{
	if(!ensure(GameHUDClass)) return;

	if (!GamePlayerHUD)
	{
		// create game hud
	}

	// game hud setup

	// game hud set menu interface
	
}

void UBaseGameInstance::LoadMainMenu()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if(!ensure(PlayerController)) return;

	// Load level with menu
	
}

void UBaseGameInstance::LoadMainMenuWidget()
{
	if (!ensure(MainMenuClass)) return;

	if (!MenuWidget)
	{
		MenuWidget = CreateWidget<UKiddyMainMenu>(this, MainMenuClass);
	}
	
	if (!ensure(MenuWidget)) return;

	MenuWidget->Setup();

	// MenuWidget->SetMenuInterface(this);
	
}

