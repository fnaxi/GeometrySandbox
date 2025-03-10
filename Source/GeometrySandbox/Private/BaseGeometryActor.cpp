// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGeometryActor.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseGeometry, All, All)

// Sets default values
ABaseGeometryActor::ABaseGeometryActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	SetRootComponent(BaseMesh);
}

// Called when the game starts or when spawned
void ABaseGeometryActor::BeginPlay()
{
	Super::BeginPlay();

	InitialLocation = GetActorLocation();
	
	// PrintTransform();
	// PrintStringTypes();
	// PrintTypes();

	SetColor(GeometryData.Color);

	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABaseGeometryActor::OnTimerFired, GeometryData.TimerRate, true);
}

void ABaseGeometryActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	UE_LOG(LogBaseGeometry, Error, TEXT("Actor is dead %s"), *GetName())
}

// Called every frame
void ABaseGeometryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HandleMovement();
}

void ABaseGeometryActor::SetColor(const FLinearColor& Color)
{
	if (!BaseMesh) return;
	
	UMaterialInstanceDynamic* DynMaterial = BaseMesh->CreateAndSetMaterialInstanceDynamic(0);
	if (DynMaterial)
	{
		DynMaterial->SetVectorParameterValue("Color", Color);
	}
}

void ABaseGeometryActor::HandleMovement()
{
	switch (GeometryData.MovementType)
	{
	case EMovementType::Sin:
		{
			// z = z0 + amplitude * sin(freq * t)
			FVector CurrentLocation = GetActorLocation();
			if (GetWorld())
			{
				float Time = GetWorld()->GetTimeSeconds();
				CurrentLocation.Z = InitialLocation.Z + GeometryData.Amplitude * FMath::Sin(GeometryData.Frequency * Time);
				SetActorLocation(CurrentLocation);
			}
		}
		break;
	case EMovementType::Static:
		break;
	default: break;
	}
}

void ABaseGeometryActor::PrintTransform()
{
	FTransform Transform = GetActorTransform();

	FVector Location = Transform.GetLocation();
	FRotator Rotation = Transform.Rotator();
	FVector Scale = Transform.GetScale3D();

	UE_LOG(LogBaseGeometry, Warning, TEXT("Actor name %s"), *GetName());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Transform %s"), *Transform.ToString());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Location %s"), *Location.ToString());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Rotation %s"), *Rotation.ToString());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Scale %s"), *Scale.ToString());
	
	UE_LOG(LogBaseGeometry, Error, TEXT("Human transform %s"), *Transform.ToHumanReadableString());
}

void ABaseGeometryActor::PrintTypes()
{
	UE_LOG(LogBaseGeometry, Warning, TEXT("Actor name %s"), *GetName());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Weapons numb: %i, kills num: %i"), WeaponsNum, KillsNum)
	UE_LOG(LogBaseGeometry, Warning, TEXT("Health: %f"), Health)
	UE_LOG(LogBaseGeometry, Warning, TEXT("Is dead: %d"), bIsDead)
	UE_LOG(LogBaseGeometry, Warning, TEXT("Has weapon: %d"), static_cast<int>(bHasWeapon))
}

void ABaseGeometryActor::PrintStringTypes()
{
	FString Name = "John Connor";
	UE_LOG(LogBaseGeometry, Display, TEXT("Name: %s"), *Name)
	
	FString WeaponsNumStr = "Weapons num = " + FString::FromInt(WeaponsNum);
	FString HealthStr = "Health = " + FString::SanitizeFloat(Health);
	FString IsDeadStr = "Is dead = " + FString(bIsDead ? "True" : "False");

	FString Stat = FString::Printf(TEXT(" \n == All Stat == \n %s \n %s \n %s "), *WeaponsNumStr, *HealthStr, *IsDeadStr);
	UE_LOG(LogBaseGeometry, Warning, TEXT("%s"), *Stat)

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Magenta, Name);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, Name, true, FVector2D(1.5f, 1.5f));
	}
}

void ABaseGeometryActor::OnTimerFired()
{
	if (++TimerCount <= MaxTimerCount)
	{
		const FLinearColor NewColor = FLinearColor::MakeRandomColor();
		UE_LOG(LogBaseGeometry, Display, TEXT("Color to set up: %s"), *NewColor.ToString())
		SetColor(NewColor);
		OnColorChanged.Broadcast(NewColor, GetName());
	}
	else
	{
		UE_LOG(LogBaseGeometry, Warning, TEXT("Timer has been stopped!"))
		GetWorldTimerManager().ClearTimer(TimerHandle);
		OnTimerFinished.Broadcast(this);
	}
}

