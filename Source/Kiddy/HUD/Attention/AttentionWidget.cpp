// © 2023 Evstigneev Daniil. All Rights Reserved.


#include "Kiddy/HUD/Attention/AttentionWidget.h"

#include "Components/Button.h"
#include "Kiddy/GameInstances/BaseGameInstance.h"

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
}
