// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_WaitRoom.h"
#include "CCNetworkManager.h"
#include "CCPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "CCPlayerController.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "FUIProtocol.h"


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
	if (Button_PlayerList_Renew)
	{
		Button_PlayerList_Renew->OnClicked.AddDynamic(this, &UUW_WaitRoom::PlayerListRenewButtonCallback);
	}
	if (Button_Exit)
	{
		Button_Exit->OnClicked.AddDynamic(this, &UUW_WaitRoom::ProgramExitCallback);
	}

	Input_WhisperMsg->OnTextCommitted.AddDynamic(this, &UUW_WaitRoom::SendWhisperCallback);

	NetworkManager = Cast<UCCNetworkManager>(\
		UGameplayStatics::GetGameInstance(GetWorld()));
	if (!NetworkManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("networkmanager is null pointer"));
	}
}

void UUW_WaitRoom::SetInfoListUI(const FString& msg)
{
	ScrollBox_InfoList->ClearChildren();

	UTextBlock* NewTextBlock = NewObject<UTextBlock>(ScrollBox_InfoList);
	NewTextBlock->Font.Size = FontProtocol::INFOLISTFONTSIZE;
	NewTextBlock->SetText(FText::FromString(msg));

	ScrollBox_InfoList->AddChild(NewTextBlock);
}

void UUW_WaitRoom::SetWhisperUI(const FString& msg)
{
	UTextBlock* NewTextBlock = NewObject<UTextBlock>(ScrollBox_ChatList);
	NewTextBlock->Font.Size = FontProtocol::INFOLISTFONTSIZE;
	int32 MsgSize = msg.Len();
	FString SubStr = msg.Mid(0, MsgSize - 2);
	NewTextBlock->SetText(FText::FromString(SubStr));
	ScrollBox_ChatList->AddChild(NewTextBlock);
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
	auto PlayerControllerPtr = GetPlayerController();
	if (!PlayerControllerPtr)
	{
		return;
	}

	PlayerControllerPtr->JoinRoomPopup();
}

void UUW_WaitRoom::RoomMakeButtonCallback()
{
	auto PlayerControllerPtr = GetPlayerController();
	if (!PlayerControllerPtr)
	{
		return;
	}

	PlayerControllerPtr->MakeRoomPopup();
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

void UUW_WaitRoom::ProgramExitCallback()
{
	auto PlayerControllerPtr = GetPlayerController();
	if (!PlayerControllerPtr)
	{
		return;
	}

	// donghyun : 소켓도 마무리지어줘야 함
	NetworkManager->sendMsg(NetworkManager->QuitProgramComm());
	NetworkManager->closeConnect();
	UKismetSystemLibrary::QuitGame(this, 0, EQuitPreference::Quit, false);
}

void UUW_WaitRoom::SendWhisperCallback(const FText& Text, ETextCommit::Type CommitMethod)
{
	switch (CommitMethod)
	{
		/*case ETextCommit::Default:
			break;*/
	case ETextCommit::OnEnter:
	{
		if (Text.IsEmpty())
			return;

		if (NetworkManager == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("networkmanager is null pointer"));
			return;
		}

		NetworkManager->sendMsg(NetworkManager->FormatWhisperComm(Input_PlayerName->GetText().ToString(), \
			Input_WhisperMsg->GetText().ToString()));

		FString EchoMsg = FString::Printf(TEXT("Sended Msg : %s"), *Input_WhisperMsg->GetText().ToString());

		UTextBlock* NewTextBlock = NewObject<UTextBlock>();
		NewTextBlock->Font.Size = FontProtocol::INFOLISTFONTSIZE;
		NewTextBlock->SetText(FText::FromString(EchoMsg));
		ScrollBox_ChatList->AddChild(NewTextBlock);
		ScrollBox_ChatList->ScrollToEnd();

		Input_WhisperMsg->SetText(FText());
	}
	break;
	/*case ETextCommit::OnUserMovedFocus:
		break;
	case ETextCommit::OnCleared:
		break;*/
	default:
		break;
	}
}