// Fill out your copyright notice in the Description page of Project Settings.

#include "CCPlayerController.h"
#include "CCNetworkManager.h"
#include "UW_Login.h"
#include "UW_WaitRoom.h"
#include "UW_PlayerInfoPopup.h"
#include "UW_RoomInfoPopup.h"
#include "UW_JoinRoomPopup.h"
#include "UW_MakeRoomPopup.h"
#include "UW_ChattingRoom.h"


ACCPlayerController::ACCPlayerController()
{
}

void ACCPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetShowMouseCursor(true);
	LoginUIObject = Cast<UUW_Login>(FindAndMakeClassObjects(WB_Login_Path));
	if (LoginUIObject)
	{
		LoginUIObject->AddToViewport();
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

	// donghyun : 이전 플레이어 상태 캐싱
	CCPlayerStatePtr->BefEnumPlayerState = CCPlayerStatePtr->EnumPlayerState;
	CCPlayerStatePtr->EnumPlayerState = StateFlag;
}

void ACCPlayerController::UndoPlayerState()
{
	if (!CCPlayerStatePtr)
	{
		return;
	}

	CCPlayerStatePtr->EnumPlayerState = CCPlayerStatePtr->BefEnumPlayerState;
}

EPlayerState& ACCPlayerController::GetPlayerState()
{
	// TODO: 여기에 return 문을 삽입합니다.
	return CCPlayerStatePtr->EnumPlayerState;
}

void ACCPlayerController::SetConntectedUI()
{
	// donghyun : 연결이 성공했으므로 로그인 UI로 변경
	//auto LoginUIObject = Cast<UUW_Login>(FindAndMakeClassObjects(WB_Login_Path));
	if (!LoginUIObject)
	{
		return;
	}
	//auto LoginUIObject = Cast<UUW_Login>(FindAndMakeClassObjects(WB_Login_Path));
	LoginUIObject->SetConnectedUI();
}

void ACCPlayerController::SetLoginUI()
{
	// donghyun : 로그인이 성공했으므로 대기실 UI로 변경
	if (!LoginUIObject)
	{
		return;
	}
	//auto LoginUIObject = Cast<UUW_Login>(FindAndMakeClassObjects(WB_Login_Path));
	LoginUIObject->RemoveFromViewport();
	WaitRoomUIObject = Cast<UUW_WaitRoom>(FindAndMakeClassObjects(WB_WaitRoom_Path));
	WaitRoomUIObject->AddToViewport();
}

void ACCPlayerController::SetInfoListUI(const FString& msg)
{
	if (!WaitRoomUIObject)
	{
		return;
	}
	//auto WaitRoomUIObject = Cast<UUW_WaitRoom>(FindAndMakeClassObjects(WB_WaitRoom_Path));
	WaitRoomUIObject->SetInfoListUI(msg);
}

void ACCPlayerController::SetPlayerInfoUI(const FString& msg)
{
	//PlayerInfoUIObject = Cast<UUW_PlayerInfoPopup>(FindAndMakeClassObjects(WB_PlayerInfo_Path));
	if (!PlayerInfoUIObject)
	{
		return;
	}
	PlayerInfoUIObject->SetPlayerInfoUI(msg);
}

void ACCPlayerController::MakePlayerInfoPopup()
{
	PlayerInfoUIObject = Cast<UUW_PlayerInfoPopup>(FindAndMakeClassObjects(WB_PlayerInfo_Path));
	if (!PlayerInfoUIObject)
	{
		return;
	}
	PlayerInfoUIObject->AddToViewport();
}

void ACCPlayerController::MakeRoomInfoPopup()
{
	RoomInfoUIObject = Cast<UUW_RoomInfoPopup>(FindAndMakeClassObjects(WB_RoomInfo_Path));
	if (!RoomInfoUIObject)
	{
		return;
	}
	RoomInfoUIObject->AddToViewport();
}

void ACCPlayerController::SetRoomInfoUI(const FString& msg)
{
	if (!RoomInfoUIObject)
	{
		return;
	}
	RoomInfoUIObject->SetRoomInfoUI(msg);
}

void ACCPlayerController::MakeRoomPopup()
{
	MakeRoomUIObject = Cast<UUW_MakeRoomPopup>(FindAndMakeClassObjects(WB_MakeRoom_Path));
	if (!MakeRoomUIObject)
	{
		return;
	}
	MakeRoomUIObject->AddToViewport();
}

void ACCPlayerController::RenewChattingRoomLog(const FString& msg)
{
	if (!ChattingRoomUIObject)
	{
		return;
	}
	ChattingRoomUIObject->RenewChattingRoomLog(msg);
}

void ACCPlayerController::WaitRoomToChattingRoom()
{
	SetPlayerState(EPlayerState::Chatting);

	if (!WaitRoomUIObject)
	{
		return;
	}
	WaitRoomUIObject->RemoveFromViewport();

	ChattingRoomUIObject = Cast<UUW_ChattingRoom>(FindAndMakeClassObjects(WB_ChattingRoom_Path));
	if (!ChattingRoomUIObject)
	{
		return;
	}
	ChattingRoomUIObject->AddToViewport();
}

void ACCPlayerController::JoinRoomPopup()
{
	JoinRoomUIObject = Cast<UUW_JoinRoomPopup>(FindAndMakeClassObjects(WB_JoinRoom_Path));
	if (!JoinRoomUIObject)
	{
		return;
	}
	JoinRoomUIObject->AddToViewport();
}

void ACCPlayerController::ChattingRoomToWaitRoom()
{
	SetPlayerState(EPlayerState::Login);
	WaitRoomUIObject = Cast<UUW_WaitRoom>(FindAndMakeClassObjects(WB_WaitRoom_Path));
	if (!WaitRoomUIObject)
	{
		return;
	}
	WaitRoomUIObject->AddToViewport();
}

void ACCPlayerController::SetJoinRoomResultUI(const FString& msg)
{
	// donghyun : 상황에 따라 return
	if (!JoinRoomUIObject)
	{
		return;
	}
	JoinRoomUIObject->SetJoinRoomResultUI(msg);
}

void ACCPlayerController::RemoveJoinRoomPopup()
{
	if (!JoinRoomUIObject)
	{
		return;
	}
	JoinRoomUIObject->RemoveFromViewport();
}

void ACCPlayerController::SetWhisperUI(const FString& msg)
{
	if (!WaitRoomUIObject)
	{
		return;
	}
	WaitRoomUIObject->SetWhisperUI(msg);
}

void ACCPlayerController::SetLoginNotifyUI(const FString& msg)
{
	if(!LoginUIObject)
	{
		return;
	}
	LoginUIObject->SetLoginNotifyUI(msg);
}

UUserWidget* ACCPlayerController::FindAndMakeClassObjects(FString& Path)
{
	TSubclassOf<UUserWidget> widget = ConstructorHelpersInternal::FindOrLoadClass(Path, UUserWidget::StaticClass());
	UUserWidget* UserWidgetObject = CreateWidget<UUserWidget>(GetWorld(), widget);
	return UserWidgetObject;
}
