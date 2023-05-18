// © 2023 Evstigneev Daniil. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Kiddy/HUD/BaseHUDWidget.h"
#include "BaseMenuWidget.generated.h"

class IKiddyMenuInterface;

/**
 *  Parent widget class for menu widgets
 */
UCLASS()
class KIDDY_API UBaseMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void Setup();
	void Teardown();

	IKiddyMenuInterface* GetMenuInterface() const { return MenuInterface;}
	void SetMenuInterface(IKiddyMenuInterface* KiddyMenuInterface);

protected:

	IKiddyMenuInterface* MenuInterface;
	
};
