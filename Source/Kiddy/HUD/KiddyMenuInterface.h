﻿// © 2023 Evstigneev Daniil. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "KiddyMenuInterface.generated.h"


// This class does not need to be modified
UINTERFACE(MinimalAPI)
class UKiddyMenuInterface : public UInterface
{
	GENERATED_BODY()

	
	
};

/*
 * Interface to handle various menu functions
 */
class KIDDY_API IKiddyMenuInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface
public:
	virtual void StartGame() = 0;
	virtual void LoadGameHUD() = 0;
	virtual void LoadMainMenu() = 0;
	
};
