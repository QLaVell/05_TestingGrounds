// Fill out your copyright notice in the Description page of Project Settings.

#include "InfiniteTerrainGameMode.h"
#include "AI/Navigation/NavMeshBoundsVolume.h"
#include "EngineUtils.h"
#include "ActorPool.h"

AInfiniteTerrainGameMode::AInfiniteTerrainGameMode() {
	NavMeshBoundsVolumePool = CreateDefaultSubobject<UActorPool>(FName("Nav Mesh Bounds Volume Pool"));

	Score = 0;
}

void AInfiniteTerrainGameMode::PopulateBoundsVolumePool() {
	TActorIterator<ANavMeshBoundsVolume> VolumeIterator(GetWorld());
	while (VolumeIterator) {
		AddToPool(*VolumeIterator);
		++VolumeIterator;
	}
}

void AInfiniteTerrainGameMode::AddToPool(ANavMeshBoundsVolume* VolumeToAdd) {
	NavMeshBoundsVolumePool->Add(VolumeToAdd);
}

void AInfiniteTerrainGameMode::NewTileConquered() {
	Score++;
}

int AInfiniteTerrainGameMode::GetScore() const {
	return Score;
}