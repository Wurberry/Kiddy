// © 2023 Evstigneev Daniil. All Rights Reserved.


#include "Kiddy/HUD/KiddyMainMenu.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

bool UKiddyMainMenu::Initialize()
{
	bool const bSuccess = Super::Initialize();
	if(!bSuccess) return false;

	/** Initialise main meni widgets and bing Callbacks*/
	if(!ensure(SettingsButton)) return false;
	SettingsButton->OnClicked.AddDynamic(this, &UKiddyMainMenu::OpenSettings);

	/**
	 * TODO: Make some dataTable with levels path and image,
	 * TODO: and generate btns from it
	 */
	
	if(!ensure(Levels1Button)) return false;
	Levels1Button->OnClicked.AddDynamic(this, &UKiddyMainMenu::OpenLevel1);

	if(!ensure(Levels2Button)) return false;
	Levels2Button->OnClicked.AddDynamic(this, &UKiddyMainMenu::OpenLevel2);

	if(!ensure(Levels3Button)) return false;
	Levels3Button->OnClicked.AddDynamic(this, &UKiddyMainMenu::OpenLevel3);
	
	
	return true;
}

void UKiddyMainMenu::OpenMainMenu()
{
	SettingsMenu->SetVisibility(ESlateVisibility::Collapsed);
}

void UKiddyMainMenu::OpenSettings()
{
	ChangeSettingsVisibility();
}

void UKiddyMainMenu::ChangeSettingsVisibility()
{
	if(SettingsMenu->GetVisibility() == ESlateVisibility::Visible)
	{
		SettingsMenu->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		SettingsMenu->SetVisibility(ESlateVisibility::Visible);
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

void UKiddyMainMenu::OpenLevel3()
{
	UGameplayStatics::OpenLevel(GetWorld(), "Level3");
}

