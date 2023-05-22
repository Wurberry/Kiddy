// © 2023 Evstigneev Daniil. All Rights Reserved.


#include "Kiddy/GameInstances/BaseGameInstance.h"

#include "BaseMenuWidget.h"
#include "KiddyMainMenu.h"
#include "Attention/AttentionWidget.h"
#include "Blueprint/UserWidget.h"
#include "Chaos/ChaosPerfTest.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

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

	UGameplayStatics::OpenLevel(GetWorld(), "BaseMenu");
	
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

void UBaseGameInstance::SetDarkMode(bool IsNeeded)
{
	if(IsNeeded)
	{
		FDateTime CurDateTime = UKismetMathLibrary::Now();
		if(CurDateTime >= FDateTime(CurDateTime.GetYear(),CurDateTime.GetMonth(), CurDateTime.GetDay(),10)
			|| CurDateTime <= FDateTime(CurDateTime.GetYear(),CurDateTime.GetMonth(), CurDateTime.GetDay()+1,7))
		{
			GetWorld()->GetTimerManager().SetTimer(TimerDarkMode,this,
				&UBaseGameInstance::BlockDarkMode, EyeProtectRateDuration, false);
		}	
	}
	else
	{
		ClearDarkModeProtect();
		GetWorld()->GetTimerManager().ClearTimer(TimerDarkMode);
	}
}

void UBaseGameInstance::SetEyeProtect(bool IsChecked)
{
	if(IsChecked)
	{
		GetWorld()->GetTimerManager().SetTimer(TimerOnEyeProtect,this,
			&UBaseGameInstance::BlockEyeProtect, EyeProtectRateDuration, false);
	}
	else
	{
		ClearEyeProtect();
		GetWorld()->GetTimerManager().ClearTimer(TimerOnEyeProtect);
	}
}

void UBaseGameInstance::ShowAttention(FString NewText)
{
	if (!ensure(AttentionClass)) return;

	AttentionWidget = CreateWidget<UAttentionWidget>(this, AttentionClass);
	AttentionWidget->SetBaseText(NewText);
	AttentionWidget->AddToViewport(5);
}

void UBaseGameInstance::BlockEyeProtect()
{
	IsEyeProtectActive = true;
	ShowAttention("You are playing too much, you need to take a break");
	// ShowAttention("Вы провели много времени в игре, вам стоит отдохнуть.");
}

void UBaseGameInstance::ClearEyeProtect()
{
	IsEyeProtectActive = false;

	UE_LOG(LogTemp, Display, TEXT("BLOCK EYE PROTECT DEACTIVATE!"));
}

void UBaseGameInstance::BlockDarkMode()
{
	IsDarkModeActive = true;
	ShowAttention("If you are playing in dark time, we rec below your screen brightness");
	// ShowAttention("Играя в темное время суток, рекомендуем вам понизить яркость экрана");
}

void UBaseGameInstance::ClearDarkModeProtect()
{
	IsDarkModeActive = false;

	UE_LOG(LogTemp, Display, TEXT("Dark Mode DEACTIVATE!"));
}

