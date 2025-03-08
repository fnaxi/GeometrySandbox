// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGeometryActor.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EMovementType : uint8
{
	Sin,
	Static
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct FGeometryData
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	EMovementType MovementType = EMovementType::Static;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	float Amplitude = 50.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Frequency = 2.0f;
	
	UPROPERTY(EditAnywhere, Category = "Design")
	FLinearColor Color = FLinearColor::Black;
};

/**
 *
 */
UCLASS()
class GEOMETRYSANDBOX_API ABaseGeometryActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseGeometryActor();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category = "Geometry Data")
	FGeometryData GeometryData;
	
	UPROPERTY(EditAnywhere, Category = "Weapon")
	int32 WeaponsNum = 4;

	UPROPERTY(EditDefaultsOnly, Category = "Stat")
	int32 KillsNum = 7;

	UPROPERTY(EditInstanceOnly, Category = "Health")
	float Health = 34.435235f;

	UPROPERTY(EditAnywhere, Category = "Health")
	bool bIsDead = false;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	bool bHasWeapon = true;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FVector InitialLocation;

	void SetColor(const FLinearColor& Color);
	
	void HandleMovement();
	
	/** Print transform data of this actor using UE_LOG(). */
	void PrintTransform();
	
	/** Print types with UE_LOG(). */
	void PrintTypes();

	/** Print FString types with UE_LOG(). */
	void PrintStringTypes();

};
