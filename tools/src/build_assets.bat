@echo off
if "%1"=="" GOTO NoAssetFolder

set AssetFolder=%1
for /r "%AssetFolder%" %%f in ("*.*") do (
	echo %%f
)

GOTO End

:NoAssetFolder
	echo No asset folder specified

:End