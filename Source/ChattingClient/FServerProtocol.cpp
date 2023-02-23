// Fill out your copyright notice in the Description page of Project Settings.


#include "FServerProtocol.h"

FString LoginSuccessMsg = TEXT("로그인 하였습니다.");
FString LoginFailMsg = TEXT("해당 이름은 사용할 수 없습니다");
FString PlayerListMsg = TEXT("-- 이용자 목록 --");

FString JoinRoomSuccessMsg = TEXT("님이 들어오셨습니다.");
FString JoinRoomFailMsg_Not = TEXT("번 방은 존재하지 않는 대화방입니다.");
FString JoinRoomFailMsg_Full = TEXT("방 인원 초과로 입장이 불가능합니다.");
FString FailToConnectMsg = TEXT("서버 연결 실패! 서버 상태나 입력한 번호를 확인하세요.");

FString FailToExecuteQuery = TEXT("명령어 인자를 정확히 입력해주세요");
