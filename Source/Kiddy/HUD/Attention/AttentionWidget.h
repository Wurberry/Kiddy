// © 2023 Evstigneev Daniil. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kiddy/HUD/BaseHUDWidget.h"
#include "AttentionWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class KIDDY_API UAttentionWidget : public UBaseHUDWidget
{
	GENERATED_BODY()

protected:

	UFUNCTION()
	virtual void NativeConstruct() override;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* BtnConfirm;

private:

	UFUNCTION()
	void DestructWidget();
	
};
