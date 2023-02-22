// Fill out your copyright notice in the Description page of Project Settings.

#include "UW_ChattingRoom.h"
#include "Kismet/GameplayStatics.h"
#include "CCPlayerState.h"
#include "CCPlayerController.h"
#include "CCNetworkManager.h"

void UUW_ChattingRoom::RoomExitCallback()
{
	auto PlayerControllerPtr = GetPlayerController();
	if (!PlayerControllerPtr)
	{
		return;
	}

	NetworkManager->sendMsg(NetworkManager->FormatQuitChattingRoomComm());
	this->RemoveFromViewport();
	PlayerControllerPtr->ChattingRoomToWaitRoom();
}

void UUW_ChattingRoom::SendChattingCallback(const FText& Text, ETextCommit::Type CommitMethod)
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

		NetworkManager->sendMsg(Input_Chat->GetText().ToString() + '\n');

		/*UTextBlock* NewTextBlock = NewObject<UTextBlock>();
		NewTextBlock->SetText(Text);
		ScrollBox_Chat->AddChild(NewTextBlock);
		ScrollBox_Chat->ScrollToEnd();*/

		Input_Chat->SetText(FText());
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

ACCPlayerController* UUW_ChattingRoom::GetPlayerController()
{
	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		return Cast<ACCPlayerController>(World->GetFirstPlayerController());;
	}
	return nullptr;
}

void UUW_ChattingRoom::NativeConstruct()
{
	if (Button_Exit)
	{
		Button_Exit->OnClicked.AddDynamic(this, &UUW_ChattingRoom::RoomExitCallback);
	}

	Input_Chat->OnTextCommitted.AddDynamic(this, &UUW_ChattingRoom::SendChattingCallback);

	NetworkManager = Cast<UCCNetworkManager>(\
		UGameplayStatics::GetGameInstance(GetWorld()));
	if (!NetworkManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("networkmanager is null pointer"));
	}
}

void UUW_ChattingRoom::RenewChattingRoomLog(const FString& msg)
{
	UTextBlock* NewTextBlock = NewObject<UTextBlock>(ScrollBox_Chat);
	int32 MsgSize = msg.Len();
	FString SubStr = msg.Mid(0, MsgSize - 2);
	NewTextBlock->SetText(FText::FromString(SubStr));
	//NewTextBlock->SetText(FText::FromString(msg));

	ScrollBox_Chat->AddChild(NewTextBlock);
	ScrollBox_Chat->ScrollToEnd();
}
