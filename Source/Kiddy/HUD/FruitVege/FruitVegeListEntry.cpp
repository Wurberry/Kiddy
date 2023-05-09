// © 2023 Evstigneev Daniil. All Rights Reserved.


#include "Kiddy/HUD/FruitVege/FruitVegeListEntry.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Kiddy/DataTables/FruitVegeDataTable.h"
#include "Kiddy/GameInstances/BaseGameInstance.h"


void UFruitVegeListEntry::Init(FFruitVege FruitVege)
{
	this->ID = FruitVege.ID;
	this->IsDark = FruitVege.IsDark;
	this->Light = FruitVege.Light;
	this->Dark = FruitVege.Dark;
	
}

void UFruitVegeListEntry::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	GameInstance = Cast<UBaseGameInstance>(GetGameInstance());
	
}

void UFruitVegeListEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UFruitVegeListEntry* FruitVege = Cast<UFruitVegeListEntry>(ListItemObject); 
	this->ID = FruitVege->ID;
	this->IsDark = FruitVege->IsDark;
	if(FruitVege->IsDark)
	{
		this->IconImage->SetBrushFromTexture(FruitVege->Dark);
	}
	else
	{
		this->IconImage->SetBrushFromTexture(FruitVege->Light);
	}
	IconImage->Brush.SetImageSize(FVector2d(150, 150));

	if(!BtnImage->OnClicked.IsBound())
	{
		BtnImage->OnClicked.AddDynamic(this, &UFruitVegeListEntry::SendItemEntry);
	}
}

void UFruitVegeListEntry::SendItemEntry()
{
	GameInstance->OnListItemFruitVegeClick.Broadcast(ID, IsDark);
}
