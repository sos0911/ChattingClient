// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

constexpr int RECVBUFSIZE = 1024;

// donghyun : 아래 msg들은 실제로 오는 메세지의 일부분일 수 있음
extern FString LoginSuccessMsg;
extern FString LoginFailMsg;
extern FString PlayerListMsg;
extern FString JoinRoomSuccessMsg;
extern FString JoinRoomFailMsg;
extern FString FailToConnectMsg;
extern FString FailToExecuteQuery;

//대화방이 개설되었습니다.
//자기 자신에게는 보낼 수 없습니다.
//님의 쪽지
//쪽지를 보냈습니다
//님을 찾을 수 없습니다.
//존재하지 않는 대화방입니다.
//님을 찾을 수 없습니다.
//님은 현재 번 채팅방에 있습니다.
//님은 현재 대기실에 있습니다.
//번 방은 존재하지 않는 대화방입니다.
//방 인원 초과로 입장이 불가능합니다.
//님이 들어오셨습니다.
//님이 나가셨습니다.
//채팅방에서 나왔습니다.
