// Fill out your copyright notice in the Description page of Project Settings.


#include "Kiddy/HUD/BaseMenuWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"

void UBaseMenuWidget::Setup()
{
	this->AddToViewport();

	auto const World = GetWorld();
	if(!ensure(World)) return;
	APlayerController* PlayerController = World->GetFirstPlayerController();
	if(!ensure(PlayerController)) return;

	this->SetOwningPlayer(PlayerController);

	/** Set input mode to Game & UI, focus the new widget, and show mouse cursor*/
	FInputModeGameAndUI InputModeData;
	InputModeData.SetWidgetToFocus(this->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	PlayerController->SetInputMode(InputModeData);

	/** Center the mouse cursor */
	PlayerController->SetMouseLocation(
		UWidgetLayoutLibrary::GetViewportSize(this).X / 2,
		UWidgetLayoutLibrary::GetViewportSize(this).Y / 2);

	PlayerController->bShowMouseCursor = true;
	
}

void UBaseMenuWidget::Teardown()
{
	this->RemoveFromViewport();

	const UWorld* World = GetWorld();
	if(!ensure(World)) return;
	APlayerController* PlayerController = World->GetFirstPlayerController();
	if(!ensure(PlayerController)) return;

	FInputModeGameAndUI InputModeData;
	PlayerController->SetInputMode(InputModeData);
	
}

void UBaseMenuWidget::SetMenuInterface(IKiddyMenuInterface* InMenuInterface)
{
	MenuInterface = InMenuInterface;
}
