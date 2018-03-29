#pragma once

#include "Destroyable_Interface.generated.h"

UINTERFACE(Blueprintable)
class UDestroyableInterface : public UInterface
{
	GENERATED_BODY()
};

class IDestroyableInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Destroyable Actor")
	bool Kill();
};