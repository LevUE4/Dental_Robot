// Fill out your copyright notice in the Description page of Project Settings.


#include "RenderCamera.h"

// Sets default values
ARenderCamera::ARenderCamera(const FObjectInitializer& ObjectinItializer) : Super(ObjectinItializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

//	rootComp = CreateDefaultSubobject<USceneComponent>("Root");

	if (!RootComponent)
		RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, false);

	Screen_Raw = CreateDefaultSubobject<UStaticMeshComponent>("Screen_Raw");
	Screen_Raw->AttachToComponent(RootComponent, rules);//
	Screen_Post = CreateDefaultSubobject<UStaticMeshComponent>("Screen_Post");
	Screen_Post->AttachToComponent(RootComponent, rules); //

	Brightness = 0;
	Multiply = 1;

	CameraID = 0;
	VideoTrackID = 0;
	isStreamOpen = false;
	VideoSize = FVector2D(1920, 1080);
	RefreshRate = 30.0f;

}

// Called when the game starts or when spawned
void ARenderCamera::BeginPlay()
{
	Super::BeginPlay();
	isStreamOpen = true;

	ColorData.AddDefaulted(VideoSize.X * VideoSize.Y);
	cvSize = cv::Size(VideoSize.X, VideoSize.Y);
	cvMat = cv::Mat(cvSize, CV_8UC4, ColorData.GetData());
	Camera_Texture2D = UTexture2D::CreateTransient(VideoSize.X, VideoSize.Y, PF_B8G8R8A8);

#if WITH_EDITORONLY_DATA
	Camera_Texture2D->MipGenSettings = TMGS_NoMipmaps;
#endif
	Camera_Texture2D->SRGB = Camera_RenderTarget->SRGB;
}

// Called every frame
void ARenderCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RefreshTimer += DeltaTime;
	if (isStreamOpen && RefreshTimer >= 1.0f / RefreshRate)
	{
		RefreshTimer -= 1.0f / RefreshRate;
		ReadFrame();
		OnNextVideoFrame();
	}
}

bool ARenderCamera::ReadFrame() {
	if (!Camera_Texture2D || !Camera_RenderTarget) return false;
	
	FRenderTarget* RenderTarget = Camera_RenderTarget->GameThread_GetRenderTargetResource();
	RenderTarget->ReadPixels(ColorData);

	cvMat = cv::Mat(cvSize, CV_8UC4, ColorData.GetData());

	cvMat.convertTo(cvMat, -1, Multiply, Brightness);

	if (!cvMat.empty())
		cv::imshow("Display", cvMat);
	
	void* TextureData = Camera_Texture2D->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
	const int32 TextureDataSize = ColorData.Num() * 4;
	FMemory::Memcpy(TextureData, ColorData.GetData(), TextureDataSize);
	Camera_Texture2D->PlatformData->Mips[0].BulkData.Unlock();
	Camera_Texture2D->UpdateResource();

	return true;
}

