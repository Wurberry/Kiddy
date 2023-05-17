// © 2023 Evstigneev Daniil. All Rights Reserved.


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
		
		// for (FName RowName : RowNames)
		// {
		// 	FFruitVege* Item = DTFruitVege->FindRow<FFruitVege>(RowName, "");
		// 	Item->IsDark = true;
		//
		// 	FFruitVege TempFruitVege = FFruitVege(Item->ID, Item->IsDark, Item->Light, Item->Dark);
		// 	
		// 	UFruitVegeListEntry* Entry = Cast<UFruitVegeListEntry>(CreateWidget(this, FruitVegeEntry));
		// 	Entry->Init(TempFruitVege);
		// 	
		// 	ListViewDark->AddItem(Entry);
		// 	ImagesDarkID.Add(Item->ID);
		// }

		ShuffleArray(RandomStream, RowNames);

		GenerateBtnsFruitVege(false, RowNames);
		
		// for (FName RowName : RowNames)
		// {
		// 	FFruitVege* Item = DTFruitVege->FindRow<FFruitVege>(RowName, "");
		// 	Item->IsDark = false;
		//
		// 	FFruitVege TempFruitVege = FFruitVege(Item->ID, Item->IsDark, Item->Light, Item->Dark);
		// 	
		// 	UFruitVegeListEntry* Entry = Cast<UFruitVegeListEntry>(CreateWidget(this, FruitVegeEntry));
		// 	Entry->Init(TempFruitVege);
		// 	
		// 	ListViewLight->AddItem(Entry);
		// 	ImagesLightID.Add(Item->ID);
		// }
	}
}

void UChooseShadowWidget::SetCheckBtn(int ID, bool IsDark) 
{
	if(IsDark)
	{
		ChooseDarkId = ID;
	} else {
		ChooseLightId = ID;
	}
	
	UE_LOG(LogTemp, Display, TEXT("Dark id - %d"), ChooseDarkId)
	UE_LOG(LogTemp, Display, TEXT("Light id - %d"), ChooseLightId)
	
	if(ChooseDarkId != 0 && ChooseDarkId == ChooseLightId)
	{
		for (int i = 0; i<ListViewDark->GetListItems().Num(); i++)
		{
			UFruitVegeListEntry* Entry = Cast<UFruitVegeListEntry>(ListViewDark->GetItemAt(i));
			if (Entry->ID == ChooseDarkId)
			{
				ListViewDark->RemoveItem(ListViewDark->GetItemAt(i));
			}
		}
		for (int i = 0; i<ListViewLight->GetListItems().Num(); i++)
		{
			UFruitVegeListEntry* Entry = Cast<UFruitVegeListEntry>(ListViewLight->GetItemAt(i));
			if (Entry->ID == ChooseLightId)
			{
				ListViewLight->RemoveItem(ListViewLight->GetItemAt(i));
			}
		}
		// ImagesDarkID.Find(ID);
		// ImagesLightID.Find(ID);
		ChooseDarkId = 0;
		ChooseLightId = 0;

		if(ListViewDark->GetListItems().Num() == 0)
		{
			CreateGamePhase();
		}
		
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
			ImagesDarkID.Add(Item->ID);
		} else
		{
			ListViewLight->AddItem(Entry);
			ImagesLightID.Add(Item->ID);
		}
		
	}
}

