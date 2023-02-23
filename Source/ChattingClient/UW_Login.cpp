// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_Login.h"
#include "FServerProtocol.h"

#include "CCNetworkManager.h"

#include "CCNetworkManager.h"
#include "CCPlayerController.h"
#include "CCPlayerState.h"
#include "Kismet/GameplayStatics.h"

#include "Runtime/UMG/Public/Components/EditableTextBox.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"

void UUW_Login::SummitButtonCallback()
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

	// donghyun : 1. ���� �κ�
	if (PlayerState->EnumPlayerState == EPlayerState::UnConnected)
	{
		if (!NetworkManager || !PlayerControllerPtr)
		{
			return;
		}

		NetworkManager->Initialize(Input_IP->GetText().ToString(), Input_Port->GetText().ToString());
	}
	// donghyun : 2. �α��� �κ�
	else if(PlayerState->EnumPlayerState == EPlayerState::Connected)
	{
		// donghyun : UI�� �ٲ��ִ� ���� �����κ��� �г��� �ߺ� ������ �� �� ����
		NetworkManager->sendMsg(NetworkManager->FormatLoginComm(Input_Nickname->GetText().ToString()));
		UE_LOG(LogTemp, Warning, TEXT("Login message sent"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("login error!"));
	}
}

ACCPlayerController* UUW_Login::GetPlayerController()
{
	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		return Cast<ACCPlayerController>(World->GetFirstPlayerController());
	}
	return nullptr;
}

void UUW_Login::NativeConstruct()
{
	if (Button_Submit)
	{
		Button_Submit->OnClicked.AddDynamic(this, &UUW_Login::SummitButtonCallback);
	}
	NetworkManager = Cast<UCCNetworkManager>(\
		UGameplayStatics::GetGameInstance(GetWorld()));
	if (!NetworkManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("networkmanager is null pointer"));
	}
}

void UUW_Login::SetConnectedUI()
{
	Text_IP->SetVisibility(ESlateVisibility::Hidden);
	Text_Port->SetVisibility(ESlateVisibility::Hidden);
	Input_IP->SetVisibility(ESlateVisibility::Hidden);
	Input_Port->SetVisibility(ESlateVisibility::Hidden);

	Text_Nickname->SetVisibility(ESlateVisibility::Visible);
	Input_Nickname->SetVisibility(ESlateVisibility::Visible);
}

void UUW_Login::SetLoginNotifyUI(const FString& msg)
{
	Text_Notify->SetText(FText::FromString(msg));
}
