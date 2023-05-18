// © 2023 Evstigneev Daniil. All Rights Reserved.


#include "Kiddy/HUD/FruitVege/FindPairListEntry.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Kiddy/DataTables/FruitVegeDataTable.h"
#include "Kiddy/GameInstances/BaseGameInstance.h"
#include "Styling/SlateColor.h"

void UFindPairListEntry::Init(FFruitVege FruitVege)
{
	this->ID = FruitVege.ID;
	this->IsDark = FruitVege.IsDark;
	this->Light = FruitVege.Light;
	this->Dark = FruitVege.Dark;
}

void UFindPairListEntry::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	GameInstance = Cast<UBaseGameInstance>(GetGameInstance());
	
}

void UFindPairListEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UFindPairListEntry* FruitVege = Cast<UFindPairListEntry>(ListItemObject); 
	this->ID = FruitVege->ID;
	this->IsDark = FruitVege->IsDark;
	this->IconImage->SetBrushFromTexture(FruitVege->Light);
	
	IconImage->Brush.SetImageSize(FVector2d(150, 150));

	if(!BtnImage->OnClicked.IsBound())
	{
		BtnImage->OnClicked.AddDynamic(this, &UFindPairListEntry::SendItemEntry);
	}
}

void UFindPairListEntry::SendItemEntry()
{
	GameInstance->OnListItemFruitVegeClick.Broadcast(ID, IsDark, this);
}
