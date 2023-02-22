// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_RoomInfoPopup.h"
#include "Kismet/GameplayStatics.h"
#include "CCPlayerState.h"
#include "CCPlayerController.h"
#include "CCNetworkManager.h"


void UUW_RoomInfoPopup::RoomInfoRenewButtonCallback()
{
	auto PlayerControllerPtr = GetPlayerController();
	if (!PlayerControllerPtr)
	{
		return;
	}

	auto PlayerState = Cast<ACCPlayerState>(PlayerControllerPtr->PlayerState);
	if (!PlayerState)
	{
		return;
	}

	PlayerControllerPtr->SetPlayerState(EPlayerState::ShowRoomInfoCommSent);
	NetworkManager->sendMsg(NetworkManager->FormatShowRoomInfoComm(Input_RoomNum->GetText().ToString()));
	UE_LOG(LogTemp, Warning, TEXT("show RoomInfo command sent"));
}

void UUW_RoomInfoPopup::RoomInfoExitCallback()
{
	this->RemoveFromViewport();
}

ACCPlayerController* UUW_RoomInfoPopup::GetPlayerController()
{
	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		return Cast<ACCPlayerController>(World->GetFirstPlayerController());;
	}
	return nullptr;
}

void UUW_RoomInfoPopup::NativeConstruct()
{
	if (Button_Confirm)
	{
		Button_Confirm->OnClicked.AddDynamic(this, &UUW_RoomInfoPopup::RoomInfoRenewButtonCallback);
	}

	if (Button_Exit)
	{
		Button_Exit->OnClicked.AddDynamic(this, &UUW_RoomInfoPopup::RoomInfoExitCallback);
	}

	NetworkManager = Cast<UCCNetworkManager>(\
		UGameplayStatics::GetGameInstance(GetWorld()));
	if (!NetworkManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("networkmanager is null pointer"));
	}
}

void UUW_RoomInfoPopup::SetRoomInfoUI(const FString& msg)
{
	ScrollBox_RoomInfo->ClearChildren();

	UTextBlock* NewTextBlock = NewObject<UTextBlock>(ScrollBox_RoomInfo);
	NewTextBlock->SetText(FText::FromString(msg));

	ScrollBox_RoomInfo->AddChild(NewTextBlock);
}
