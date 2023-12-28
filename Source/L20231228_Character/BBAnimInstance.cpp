// Fill out your copyright notice in the Description page of Project Settings.


#include "BBAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UBBAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	//Super는 부모 함수를 호출해서 재정의 하기 위한 작업.
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	//해당 폰의 소유자가 현자 Owner가 맞는지 가져와서 검증 후에 작업을 한다.
	ACharacter* MyCharacter = Cast<ACharacter>(TryGetPawnOwner());
	if (IsValid(MyCharacter))
	{
		//Velocity는 방향을 포함한 속도이며, 스칼라는 속도만 가지고 있다.
		//그래서 아래처럼 해서 속도와 방향을 구하도록 해준다.
		// Size2D로 하면 Z축을 제외하고 속도를 계산함
		Speed = MyCharacter->GetCharacterMovement()->Velocity.Size2D();
	}
}
