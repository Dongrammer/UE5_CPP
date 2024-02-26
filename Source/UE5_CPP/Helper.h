#pragma once

#include "CoreMinimal.h"

class UE5_CPP_API Helper
{
public:
	template<typename T>
	static T* CreateComponent(AActor* InOwner, FName InComponentName, USceneComponent* InParent = nullptr, FName InSocketName = NAME_None)
	{
		T* Component = InOwner->CreateDefaultSubobject<T>(InComponentName);

		if (InParent != nullptr)
			Component->SetupAttachment(InParent, InSocketName);
		else
			InOwner->SetRootComponent(Component);

		return Component;
	}

	template<typename T>
	static T* GetAsset(FString InPath)
	{
		ConstructorHelpers::FObjectFinder<T> Asset(*InPath);

		return Cast<T>(Asset.Object);
	}
};
