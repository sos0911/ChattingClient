// Fill out your copyright notice in the Description page of Project Settings.

#include "UW_ChattingRoom.h"
#include "Kismet/GameplayStatics.h"
#include "CCPlayerState.h"
#include "CCPlayerController.h"
#include "CCNetworkManager.h"

void UUW_ChattingRoom::RoomExitCallback()
{
	this->RemoveFromViewport();
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

	NetworkManager = Cast<UCCNetworkManager>(\
		UGameplayStatics::GetGameInstance(GetWorld()));
	if (!NetworkManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("networkmanager is null pointer"));
	}
}

void UUW_ChattingRoom::SetChatInfoUI(const FString& msg)
{
	UTextBlock* NewTextBlock = NewObject<UTextBlock>(ScrollBox_Chat);
	NewTextBlock->SetText(FText::FromString(msg));

	ScrollBox_Chat->AddChild(NewTextBlock);
}
