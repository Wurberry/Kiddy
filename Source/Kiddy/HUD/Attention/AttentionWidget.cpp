// © 2023 Evstigneev Daniil. All Rights Reserved.


#include "Kiddy/HUD/Attention/AttentionWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kiddy/GameInstances/BaseGameInstance.h"

void UAttentionWidget::SetBaseText(FString NewText)
{
	TBShowText->SetText(FText::FromString(NewText));
}

void UAttentionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BtnConfirm->OnClicked.AddDynamic(this, &UAttentionWidget::DestructWidget);
	
}

void UAttentionWidget::DestructWidget()
{
	this->RemoveFromParent();
	this->Destruct();

	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetGameInstance());
	
	if(GameInstance->GetIsEyeProtect())
	{
		GameInstance->SetEyeProtect(true);
	}
	else
	{
		GameInstance->SetEyeProtect(false);
	}
	
	if(GameInstance->GetIsDarkMode())
	{
		GameInstance->SetDarkMode(true);
	}
	
}
