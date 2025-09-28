// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimeManager.generated.h"

UCLASS()
class DIVER_API ATimeManager : public AActor
{
	GENERATED_BODY()
	
public:
	ATimeManager();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

public:
    // 하루 주기 (초)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
    float DayLengthInSeconds = 1200.f;

    // 태양 최대 세기
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
    float MaxSunIntensity = 10.f;

    // 스카이 라이트 최대 세기
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
    float MaxSkyIntensity = 1.f;

    // 태양 역할 Directional Light
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
    ADirectionalLight* DirectionalLight;

    // 하늘광 Sky Light
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
    ASkyLight* SkyLight;

    // 하늘 대기 Sky Atmosphere
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
    ASkyAtmosphere* SkyAtmosphere;

    // 전체 화면 PostProcessVolume (선택사항)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
    APostProcessVolume* PostProcessVolume;

private:
    float TimeOfDay = 0.0f;
};
