// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGeometryActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnColorChanged, const FLinearColor&, Color, const FString&, Name);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimerFinished, AActor*);

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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	EMovementType MovementType = EMovementType::Static;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Amplitude = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Frequency = 2.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design")
	FLinearColor Color = FLinearColor::Black;

	UPROPERTY(EditAnywhere, Category = "Design")
	float TimerRate = 3.0f;

	FString ToString() const
	{
		FString MoveTypeStr = MovementType == EMovementType::Sin ? "Sin" : "Static";
		FString ColorStr = Color.ToString();

		FString Formatted = FString::Printf(
			TEXT(" === GEOMETRY DATA === \n MoveType: %s \n Amplitude: %f \n Frequency: %f \n Color: %s \n TimerRate: %f \n"),
			*MoveTypeStr, Amplitude, Frequency, *ColorStr, TimerRate);
		return Formatted;
	}
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

	UPROPERTY(BlueprintAssignable)
	FOnColorChanged OnColorChanged;
	
	FOnTimerFinished OnTimerFinished;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Geometry Data")
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
	
	/** Overridable function called whenever this actor is being removed from a level */
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void SetGeometryData(const FGeometryData& Data) { GeometryData = Data; };

	UFUNCTION(BLueprintCallable)
	FGeometryData GetGeometryData() const { return GeometryData; };
	
private:
	FVector InitialLocation;
	FTimerHandle TimerHandle;

	const int32 MaxTimerCount = 5;
	int32 TimerCount = 0;
	
	void SetColor(const FLinearColor& Color);
	
	void HandleMovement();
	
	/** Print transform data of this actor using UE_LOG(). */
	void PrintTransform();
	
	/** Print types with UE_LOG(). */
	void PrintTypes();

	/** Print FString types with UE_LOG(). */
	void PrintStringTypes();

	void OnTimerFired();

};
