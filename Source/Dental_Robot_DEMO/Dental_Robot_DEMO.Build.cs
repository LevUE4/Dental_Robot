// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
using System.IO;
using UnrealBuildTool;

public class Dental_Robot_DEMO : ModuleRules
{
	string OPENCV_VERSION = "451";
	private string ThirdPartyPath
    {
		get
        {
			return Path.GetFullPath(Path.Combine(ModuleDirectory, "../../ThirdParty/"));
        }
    }

	public bool LoadOpenCV(ReadOnlyTargetRules Target)
    {
		bool isLibrarySupported = false;

		string OpenCVPath = Path.Combine(ThirdPartyPath, "OpenCV");

		string LibPath = "";
		bool isdebug = Target.Configuration == UnrealTargetConfiguration.Debug;
		if (Target.Platform == UnrealTargetPlatform.Win64)
        {
			LibPath = Path.Combine(OpenCVPath, "Libraries", "Win64");
			isLibrarySupported = true;
        } 
		else
        {
			string Err = string.Format("{0} deticated server is made to depend on {1}. We want to avoid this, please correct module dependencies.");
        }

		if (isLibrarySupported)
        {
			PublicIncludePaths.AddRange(new string[] { Path.Combine(OpenCVPath, "Includes") });
			PublicAdditionalLibraries.Add(Path.Combine(LibPath, "opencv_world" + OPENCV_VERSION + ".lib"));
			PublicDelayLoadDLLs.Add("opencv_world" + OPENCV_VERSION + ".dll");
			PublicDelayLoadDLLs.Add("opencv_videoio_ffmpeg" + OPENCV_VERSION + "_64.dll");
        }
		PublicDefinitions.Add(string.Format("WITH_OPENCV_BINDING={0}", isLibrarySupported ? 1 : 0));
		return isLibrarySupported;
    }

	public Dental_Robot_DEMO(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PublicDependencyModuleNames.Add("MediaAssets");

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true

		LoadOpenCV(Target);
	}
}
