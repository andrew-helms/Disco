// Copyright Epic Games, Inc. All Rights Reserved.

#include "DiscsProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

ADiscsProjectile::ADiscsProjectile() 
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DiscMesh"));
	Mesh->AttachTo(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/Geometry/Meshes/Frisbee.Frisbee'"));
	if (MeshAsset.Succeeded())
	{
		Mesh->SetStaticMesh(MeshAsset.Object);
	}
	Mesh->OnComponentHit.AddDynamic(this, &ADiscsProjectile::OnHit);
	Mesh->BodyInstance.SetCollisionProfileName("Projectile");
	Mesh->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	Mesh->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = Mesh;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = Mesh;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 30000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 300.0f;
}

void ADiscsProjectile::Tick(float DeltaTime)
{
	float drag_scale = 0.995;
	FVector velocity = this->GetVelocity();
	velocity.X *= drag_scale;
	velocity.Y *= drag_scale;
	velocity.Z *= 0.97;
	ProjectileMovement->Velocity = velocity;
	float gravity_scale = 1;
	float speed = sqrt(velocity.X * velocity.X + velocity.Y * velocity.Y + velocity.Z * velocity.Z);
	gravity_scale -= (speed / 3000.0);
	if (gravity_scale < 0)
	{
		gravity_scale = 0;
	}
	ProjectileMovement->ProjectileGravityScale = gravity_scale;
}

void ADiscsProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100000.0f, GetActorLocation());

		Destroy();
	}
}