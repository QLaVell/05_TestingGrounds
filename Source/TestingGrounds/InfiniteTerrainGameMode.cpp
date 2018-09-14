// Fill out your copyright notice in the Description page of Project Settings.

#include "InfiniteTerrainGameMode.h"
#include "AI/Navigation/NavMeshBoundsVolume.h"
#include "EngineUtils.h"

void AInfiniteTerrainGameMode::PopulateBoundsVolumePool() {
	TActorIterator<ANavMeshBoundsVolume> VolumeIterator(GetWorld());
	while (VolumeIterator) {
		AddToPool(*VolumeIterator);
		++VolumeIterator;
	}
}

void AInfiniteTerrainGameMode::AddToPool(ANavMeshBoundsVolume* VolumeToAdd) {
	UE_LOG(LogTemp, Warning, TEXT("NavMeshBoundsVolume found: %s"), *VolumeToAdd->GetName())
}