// Fill out your copyright notice in the Description page of Project Settings.


#include "BBPC.h"
#include "EnhancedInputSubsystems.h"

void ABBPC::BeginPlay()
{
	Super::BeginPlay();

	//아래의 코드는 Subsystem 으로부터 Localplayer 정보를 가져오는 코드.
	//ULocalPlayer 클래스로의 서브시스템을 가져와서 이곳에서 현재 로컬플레이어 정보를 가져온다.

	UEnhancedInputLocalPlayerSubsystem* SubSystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	//이후 얻은 서브시스템이 유효하고, DefaultIMC가 유효한 경우에 로직을 이어간다.
	if (SubSystem && DefaultIMC)
	{
		//MappingContext인 DefaultIMC를 서브 시스템에 추가한다.
		// 이후 이를 통해 입력 매핑을 효과적으로 정의하고 관리하게 되며, 0은 컨텍스트의 우선순위.
		//이는 더 높은 우선순위의 컨텍스트가 현재 활성화된 경우에만 해당 컨텍스트를 사용하게 한다.
		SubSystem->AddMappingContext(DefaultIMC, 0);
	}
}
