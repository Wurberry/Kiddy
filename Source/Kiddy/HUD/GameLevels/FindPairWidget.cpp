﻿// © 2023 Evstigneev Daniil. All Rights Reserved.


#include "Kiddy/HUD/GameLevels/FindPairWidget.h"

#include <string>

#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/ListView.h"
#include "FruitVege/FindPairListEntry.h"
#include "Kiddy/DataTables/FruitVegeDataTable.h"
#include "Kiddy/GameInstances/BaseGameInstance.h"
#include "Kismet/GameplayStatics.h"

bool UFindPairWidget::Initialize()
{
	bool const bSuccess = Super::Initialize();
	if(!bSuccess) return false;
	
	GameInstance = Cast<UBaseGameInstance>(GetGameInstance());
	
	DTFruitVege = LoadObject<UDataTable>(NULL, UTF8_TO_TCHAR("DataTable'/Game/Kiddy/Core/DataTables/DT_FruitVege.DT_FruitVege'"));
	
	return true;
}

void UFindPairWidget::CreateGamePhase()
{
	GameInstance->OnListItemFruitVegeClick.Clear();
	GameInstance->OnListItemFruitVegeClick.AddDynamic(this, &UFindPairWidget::SetCheckBtn);

	BtnExit->OnClicked.Clear();
	BtnExit->OnClicked.AddDynamic(this, &UFindPairWidget::GoToMenu);
	
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

void UFindPairWidget::SetCheckBtn(int ID, bool IsDark, UObject* Object) 
{
	if(IsDark)
	{
		if(ListEntryDark != NULL)
		{
			ListEntryDark->IconImage->SetColorAndOpacity(FLinearColor(1,1,1,0));
		}
		ListEntryDark = Cast<UFindPairListEntry>(Object);
		ListEntryDark->IconImage->SetColorAndOpacity(FLinearColor(1,1,1,1));
		ChooseDarkId = ID;
	} else {
		if(ListEntryLight != NULL)
		{
			ListEntryLight->IconImage->SetColorAndOpacity(FLinearColor(1,1,1,0));
		}
		ListEntryLight = Cast<UFindPairListEntry>(Object);
		ListEntryLight->IconImage->SetColorAndOpacity(FLinearColor(1,1,1,1));
		ChooseLightId = ID;
	}
	
	UE_LOG(LogTemp, Display, TEXT("Dark id - %d"), ChooseDarkId)
	UE_LOG(LogTemp, Display, TEXT("Light id - %d"), ChooseLightId)
	
	if(ChooseDarkId == ChooseLightId)
	{
		GetWorld()->GetTimerManager().SetTimer(TimerPairWait, this, &UFindPairWidget::StartProcessRemovePairBtn, 0.2);
	} else if (ChooseDarkId != 0 && ChooseLightId != 0 && ChooseDarkId != ChooseLightId)
	{
		GetWorld()->GetTimerManager().SetTimer(TimerPairWait, this, &UFindPairWidget::HideBtnsPair, 0.5);
	}
}

void UFindPairWidget::GoToMenu()
{
	UGameplayStatics::OpenLevel(GetWorld(), "BaseMenu");
}

void UFindPairWidget::GenerateBtnsFruitVege(bool IsDark,  TArray<FName> RowNames)
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
			
		UFindPairListEntry* Entry = Cast<UFindPairListEntry>(CreateWidget(this, FindPairListEntry));
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

void UFindPairWidget::RemoveBtnsFruitVege(TArray<int> &Images, UListView* ListView, int ID)
{
	int TempFindImgIndex = Images.Find(ID);
	ListView->RemoveItem(ListView->GetItemAt(TempFindImgIndex));
	Images.RemoveAt(TempFindImgIndex);
}

void UFindPairWidget::StartProcessRemovePairBtn()
{
	ListEntryDark->IconImage->SetColorAndOpacity(FLinearColor(1,1,1,0));
	ListEntryLight->IconImage->SetColorAndOpacity(FLinearColor(1,1,1,0));
		
	RemoveBtnsFruitVege(ImagesDarkID, ListViewDark, ChooseDarkId);
	RemoveBtnsFruitVege(ImagesLightID, ListViewLight, ChooseLightId);
	ChooseDarkId = 0;
	ChooseLightId = 0;
		
	if(ListViewLight->GetListItems().Num() == 0)
	{
		CreateGamePhase();
	}
}

void UFindPairWidget::HideBtnsPair()
{
	ListEntryDark->IconImage->SetColorAndOpacity(FLinearColor(1,1,1,0));
	ListEntryLight->IconImage->SetColorAndOpacity(FLinearColor(1,1,1,0));
	ChooseDarkId = 0;
	ChooseLightId = 0;
}
