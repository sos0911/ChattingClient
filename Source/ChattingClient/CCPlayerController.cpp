// Fill out your copyright notice in the Description page of Project Settings.

#include "CCPlayerController.h"
#include "CCNetworkManager.h"
#include "UW_Login.h"
#include "UW_WaitRoom.h"
#include "UW_PlayerInfoPopup.h"
#include "UW_RoomInfoPopup.h"

ACCPlayerController::ACCPlayerController()
{
	/*static ConstructorHelpers::FClassFinder<UUW_Login> WB_Login(TEXT(\
		"/Game/UI/BP_Login"));
	if (WB_Login.Succeeded())
	{
		LoginUIClass = WB_Login.Class;
	}
	static ConstructorHelpers::FClassFinder<UUW_WaitRoom> WB_WaitRoom(TEXT(\
		"/Game/UI/BP_WaitRoom"));
	if (WB_WaitRoom.Succeeded())
	{
		WaitRoomUIClass = WB_WaitRoom.Class;
	}
	static ConstructorHelpers::FClassFinder<UUW_PlayerInfoPopup> WB_PlayerInfo(TEXT(\
		"/Game/UI/BP_PlayerInfo_Popup"));
	if (WB_PlayerInfo.Succeeded())
	{
		PlayerInfoUIClass = WB_PlayerInfo.Class;
	}*/
}

void ACCPlayerController::BeginPlay()
{
	Super::BeginPlay();

	LoginUIObject = Cast<UUW_Login>(FindAndMakeClassObjects(WB_Login_Path));
	if (LoginUIObject)
	{
		LoginUIObject->AddToViewport();
	}


	/*if (LoginUIClass)
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

	if (PlayerInfoUIClass)
	{
		PlayerInfoUIObject = CreateWidget<UUW_PlayerInfoPopup>(GetWorld(), PlayerInfoUIClass);
	}*/

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

void ACCPlayerController::SetPlayerListUI(const FString& msg)
{
	if (!WaitRoomUIObject)
	{
		return;
	}
	//auto WaitRoomUIObject = Cast<UUW_WaitRoom>(FindAndMakeClassObjects(WB_WaitRoom_Path));
	WaitRoomUIObject->SetPlayerListUI(msg);
}

void ACCPlayerController::SetRoomListUI(const FString& msg)
{
	if (!WaitRoomUIObject)
	{
		return;
	}
	//auto WaitRoomUIObject = Cast<UUW_WaitRoom>(FindAndMakeClassObjects(WB_WaitRoom_Path));
	WaitRoomUIObject->SetRoomListUI(msg);
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

UUserWidget* ACCPlayerController::FindAndMakeClassObjects(FString& Path)
{
	TSubclassOf<UUserWidget> widget = ConstructorHelpersInternal::FindOrLoadClass(Path, UUserWidget::StaticClass());
	UUserWidget* UserWidgetObject = CreateWidget<UUserWidget>(GetWorld(), widget);
	return UserWidgetObject;
}
