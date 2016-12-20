// Fill out your copyright notice in the Description page of Project Settings.

#include "../BattleTanks.h"
#include "../Public/Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform); // TODO to new API

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	ProjectileMovement->bAutoActivate = false;

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->bAutoActivate = false;

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
	ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

}

void AProjectile::LaunchProjectile(float Speed)
{
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovement->Activate();

	// Missle mesh came in imported the wrong way around, this flips it so it points the danger pointy the right way
	CollisionMesh->AddLocalRotation(FRotator(180, 0, 0));

	// Move the projectile trail (LaunchBlast) back 5 cm to the back of the projectile so it doesn't appear in the middle of the missle
	LaunchBlast->SetRelativeLocation(FVector(5, 0, 0));

	// Play smoke trail sound
	ProjectileMovementSoundAudio = UGameplayStatics::SpawnSoundAttached(ProjectileMovementSound, RootComponent, NAME_None, FVector::ZeroVector, EAttachLocation::SnapToTarget, true);
	ProjectileMovementSoundAudio->Activate();
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();
	ExplosionForce->FireImpulse();

	SetRootComponent(ImpactBlast);
	CollisionMesh->DestroyComponent();

	UGameplayStatics::ApplyRadialDamage(
		this,
		ProjectileDamage,
		GetActorLocation(),
		ExplosionForce->Radius,	// for consistence
		UDamageType::StaticClass(),
		TArray<AActor*>()); // damage all actors

	FTimerHandle Timer;
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &AProjectile::OnTimerExpire, DestroyDelay, false);

	// Play impact sound
	UGameplayStatics::SpawnSoundAttached(SoundOnImpact, RootComponent, NAME_None, FVector::ZeroVector, EAttachLocation::SnapToTarget, true);

	// Stop smoke trail sound
	ProjectileMovementSoundAudio->Deactivate();
}

void AProjectile::OnTimerExpire()
{
	Destroy();
}
