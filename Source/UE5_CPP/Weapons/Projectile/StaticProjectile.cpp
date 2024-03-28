#include "Weapons/Projectile/StaticProjectile.h"

#include "Components/BoxComponent.h"
#include "Helper.h"

AStaticProjectile::AStaticProjectile()
{
	Bullet = Helper::CreateSceneComponent<UStaticMeshComponent>(this, "Bullet Mesh", Scene);
	Bullet->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Collision->SetupAttachment(Scene);
}
