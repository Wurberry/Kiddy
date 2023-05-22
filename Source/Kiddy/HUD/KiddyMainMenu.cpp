// © 2023 Evstigneev Daniil. All Rights Reserved.

#include "Kiddy/HUD/KiddyMainMenu.h"

#include "SettingsWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

bool UKiddyMainMenu::Initialize()
{
	bool const bSuccess = Super::Initialize();
	if(!bSuccess) return false;

	/** Initialise main meni widgets and bing Callbacks*/
	if(!ensure(SettingsButton)) return false;
	SettingsButton->OnClicked.AddDynamic(this, &UKiddyMainMenu::OpenSettings);
	
	if(!ensure(Levels1Button)) return false;
	Levels1Button->OnClicked.AddDynamic(this, &UKiddyMainMenu::OpenLevel1);

	if(!ensure(Levels2Button)) return false;
	Levels2Button->OnClicked.AddDynamic(this, &UKiddyMainMenu::OpenLevel2);
	
	return true;
}

void UKiddyMainMenu::OpenMainMenu()
{
	SettingsWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void UKiddyMainMenu::OpenSettings()
{
	ChangeSettingsVisibility();
}

void UKiddyMainMenu::ChangeSettingsVisibility()
{
	if(SettingsWidget->GetVisibility() == ESlateVisibility::Visible)
	{
		SettingsWidget->SetVisibility(ESlateVisibility::Collapsed);
		
	}
	else
	{
		SettingsWidget->SetVisibility(ESlateVisibility::Visible);
		Cast<USettingsWidget>(SettingsWidget)->Init();
	}
}

void UKiddyMainMenu::OpenLevel1()
{
	UGameplayStatics::OpenLevel(GetWorld(), "ChooseShadow");
}

void UKiddyMainMenu::OpenLevel2()
{
	UGameplayStatics::OpenLevel(GetWorld(), "FindPair");
}

