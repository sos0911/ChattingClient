// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_PlayerInfoPopup.h"
#include "Kismet/GameplayStatics.h"
#include "CCPlayerState.h"
#include "CCPlayerController.h"
#include "CCNetworkManager.h"


void UUW_PlayerInfoPopup::PlayerInfoRenewButtonCallback()
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

	PlayerControllerPtr->SetPlayerState(EPlayerState::ShowPlayerInfoCommSent);
	NetworkManager->sendMsg(NetworkManager->FormatShowPlayerInfoComm(Input_PlayerName->GetText().ToString()));
	UE_LOG(LogTemp, Warning, TEXT("show PlayerInfo command sent"));
}

void UUW_PlayerInfoPopup::PlayerInfoExitCallback()
{
	this->RemoveFromViewport();
}

ACCPlayerController* UUW_PlayerInfoPopup::GetPlayerController()
{
	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		return Cast<ACCPlayerController>(World->GetFirstPlayerController());;
	}
	return nullptr;
}

void UUW_PlayerInfoPopup::NativeConstruct()
{
	if (Button_Confirm)
	{
		Button_Confirm->OnClicked.AddDynamic(this, &UUW_PlayerInfoPopup::PlayerInfoRenewButtonCallback);
	}

	if (Button_Exit)
	{
		Button_Exit->OnClicked.AddDynamic(this, &UUW_PlayerInfoPopup::PlayerInfoExitCallback);
	}

	NetworkManager = Cast<UCCNetworkManager>(\
		UGameplayStatics::GetGameInstance(GetWorld()));
	if (!NetworkManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("networkmanager is null pointer"));
	}
}

void UUW_PlayerInfoPopup::SetPlayerInfoUI(const FString& msg)
{
	ScrollBox_PlayerInfo->ClearChildren();

	UTextBlock* NewTextBlock = NewObject<UTextBlock>(ScrollBox_PlayerInfo);
	NewTextBlock->SetText(FText::FromString(msg));

	ScrollBox_PlayerInfo->AddChild(NewTextBlock);
}
