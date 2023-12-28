// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BBAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class L20231228_CHARACTER_API UBBAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	//이 코드로 인하여 UAnimInstance에서 사용되는데 핵심인 NativeUpdateAnimation 함수를 재정의.
	// 이 함수를 이용해서 애니메이션을 프래임마다(Tick마다) 호출해서 업데이트.
	// 위와 같은 작업 덕분에 우리는 모션을 부드럽게 보는것이 가능.
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;


	//캐릭터의 이동속도를 담기 위한 변수 생성
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Stat")
	float Speed;
};
