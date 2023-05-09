// © 2023 Evstigneev Daniil. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BaseHUDWidget.h"
#include "SettingsWidget.generated.h"


/**
 * 
 */
UCLASS()
class KIDDY_API USettingsWidget : public UBaseHUDWidget
{
	GENERATED_BODY()

public:
	
	void NativeConstruct() override;
	
};
