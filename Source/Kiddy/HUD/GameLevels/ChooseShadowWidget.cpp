﻿// © 2023 Evstigneev Daniil. All Rights Reserved.


#include "Kiddy/HUD/GameLevels/ChooseShadowWidget.h"

#include <string>

#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/ListView.h"
#include "FruitVege/FruitVegeListEntry.h"
#include "Kiddy/DataTables/FruitVegeDataTable.h"
#include "Kiddy/GameInstances/BaseGameInstance.h"
#include "Kismet/GameplayStatics.h"

bool UChooseShadowWidget::Initialize()
{
	bool const bSuccess = Super::Initialize();
	if(!bSuccess) return false;
	
	GameInstance = Cast<UBaseGameInstance>(GetGameInstance());
	
	DTFruitVege = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR("DataTable'/Game/Kiddy/Core/DataTables/DT_FruitVege.DT_FruitVege'"));
	
	return true;
}

void UChooseShadowWidget::CreateGamePhase()
{
	GameInstance->OnListItemFruitVegeClick.Clear();
	GameInstance->OnListItemFruitVegeClick.AddDynamic(this, &UChooseShadowWidget::SetCheckBtn);

	BtnExit->OnClicked.Clear();
	BtnExit->OnClicked.AddDynamic(this, &UChooseShadowWidget::GoToMenu);
	
	if(!DTFruitVege) return;

	TArray<FName> RowNames = DTFruitVege->GetRowNames();
	
	FRandomStream RandomStream;
	double secs = FTimespan(FDateTime::Now().GetTicks()).GetTotalSeconds();
	RandomStream.Initialize((int32)(((int64)secs) % INT_MAX));
	
	ShuffleArray(RandomStream, RowNames);
	
	RowNames.RemoveAt(CountElementsView, RowNames.Num()-CountElementsView);
	
	if(!RowNames.IsEmpty())
	{
		GenerateBtnsFruitVege(true, RowNames);

		ShuffleArray(RandomStream, RowNames);

		GenerateBtnsFruitVege(false, RowNames);
	}
}

void UChooseShadowWidget::SetCheckBtn(int ID, bool IsDark, UObject* Object) 
{
	if (IsDark)
	{
		if (ChooseDarkId != 0)
		{
			ListEntryDark->ClearActive();
		}
		ListEntryDark = Cast<UFruitVegeListEntry>(Object);
		ListEntryDark->SetActive();
		ChooseDarkId = ID;
	} else {
		if (ChooseLightId != 0)
		{
			ListEntryLight->ClearActive();
		}
		ListEntryLight = Cast<UFruitVegeListEntry>(Object);
		ListEntryLight->SetActive();
		ChooseLightId = ID;
	}
	
	if (ChooseDarkId == ChooseLightId)
	{
		RemoveBtnsFruitVege(ImagesDarkID, ListViewDark, ChooseDarkId);
		RemoveBtnsFruitVege(ImagesLightID, ListViewLight, ChooseLightId);
		ClearListBtnPairActive();
		
		if (ListViewLight->GetListItems().Num() == 0)
		{
			CreateGamePhase();
		}
	} else if (ChooseDarkId != 0 && ChooseLightId != 0 && ChooseDarkId != ChooseLightId)
	{
		ClearListBtnPairActive();
	}
}

void UChooseShadowWidget::GoToMenu()
{
	UGameplayStatics::OpenLevel(GetWorld(), "BaseMenu");
}

void UChooseShadowWidget::GenerateBtnsFruitVege(bool IsDark,  TArray<FName> RowNames)
{
	for (FName RowName : RowNames)
	{
		FFruitVege* Item = DTFruitVege->FindRow<FFruitVege>(RowName, "");

		if (IsDark)
		{
			Item->IsDark = true;
		} else
		{
			Item->IsDark = false;
		}

		FFruitVege TempFruitVege = FFruitVege(Item->ID, Item->IsDark, Item->Light, Item->Dark);
			
		UFruitVegeListEntry* Entry = Cast<UFruitVegeListEntry>(CreateWidget(this, FruitVegeEntry));
		Entry->Init(TempFruitVege);

		if (IsDark)
		{
			ListViewDark->AddItem(Entry);
			ImagesDarkID.Add(Entry->ID);
		} else
		{
			ListViewLight->AddItem(Entry);
			ImagesLightID.Add(Entry->ID);
		}
		
	}
}

void UChooseShadowWidget::RemoveBtnsFruitVege(TArray<int> &Images, UListView* ListView, int ID)
{
	int TempFindImgIndex = Images.Find(ID);
	ListView->RemoveItem(ListView->GetItemAt(TempFindImgIndex));
	Images.RemoveAt(TempFindImgIndex);
}

void UChooseShadowWidget::ClearListBtnPairActive()
{
	ListEntryDark->ClearActive();
	ListEntryLight->ClearActive();
	ChooseDarkId = 0;
	ChooseLightId = 0;
}