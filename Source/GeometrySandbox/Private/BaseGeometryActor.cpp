// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGeometryActor.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseGeometry, All, All)

// Sets default values
ABaseGeometryActor::ABaseGeometryActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseGeometryActor::BeginPlay()
{
	Super::BeginPlay();

	// PrintStringTypes();
	// PrintTypes();
}

// Called every frame
void ABaseGeometryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseGeometryActor::PrintTypes()
{
	int32 WeaponsNum = 4;
	int32 KillsNum = 7;
	float Health = 34.435235f;
	bool bIsDead = false;
	bool bHasWeapon = true;

	UE_LOG(LogTemp, Display, TEXT("Weapons numb: %i, kills num: %i"), WeaponsNum, KillsNum)
	UE_LOG(LogTemp, Display, TEXT("Health: %f"), Health)
	UE_LOG(LogTemp, Display, TEXT("Health: %.2f"), Health)
	UE_LOG(LogTemp, Display, TEXT("Is dead: %d"), bIsDead)
	UE_LOG(LogTemp, Display, TEXT("Has weapon: %d"), static_cast<int>(bHasWeapon))
}

void ABaseGeometryActor::PrintStringTypes()
{
	FString Name = "John Connor";
	UE_LOG(LogBaseGeometry, Display, TEXT("Name: %s"), *Name)

	int32 WeaponsNum = 4;
	float Health = 34.435235f;
	bool bIsDead = false;
	
	FString WeaponsNumStr = "Weapons num = " + FString::FromInt(WeaponsNum);
	FString HealthStr = "Health = " + FString::SanitizeFloat(Health);
	FString IsDeadStr = "Is dead = " + FString(bIsDead ? "True" : "False");

	FString Stat = FString::Printf(TEXT(" \n == All Stat == \n %s \n %s \n %s "), *WeaponsNumStr, *HealthStr, *IsDeadStr);
	UE_LOG(LogBaseGeometry, Warning, TEXT("%s"), *Stat)

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Magenta, Name);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, Name, true, FVector2D(1.5f, 1.5f));
}

