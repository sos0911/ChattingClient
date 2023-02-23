// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_Login.h"
#include "FServerProtocol.h"

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
	if (PlayerState->EnumPlayerState == EPlayerState::UnConnected)
	{
		if (!NetworkManager || !PlayerControllerPtr)
		{
			return;
		}

		/*int Itemnumber = 2;
		TMap<FString, FStringFormatArg> args;
		args.Emplace(Input_IP->GetText().ToString(), \
			Input_Port->GetText().ToString());
		FString msg = FString::Format(TEXT("o {} {}"), args);*/

		NetworkManager->Initialize(Input_IP->GetText().ToString(), Input_Port->GetText().ToString());

		//PlayerControllerPtr->SetConntectedUI();
		//SetConnectedUI();

		/*FString msg = FString::Printf(TEXT("o %s %s"), *(Input_IP->GetText().ToString()), \
			* (Input_Port->GetText().ToString()));
		NetworkManager->sendMsg(msg);*/
	}
	// donghyun : 2. 로그인 부분
	else if(PlayerState->EnumPlayerState == EPlayerState::Connected)
	{
		// donghyun : UI를 바꿔주는 것은 서버로부터 닉네임 중복 응답이 온 후 진행
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
