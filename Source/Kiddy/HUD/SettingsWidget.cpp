#include "SettingsWidget.h"
#include "Components/CheckBox.h"
#include "Components/ComboBoxString.h"
#include "Kiddy/GameInstances/BaseGameInstance.h"

void USettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CBColorBlinding->SetSelectedIndex(0);
	
}

void USettingsWidget::SetDarkModeInstance(bool IsChecked)
{
	Cast<UBaseGameInstance>(GetGameInstance())->SetDarkMode(IsChecked);
}

void USettingsWidget::SetEyeProtectInstance(bool IsChecked)
{
	Cast<UBaseGameInstance>(GetGameInstance())->SetEyeProtect(IsChecked);
}

void USettingsWidget::Init()
{
	ChBDarkMode->OnCheckStateChanged.Clear();
	ChBEyeProtect->OnCheckStateChanged.Clear();
	ChBDarkMode->OnCheckStateChanged.AddDynamic(this, &USettingsWidget::SetDarkModeInstance);
	ChBEyeProtect->OnCheckStateChanged.AddDynamic(this, &USettingsWidget::SetEyeProtectInstance);
}
