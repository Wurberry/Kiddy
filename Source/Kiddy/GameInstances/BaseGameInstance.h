// © 2023 Evstigneev Daniil. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "KiddyMenuInterface.h"
#include "Engine/GameInstance.h"
#include "BaseGameInstance.generated.h"

/**
 *  Kiddy Game Instance
 */
UCLASS()
class KIDDY_API UBaseGameInstance : public UGameInstance, public IKiddyMenuInterface
{
	GENERATED_BODY()

public:

	virtual virtual void Init() override;

	virtual void StartGame() override;
	virtual void LoadMainMenu() override;
	virtual void OpenCloseSettings(bool bNeedToOpen) override;
	
};
