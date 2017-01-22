// Fill out your copyright notice in the Description page of Project Settings.

#include "GGJ17Alpha.h"
#include "GGJPlayer.h"


// Sets default values
AGGJPlayer::AGGJPlayer()
{
	MaxStamina = 100.0f;

	MovementSpeed = 500.0f;
	Stamina = MaxStamina;

	bUsingSpecial = false;

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeLocationAndRotation(FVector(0, 0, 50), FRotator(0, 0, 0));
	SpringArm->TargetArmLength = 500;
	SpringArm->bEnableCameraLag = false;
	SpringArm->CameraLagSpeed = 3;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(RootComponent);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Gets stamina value
float AGGJPlayer::GetStamina()
{
	return Stamina;
}

// Gets the max stamina
float AGGJPlayer::GetMaxStamina()
{
	return MaxStamina;
}

// Converts Stamina value to a normalized value (0 - 1)
float AGGJPlayer::GetStaminaPercent()
{
	float Ratio = Stamina / MaxStamina;
	return Ratio;
}

// Increases Stamina value
void AGGJPlayer::IncreaseStamina(float value)
{
	float NewStamina = Stamina + value;
	Stamina = FMath::Clamp(Stamina, 0.0f, MaxStamina);
}

// Decreases Stamina value
void AGGJPlayer::DecreaseStamina(float value)
{
	float NewStamina = Stamina - value;
	Stamina = FMath::Clamp(Stamina, 0.0f, MaxStamina);
}

// Checks to see if player is using special vision
bool AGGJPlayer::IsUsingSpecial()
{
	return bUsingSpecial;
}

// Toggle Special on/off
void AGGJPlayer::EnableSpecial(bool value)
{
	bUsingSpecial = value;
}

// Called when the game starts or when spawned
void AGGJPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGGJPlayer::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	//Rotate our actor's yaw, which will turn our camera because we're attached to it
	{
		FRotator NewRotation = GetActorRotation();
		NewRotation.Yaw += CameraInput.X;
		SetActorRotation(NewRotation);
	}

	//Rotate our camera's pitch, but limit it so we're always looking downward
	{
		FRotator NewRotation = SpringArm->GetComponentRotation();
		NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + CameraInput.Y, -80.0f, -15.0f);
		SpringArm->SetWorldRotation(NewRotation);
	}

	if (!MovementInput.IsZero())
	{
		//Scale our movement input axis values by 100 units per second
		MovementInput = MovementInput.SafeNormal() * MovementSpeed;
		FVector NewLocation = GetActorLocation();
		NewLocation += GetActorForwardVector() * MovementInput.X * DeltaTime;
		NewLocation += GetActorRightVector() * MovementInput.Y * DeltaTime;
		SetActorLocation(NewLocation);
	}
}

float AGGJPlayer::GetMovementSpeed()
{
	return MovementSpeed;
}

void AGGJPlayer::MoveForward(float value)
{
	MovementInput.X = FMath::Clamp(value, -1.0f, 1.0f);

}

void AGGJPlayer::MoveRight(float value)
{
	MovementInput.Y = FMath::Clamp(value, -1.0f, 1.0f);

}
void AGGJPlayer::CameraPitch(float value)
{
	CameraInput.Y = value;
}

void AGGJPlayer::CameraYaw(float value)
{
	CameraInput.X += value;
}

// Called to bind functionality to input
void AGGJPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AGGJPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGGJPlayer::MoveRight);
	PlayerInputComponent->BindAxis("CameraPitch", this, &AGGJPlayer::CameraPitch);
	PlayerInputComponent->BindAxis("CameraYaw", this, &AGGJPlayer::CameraYaw);

}

