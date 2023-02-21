// Fill out your copyright notice in the Description page of Project Settings.

#include "CCPlayerController.h"
#include "CCNetworkManager.h"
#include "UW_Login.h"
#include "UW_WaitRoom.h"

ACCPlayerController::ACCPlayerController()
{
	static ConstructorHelpers::FClassFinder<UUW_Login> WB_Login(TEXT(\
		"/Game/UI/BP_Login"));
	if (WB_Login.Succeeded())
	{
		LoginUIClass = WB_Login.Class;
	}
	static ConstructorHelpers::FClassFinder<UUW_WaitRoom> WB_WaitRoom(TEXT(\
		"/Game/UI/BP_WaitRoom"));
	if (WB_Login.Succeeded())
	{
		WaitRoomUIClass = WB_WaitRoom.Class;
	}
}

void ACCPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (LoginUIClass)
	{
		LoginUIObject = CreateWidget<UUW_Login>(GetWorld(), LoginUIClass);
		if (LoginUIObject)
		{
			LoginUIObject->AddToViewport();
		}
	}

	if (WaitRoomUIClass)
	{
		WaitRoomUIObject = CreateWidget<UUW_WaitRoom>(GetWorld(), WaitRoomUIClass);
	}

	NetworkManagerPtr = Cast<UCCNetworkManager>(\
		UGameplayStatics::GetGameInstance(GetWorld()));
	if (!NetworkManagerPtr)
	{
		UE_LOG(LogTemp, Warning, TEXT("networkmanager is null pointer"));
	}

	CCPlayerStatePtr = Cast<ACCPlayerState>(PlayerState);
}

//void ACCPlayerController::SetupInputComponent()
//{
//	Super::SetupInputComponent();
//}

void ACCPlayerController::PlayerTick(float Deltatime)
{
	NetworkManagerPtr->RecvMsg();
}

void ACCPlayerController::SetPlayerState(const EPlayerState& StateFlag)
{
	if (!CCPlayerStatePtr)
	{
		return;
	}

	CCPlayerStatePtr->EnumPlayerState = StateFlag;
}

void ACCPlayerController::SetConntectedUI()
{
	// donghyun : 연결이 성공했으므로 로그인 UI로 변경
	LoginUIObject->SetConnectedUI();
}

void ACCPlayerController::SetLoginUI()
{
	// donghyun : 로그인이 성공했으므로 대기실 UI로 변경
	LoginUIObject->RemoveFromViewport();
	WaitRoomUIObject->AddToViewport();
}