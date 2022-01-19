// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenCVCameraReader.h"

// Sets default values
AOpenCVCameraReader::AOpenCVCameraReader(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ensure the root component exists
	if (!RootComponent)
		RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, false);

	// Create and attach sub components
	Screen_Raw = CreateDefaultSubobject<UStaticMeshComponent>("Screen Raw");
	Screen_Raw->AttachToComponent(RootComponent, rules);
	Screen_Post = CreateDefaultSubobject<UStaticMeshComponent>("Screen Post");
	Screen_Post->AttachToComponent(RootComponent, rules);

	// setup property defaults
	ColorMode = ETextureRenderTargetFormat::RTF_RGBA8;

	Brightness = 0;
	Multiply = 1;

	// Initialize OpenCV and webcam properties
	CameraID = 0;
	VideoTrackID = 0;
	VideoSize = FVector2D(1920, 1080);
	RefreshRate = 30.0f;
}

// Called when the game starts or when spawned
void AOpenCVCameraReader::BeginPlay()
{
	Super::BeginPlay();

	// Prepare the color data array
	ColorData.AddDefaulted(VideoSize.X * VideoSize.Y);

	// setup openCV
	cvSize = cv::Size(VideoSize.X, VideoSize.Y);
	int cvColorMode = GetColorMode_CV();
	cvMat = cv::Mat(cvSize, cvColorMode, ColorData.GetData());

	// create dynamic texture
	OpenCV_Texture2D = UTexture2D::CreateTransient(VideoSize.X, VideoSize.Y, PF_B8G8R8A8);
#if WITH_EDITORONLY_DATA
	OpenCV_Texture2D->MipGenSettings = TMGS_NoMipmaps;
#endif
	OpenCV_Texture2D->SRGB = RenderTarget->SRGB;
}

// Called every frame
void AOpenCVCameraReader::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RefreshTimer += DeltaTime;
	if (RefreshTimer >= 1.0f / RefreshRate) {
		RefreshTimer -= 1.0f / RefreshRate;
		ReadFrame();
		OnNextVideoFrame();
	}
}

int AOpenCVCameraReader::GetColorMode_CV() {
	int cvColorMode = CV_8UC4;
	switch (ColorMode)
	{
	case ETextureRenderTargetFormat::RTF_RGBA8:
		cvColorMode = CV_8UC4;
		break;
	case ETextureRenderTargetFormat::RTF_RGBA16f:
		UE_LOG(LogTemp, Warning, TEXT("16 bit not yet supported, Only 8 bit colour implemented currently will always return CV_8UC4"));
		cvColorMode = CV_16FC4;
		break;
	case ETextureRenderTargetFormat::RTF_RGBA32f:
		UE_LOG(LogTemp, Warning, TEXT("32 bit not yet supported, Only 8 bit colour implemented currently will always return CV_8UC4"));
		cvColorMode = CV_32FC4;
		break;
	default:
		// TODO Error unrecognized color format!
		cvColorMode = CV_8UC4;
		break;
	}
	return cvColorMode;
}

bool AOpenCVCameraReader::ReadFrame() {
	if (!OpenCV_Texture2D || !RenderTarget) return false;
	// Read the pixels from the RenderTarget and store them in a FColor array
	//TArray<FColor> SurfData;

	FRenderTarget* renderTarget = RenderTarget->GameThread_GetRenderTargetResource();

	renderTarget->ReadPixels(ColorData);
	int cvColorMode = GetColorMode_CV();

	// Get the color data
	cvMat = cv::Mat(cvSize, cvColorMode, ColorData.GetData());

	// do fun stuff here
	cvMat.convertTo(cvMat, -1, Multiply, Brightness);

	// show the openCV window
	if (!cvMat.empty())
		cv::imshow("Display", cvMat);

	void* TextureData = OpenCV_Texture2D->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
	const int32 TextureDataSize = ColorData.Num() * 4;
	// set the texture data

	FMemory::Memcpy(TextureData, ColorData.GetData(), TextureDataSize);
	OpenCV_Texture2D->PlatformData->Mips[0].BulkData.Unlock();
	// Apply Texture changes to GPU memory
	OpenCV_Texture2D->UpdateResource();

	/*
	//Wrapped in a render command for performance
	ENQUEUE_RENDER_COMMAND(WriteOpenCVTexture)(
		[RTarget = RenderTarget, RTexture = OpenCV_Texture2D, ColorD = ColorData](FRHICommandList& RHICmdList)
		{

		});
	*/
	return true;
}

void AOpenCVCameraReader::NextCamera()
{
	CameraID += 1;
	ValidateCameraID();
}
//increment video track by one then validate exists
void AOpenCVCameraReader::NextVideoTrack()
{
	VideoTrackID += 1;
	ValidateVideoTrackID();
}



