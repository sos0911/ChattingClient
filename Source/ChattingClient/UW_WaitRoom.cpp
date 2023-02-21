// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_WaitRoom.h"
#include "CCNetworkManager.h"
#include "Kismet/GameplayStatics.h"


class APlayerController* UUW_WaitRoom::GetPlayerController()
{
	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		return World->GetFirstPlayerController();
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

void UUW_WaitRoom::RoomListRenewButtonCallback()
{

}

void UUW_WaitRoom::RoomJoinButtonCallback()
{

}

void UUW_WaitRoom::RoomMakeButtonCallback()
{

}

void UUW_WaitRoom::RoomInfoButtonCallback()
{

}

void UUW_WaitRoom::PlayerInfoButtonCallback()
{

}

void UUW_WaitRoom::SendWhisperButtonCallback()
{

}

void UUW_WaitRoom::PlayerListRenewButtonCallback()
{

}
