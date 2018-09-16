// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"


USTRUCT()
struct FSpawnPosition {
	GENERATED_USTRUCT_BODY()

	FVector Location;
	float YawRotation;
	float Scale;
};

USTRUCT(BlueprintType)
struct FAISpawnParams {
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Params")
	int MinSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Params")
	int MaxSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Params")
	float Radius;

	FAISpawnParams() {
		MinSpawn = 1;
		MaxSpawn = 1;
		Radius = 500;
	}
};

USTRUCT(BlueprintType)
struct FObjectSpawnParams {
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Params")
	int MinSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Params")
	int MaxSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Params")
	float Radius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Params")
	float MinScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Params")
	float MaxScale;

	FObjectSpawnParams() {
		MinSpawn = 1;
		MaxSpawn = 1;
		Radius = 500;
		MinScale = 1.0f;
		MaxScale = 1.0f;
	}

	FObjectSpawnParams(FAISpawnParams SpawnParams) {
		MinSpawn = SpawnParams.MinSpawn;
		MaxSpawn = SpawnParams.MaxSpawn;
		Radius = SpawnParams.Radius;
		MinScale = 1.0f;
		MaxScale = 1.0f;
	}
};

class UActorPool;

UCLASS()
class TESTINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, Category = "Navigation")
	FVector NavigationBoundsOffset;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FVector MinExtent;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FVector MaxExtent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void PlaceActors(TSubclassOf<AActor> ToSpawn, FObjectSpawnParams SpawnParams);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void PlaceAIPawns(TSubclassOf<APawn> ToSpawn, FAISpawnParams SpawnParams);

	UFUNCTION(BlueprintCallable, Category = "Pool")
	void SetPool(UActorPool* InPool);

	
private:
	bool FindEmptyLocation(FVector& OutLocation, float Radius);

	template<class T>
	void RandomlyPlaceActors(TSubclassOf<T> ToSpawn, FObjectSpawnParams SpawnParams);

	void PlaceActor(TSubclassOf<AActor> ToSpawn, FSpawnPosition& SpawnPosition);

	void PlaceActor(TSubclassOf<APawn> ToSpawn, FSpawnPosition& SpawnPosition);

	bool CanSpawnAtLocation(FVector Location, float Radius);

	void PositionNavMeshBoundsVolume();

	UActorPool* Pool;

	AActor* NavMeshBoundsVolume;
};
