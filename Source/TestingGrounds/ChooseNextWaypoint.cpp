// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrollingGuard.h" // TODO Remove coupling

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	// Get the patrol points
	APatrollingGuard* PatrollingGuard = Cast<APatrollingGuard>(OwnerComp.GetAIOwner()->GetPawn());
	TArray<AActor*> PatrolPoints = PatrollingGuard->PatrolPointsCPP;

	// Set the next waypoint
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	int32 Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);

	// TODO Protect against empty patrol routes

	// Cycle the index
	int32 NextIndex = (Index + 1) % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);

	//UE_LOG(LogTemp, Warning, TEXT("Waypoint: %s"), *NextWaypoint->GetName())
	return EBTNodeResult::Succeeded;
}


