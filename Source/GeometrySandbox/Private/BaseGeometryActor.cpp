// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGeometryActor.h"

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

	PrintTypes();
}

// Called every frame
void ABaseGeometryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseGeometryActor::PrintTypes()
{
	UE_LOG(LogTemp, Display, TEXT("Hello Unreal!"))
	UE_LOG(LogTemp, Warning, TEXT("Hello Unreal!"))
	UE_LOG(LogTemp, Error, TEXT("Hello Unreal!"))

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

