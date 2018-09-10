// Fill out your copyright notice in the Description page of Project Settings.

#include "Mannequin.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "../Weapons/Gun.h"


// Sets default values
AMannequin::AMannequin()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a CameraComponent
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetRootComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(7.864780, 7.897638, 65.000351); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeLocation = FVector(3.293318, -4.998758, -161.327179);
	Mesh1P->RelativeRotation = FRotator(1.9, -19.19, 5.2);

}

// Called when the game starts or when spawned
void AMannequin::BeginPlay()
{
	Super::BeginPlay();
	
	if (GunBluprint == NULL) {
		UE_LOG(LogTemp, Warning, TEXT("Gun blueprint missing."));
		return;
	}

	Gun = GetWorld()->SpawnActor<AGun>(GunBluprint);

	if (IsPlayerControlled()) {
		Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint")); // Attach gun mesh to first person grip point 
	} else {
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint")); // Attach gun mesh to third person grip point
	}
	Gun->AnimInstance1P = Mesh1P->GetAnimInstance();
	Gun->AnimInstance3P = GetMesh()->GetAnimInstance();

	if (InputComponent != NULL) {
		InputComponent->BindAction("Fire", IE_Pressed, this, &AMannequin::PullTrigger);
	}
}

// Called every frame
void AMannequin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMannequin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMannequin::UnPossessed() {
	Super::UnPossessed();

	if (Gun != NULL) {
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint")); // Attach gun mesh to third person grip point
	}
}

void AMannequin::PullTrigger() {
	Gun->OnFire();
	MakeNoise(1.0f, this, GetActorLocation());
}