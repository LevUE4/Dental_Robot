#pragma once

#include "CoreMinimal.h"

#include "FStruct.genetated.h"

USTRUCT (BlueprintType)
struct FStruct
{
	GENERATE_BODY()

	public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AA")
			float y_accel = 0;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AA")
			float x_accel = 0;
		
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AA")
			float z_accel = 0;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AA")
			float mic_fft_freq = 0;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AA")
			float mic_fft_vol = 0;


		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AA")
			TArray <TouchSenseStruct> aTouchSense;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AA")
			TArray <TempSenseStruct> aTempSense;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AA")
			TArray <ZoneForceStruct> aZoneSorce;
		

};