@echo off

echo Searching for .uproject to build...
for %%f in (*.uproject) do (
    set "UPROJECT=%%f"
)

if not defined UPROJECT (
    echo No .uproject found.
    pause
    exit /b 1
)

set "UPROJECT_PATH=%CD%\%UPROJECT%"
echo Found .uproject: %UPROJECT_PATH%

"C:\Program Files\Epic Games\UE_5.4\Engine\Build\BatchFiles\RunUAT.bat" BuildCookRun -project="%UPROJECT_PATH%" -build -clean -ForceMonolithic -cook -IgnoreCookErrors -ForceDebugInfo -TargetPlatforms=Win64
