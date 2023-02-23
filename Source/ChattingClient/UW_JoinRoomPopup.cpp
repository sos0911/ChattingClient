// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_JoinRoomPopup.h"
#include "Kismet/GameplayStatics.h"
#include "CCPlayerState.h"
#include "CCPlayerController.h"
#include "CCNetworkManager.h"

#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/ScrollBox.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "Runtime/UMG/Public/Components/EditableTextBox.h"

void UUW_JoinRoomPopup::JoinRoomButtonCallback()
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

	NetworkManager->sendMsg(NetworkManager->FormatJoinRoomComm(Input_RoomNum->GetText().ToString()));
	PlayerControllerPtr->SetPlayerState(EPlayerState::JoinRoomCommSent);
	UE_LOG(LogTemp, Warning, TEXT("JoinRoom command sent"));
}

void UUW_JoinRoomPopup::JoinRoomExitCallback()
{
	this->RemoveFromViewport();
	auto PlayerControllerPtr = GetPlayerController();
	if (!PlayerControllerPtr)
	{
		return;
	}
	PlayerControllerPtr->SetPlayerState(EPlayerState::Login);
}

ACCPlayerController* UUW_JoinRoomPopup::GetPlayerController()
{
	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		return Cast<ACCPlayerController>(World->GetFirstPlayerController());;
	}
	return nullptr;
}

void UUW_JoinRoomPopup::NativeConstruct()
{
	if (Button_Confirm)
	{
		Button_Confirm->OnClicked.AddDynamic(this, &UUW_JoinRoomPopup::JoinRoomButtonCallback);
	}

	if (Button_Exit)
	{
		Button_Exit->OnClicked.AddDynamic(this, &UUW_JoinRoomPopup::JoinRoomExitCallback);
	}

	NetworkManager = Cast<UCCNetworkManager>(\
		UGameplayStatics::GetGameInstance(GetWorld()));
	if (!NetworkManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("networkmanager is null pointer"));
	}
}

void UUW_JoinRoomPopup::SetJoinRoomResultUI(const FString& msg)
{
	ScrollBox_Result->ClearChildren();

	UTextBlock* NewTextBlock = NewObject<UTextBlock>(ScrollBox_Result);
	NewTextBlock->SetText(FText::FromString(msg));
	ScrollBox_Result->AddChild(NewTextBlock);
}
