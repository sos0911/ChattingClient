// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_Login.h"

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

	// donghyun : 1. 연결 부분
	if (PlayerState->PlayerState == EPlayerState::Connected)
	{
		if (NetworkManager)
		{
			/*int Itemnumber = 2;
			TMap<FString, FStringFormatArg> args;
			args.Emplace(Input_IP->GetText().ToString(), \
				Input_Port->GetText().ToString());
			FString msg = FString::Format(TEXT("o {} {}"), args);*/

			NetworkManager->Initialize(Input_IP->GetText().ToString(), Input_Port->GetText().ToString());

			Text_IP->SetVisibility(ESlateVisibility::Hidden);
			Input_IP->SetVisibility(ESlateVisibility::Hidden);
			Text_Port->SetVisibility(ESlateVisibility::Hidden);
			Input_Port->SetVisibility(ESlateVisibility::Hidden);

			Text_Nickname->SetVisibility(ESlateVisibility::Visible);
			Input_Nickname->SetVisibility(ESlateVisibility::Visible);

			/*FString msg = FString::Printf(TEXT("o %s %s"), *(Input_IP->GetText().ToString()), \
				* (Input_Port->GetText().ToString()));
			NetworkManager->sendMsg(msg);*/
		}
	}
	// donghyun : 2. 로그인 부분
	else if(PlayerState->PlayerState == EPlayerState::Login)
	{
		UE_LOG(LogTemp, Warning, TEXT("Login message sent"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("login error!"));
	}
}

APlayerController* UUW_Login::GetPlayerController()
{
	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		return World->GetFirstPlayerController();
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
