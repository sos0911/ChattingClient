// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_MakeRoomPopup.h"
#include "Kismet/GameplayStatics.h"
#include "CCPlayerState.h"
#include "CCPlayerController.h"
#include "CCNetworkManager.h"


void UUW_MakeRoomPopup::MakeRoomButtonCallback()
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

	NetworkManager->sendMsg(NetworkManager->FormatMakeRoomComm(Input_RoomMaximumCnt->GetText().ToString(), \
		Input_RoomName->GetText().ToString()));
	UE_LOG(LogTemp, Warning, TEXT("makeRoom command sent"));

	this->RemoveFromViewport();
	PlayerControllerPtr->WaitRoomToChattingRoom();
}

void UUW_MakeRoomPopup::MakeRoomExitCallback()
{
	this->RemoveFromViewport();
	auto PlayerControllerPtr = GetPlayerController();
	if (!PlayerControllerPtr)
	{
		return;
	}
	PlayerControllerPtr->SetPlayerState(EPlayerState::Login);
}

ACCPlayerController* UUW_MakeRoomPopup::GetPlayerController()
{
	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		return Cast<ACCPlayerController>(World->GetFirstPlayerController());;
	}
	return nullptr;
}

void UUW_MakeRoomPopup::NativeConstruct()
{
	if (Button_Confirm)
	{
		Button_Confirm->OnClicked.AddDynamic(this, &UUW_MakeRoomPopup::MakeRoomButtonCallback);
	}

	if (Button_Exit)
	{
		Button_Exit->OnClicked.AddDynamic(this, &UUW_MakeRoomPopup::MakeRoomExitCallback);
	}

	NetworkManager = Cast<UCCNetworkManager>(\
		UGameplayStatics::GetGameInstance(GetWorld()));
	if (!NetworkManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("networkmanager is null pointer"));
	}
}
