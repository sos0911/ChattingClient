// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_WaitRoom.h"
#include "CCNetworkManager.h"
#include "CCPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "CCPlayerController.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"


class ACCPlayerController* UUW_WaitRoom::GetPlayerController()
{
	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		return Cast<ACCPlayerController>(World->GetFirstPlayerController());;
	}
	return nullptr;
}

void UUW_WaitRoom::NativeConstruct()
{
	if (Button_RoomList_Renew)
	{
		Button_RoomList_Renew->OnClicked.AddDynamic(this, &UUW_WaitRoom::RoomListRenewButtonCallback);
	}
	if (Button_Room_Join)
	{
		Button_Room_Join->OnClicked.AddDynamic(this, &UUW_WaitRoom::RoomJoinButtonCallback);
	}
	if (Button_Room_Make)
	{
		Button_Room_Make->OnClicked.AddDynamic(this, &UUW_WaitRoom::RoomMakeButtonCallback);
	}
	if (Button_Room_Info)
	{
		Button_Room_Info->OnClicked.AddDynamic(this, &UUW_WaitRoom::RoomInfoButtonCallback);
	}
	if (Button_Player_Info)
	{
		Button_Player_Info->OnClicked.AddDynamic(this, &UUW_WaitRoom::PlayerInfoButtonCallback);
	}
	if (Button_Send_Whisper)
	{
		Button_Send_Whisper->OnClicked.AddDynamic(this, &UUW_WaitRoom::SendWhisperButtonCallback);
	}
	if (Button_PlayerList_Renew)
	{
		Button_PlayerList_Renew->OnClicked.AddDynamic(this, &UUW_WaitRoom::PlayerListRenewButtonCallback);
	}


	NetworkManager = Cast<UCCNetworkManager>(\
		UGameplayStatics::GetGameInstance(GetWorld()));
	if (!NetworkManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("networkmanager is null pointer"));
	}
}

void UUW_WaitRoom::SetPlayerListUI(const FString& msg)
{
	ScrollBox_PlayerList->ClearChildren();

	UTextBlock* NewTextBlock = NewObject<UTextBlock>(ScrollBox_PlayerList);
	NewTextBlock->SetText(FText::FromString(msg));

	ScrollBox_PlayerList->AddChild(NewTextBlock);
}

void UUW_WaitRoom::SetRoomListUI(const FString& msg)
{
	ScrollBox_RoomList->ClearChildren();

	UTextBlock* NewTextBlock = NewObject<UTextBlock>(ScrollBox_RoomList);
	NewTextBlock->SetText(FText::FromString(msg));

	ScrollBox_RoomList->AddChild(NewTextBlock);
}

void UUW_WaitRoom::RoomListRenewButtonCallback()
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

	/*if (PlayerState->EnumPlayerState != EPlayerState::Login)
	{
		UE_LOG(LogTemp, Warning, TEXT("Login error occured before using lobby func"));
		return;
	}*/

	// donghyun : UI 내용 채우는건 서버로부터 온 후
	PlayerControllerPtr->SetPlayerState(EPlayerState::ShowRoomListCommSent);
	NetworkManager->sendMsg(NetworkManager->FormatShowRoomListComm());
	UE_LOG(LogTemp, Warning, TEXT("show RoomList command sent"));
}

void UUW_WaitRoom::RoomJoinButtonCallback()
{

}

void UUW_WaitRoom::RoomMakeButtonCallback()
{

}

void UUW_WaitRoom::RoomInfoButtonCallback()
{
	auto PlayerControllerPtr = GetPlayerController();
	if (!PlayerControllerPtr)
	{
		return;
	}

	PlayerControllerPtr->MakeRoomInfoPopup();
}

void UUW_WaitRoom::PlayerInfoButtonCallback()
{
	auto PlayerControllerPtr = GetPlayerController();
	if (!PlayerControllerPtr)
	{
		return;
	}

	PlayerControllerPtr->MakePlayerInfoPopup();
}

void UUW_WaitRoom::SendWhisperButtonCallback()
{

}

void UUW_WaitRoom::PlayerListRenewButtonCallback()
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

	if (PlayerState->EnumPlayerState != EPlayerState::Login)
	{
		UE_LOG(LogTemp, Warning, TEXT("Login error occured before using lobby func"));
		return;
	}

	// donghyun : UI 내용 채우는건 서버로부터 온 후
	PlayerControllerPtr->SetPlayerState(EPlayerState::ShowPlayerListCommSent);
	NetworkManager->sendMsg(NetworkManager->FormatShowPlayerListComm());
	UE_LOG(LogTemp, Warning, TEXT("show playerList command sent"));
}
