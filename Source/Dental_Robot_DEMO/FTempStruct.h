#pragma once

#include "CoreMinimal.h"

#include "FTempStruct.genetated.h"

USTRUCT(BlueprintType)
struct FStruct
{
	GENERATE_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AA")
		int id = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AA")
		float Temp = 0;

};