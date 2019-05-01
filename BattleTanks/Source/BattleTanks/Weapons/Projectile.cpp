// Fill out your copyright notice in the Description page of Project Settings.

#include "../BattleTanks.h"
#include "Projectile.h"


AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	/* Construct the collision mesh. */
	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);

	/* Construct the Launch Blast particle system. */
	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform); // TODO to new API

	/* Construct the Projectile Movement component. */
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	ProjectileMovement->bAutoActivate = false;

	/* Construct the Impact Blast particle system. */
	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->bAutoActivate = false;

	ImpactExplosion = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Explosion"));
	ImpactExplosion->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactExplosion->bAutoActivate = false;

	/* Construct the Explosion Force component. */
	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
	ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	/* Bind the OnComponentHit delegate to our Projectile so we can process hit events. */
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

}

void AProjectile::LaunchProjectile(float Speed)
{
	/* Set the veolicty based on speed and activate. */
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovement->Activate();

	/* Missle mesh came in imported the wrong way around, this flips it so it points the danger pointy the right way */
	CollisionMesh->AddLocalRotation(FRotator(180, 0, 0));

	/* Move the projectile trail (LaunchBlast) back 5 cm to the back of the projectile so it doesn't appear in the middle of the missle. */
	LaunchBlast->SetRelativeLocation(FVector(5, 0, 0));

	/* Spawn & Play the smoke trail sound. */
	ProjectileMovementSoundAudio = UGameplayStatics::SpawnSoundAttached(ProjectileMovementSound, RootComponent, NAME_None, FVector::ZeroVector, EAttachLocation::SnapToTarget, true);
	ProjectileMovementSoundAudio->Activate();
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	/* Deactivate the Launch Blast ( the projectile trail ), activate the ImpactBlast
	and pulse once the explosino force to move whatever was hit. */
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();
	ImpactExplosion->Activate();
	ExplosionForce->FireImpulse();
	
	/* Set the root component to the Impact Blast so that we can delete the collision mesh. */
	SetRootComponent(ImpactBlast);
	
	/* Delete the collision mesh so that we don't get snagged on impacted projectiles in the world.*/
	CollisionMesh->DestroyComponent();

	/* Apply a radial damage, making it the same radius as the explosion force for consistency. 
	Currently this is set up to damage all actors. */
	UGameplayStatics::ApplyRadialDamage(
		this,
		ProjectileDamage,
		GetActorLocation(),
		ExplosionForce->Radius,
		UDamageType::StaticClass(),
		TArray<AActor*>()); // damage all actors

	/* Timer that once expired destroys the projectile to garbage collect it from the world. */
	FTimerHandle Timer;
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &AProjectile::OnTimerExpire, DestroyDelay, false);

	/* Play impact sound. */
	//UGameplayStatics::SpawnSoundAttached(SoundOnImpact, RootComponent, NAME_None, FVector::ZeroVector, EAttachLocation::SnapToTarget, true);

	/* Stop projectile trail sound. */
	ProjectileMovementSoundAudio->Deactivate();
}

/* Garbage collection for projectiles. */
void AProjectile::OnTimerExpire()
{
	Destroy();
}
