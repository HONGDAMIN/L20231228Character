// Fill out your copyright notice in the Description page of Project Settings.


#include "BBC.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h" //향상된 입력을 사용하기 위해 추가
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABBC::ABBC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);	

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	//캐릭터 초기 위치값 지정
	GetMesh()->SetRelativeLocation(FVector(0, 0, -GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));
	//캐릭터 초기 회전값(Pitch,Yaw,Roll)
	GetMesh()->SetRelativeRotation(FRotator(0, -90.0f, 0));

}


// Called when the game starts or when spawned
void ABBC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABBC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input

// 아래의 함수를 통해서 플레이어 입력 요소에 입력 바인딩을 설정.
void ABBC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// 형변환을 통해서 PlayerInputComponent 를 UEnhancedInputComponent 형으로 캐스팅.
	// 즉, 향상된 입력 기능을 제공하는 커스텀 입력 컴포넌트 클래스인 UEnhancedInputComponent로 캐스팅.
	
	UEnhancedInputComponent* UEIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (UEIC)
	{
		// 상속받은 ACharacter 에 Jump 관련한 함수는 이미 있기 때문에 ABBC::Jump 함수를 만들지 않아도 된다.
		// 아래처럼 우리가 만든 액션에 바인딩을 걸어주고 호출시키는 코드를 작성.
		UEIC->BindAction(IA_Jump, ETriggerEvent::Started, this, &ABBC::Jump);
		UEIC->BindAction(IA_Jump, ETriggerEvent::Completed, this, &ABBC::StopJumping);

		UEIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ABBC::Move);
		UEIC->BindAction(IA_Look, ETriggerEvent::Triggered, this, &ABBC::Look);
	}
}


void ABBC::Move(const FInputActionValue& Value)
{
	//입력 값 Valu로 부터 2축(X,Y)형태의 값을 추출.
	FVector2D Dir = Value.Get<FVector2D>();

	//현재 컨트롤러의 회전 값을 가져와서 이를 Yaw 값만 사용해 캐릭터가 바라보는 방향을 구한다.
	//즉, Yaw에 해당하는 값 외에는 0을 넣은 이유는 Yaw값만을 구하기 위해서이다.
	FRotator CameraRotaion = GetControlRotation();
	FRotator DirectionRotation = FRotator(0, CameraRotaion.Yaw, 0);

	//이제 가져온 값을 바탕으로 캐릭터가 전진하는 방향의 벡터값과 오른쪽으로 이동하는 벡터값을 구하게된다.
	FVector FowardVector = UKismetMathLibrary::GetForwardVector(DirectionRotation);
	FVector RightVector = UKismetMathLibrary::GetRightVector(DirectionRotation);

	//최종적으로 전진 방향의 벡터와 전후 이동 입력 Dir.Y 를 곱해서 이동값을 추가해준다.
	//두번째 코드는 우측 방향의 벡터와 좌우 이동 입력 Dir.X를 곱해서 이동값을 추가해준다.

	AddMovementInput(FowardVector, Dir.Y);
	AddMovementInput(RightVector, Dir.X);
}

void ABBC::Look(const FInputActionValue& Value)
{
	//위처럼 이번에는 캐릭터의 회전을 위해서 입력 값으로 부터 값을 추출한다.
	FVector2D Rotation = Value.Get<FVector2D>();

	//이후에 아래처럼 Yaw에 대한, Pitch에 대한 이동값을 추출한다.
	AddControllerYawInput(Rotation.X);
	AddControllerPitchInput(Rotation.Y);
}


