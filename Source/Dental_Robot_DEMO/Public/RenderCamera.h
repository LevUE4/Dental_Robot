// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "MediaTexture.h"
#include "Runtime/Engine/Classes/Engine/Texture2D.h"
#include "Runtime/Engine/Classes/Engine/TextureRenderTarget2D.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RenderCamera.generated.h"

UCLASS()
class DENTAL_ROBOT_DEMO_API ARenderCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARenderCamera(const FObjectInitializer& ObjectinItializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(blueprintReadWrite, EditAnywhere, Category = "Components")
		USceneComponent* rootComp;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = OpenCV)
		UStaticMeshComponent* Screen_Raw;
	//UPROPERTY(blueprintReadWrite, EditAnywhere, Category = "Camera")
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = OpenCV)
		UStaticMeshComponent* Screen_Post;

	UPROPERTY(blueprintReadWrite, EditAnywhere, Category = Camera, meta = (ClampMin = 0, UIMin = 0))
		int32 CameraID;
	UPROPERTY(blueprintReadWrite, EditAnywhere, Category = Camera, meta = (ClampMin = 0, UIMin = 0))
		int32 VideoTrackID;
	UPROPERTY(blueprintReadWrite, EditAnywhere, Category = Camera, meta = (ClampMin = 0, UIMin = 0))
		float RefreshRate;
	UPROPERTY(blueprintReadWrite, Category = Camera)
		float RefreshTimer; 
	UPROPERTY(blueprintReadWrite, Category = Camera)
		bool isStreamOpen;
	UPROPERTY(blueprintReadWrite, Category = Camera)
		FVector2D VideoSize;

	UPROPERTY(blueprintReadWrite, EditAnywhere, Category = Camera)
		float Brightness;
	UPROPERTY(blueprintReadWrite, EditAnywhere, Category = Camera)
		float Multiply;

	UPROPERTY(blueprintReadWrite, EditAnywhere, Category = Camera)
		UMediaPlayer* Camera_MediaPlayer;
	UPROPERTY(blueprintReadWrite, EditAnywhere, Category = Camera)
		UMediaTexture* Camera_MediaTexture;
	UPROPERTY(blueprintReadWrite, EditAnywhere, Category = Camera)
		UTextureRenderTarget2D* Camera_RenderTarget;
	UPROPERTY(blueprintReadWrite, EditAnywhere, Category = Camera)
		UTextureRenderTarget2D* Camera_RenderTexture;
	UPROPERTY(blueprintReadWrite, EditAnywhere, Category = Camera)
		UMaterialInstanceDynamic* Camera_MatRaw;
	UPROPERTY(blueprintReadWrite, EditAnywhere, Category = Camera)
		UMaterialInstanceDynamic* Camera_MatPost;

	UPROPERTY(blueprintReadOnly, VisibleAnywhere, Category = Camera)
		UTexture2D* Camera_Texture2D;

	UPROPERTY(blueprintReadOnly, VisibleAnywhere, Category = Data)
		TArray<FColor> ColorData;

	UFUNCTION(blueprintImplementableEvent, Category = Camera)
		void OnNextVideoFrame();
	UFUNCTION(BlueprintCallable, Category = Data)
		bool ReadFrame();

	cv::Size cvSize;
	cv::Mat cvMat;
};
