@echo off 

for %%F IN (C:\Midnight\shaders\slang\*.slang) DO (
    echo #=====================================
    echo # Compiling [%%~nF]
    echo #=====================================
    
    C:\VulkanSDK\1.4.341.1\Bin\slangc.exe %%F ^
	    -target spirv ^
	    -profile spirv_1_4 ^
	    -emit-spirv-directly ^
	    -fvk-use-entrypoint-name ^
	    -entry Vertex_Main ^
	    -entry Fragment_Main ^
	    -o C:\Midnight\shaders\spirv\%%~nF.spv

echo:     
echo +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
echo: 
)

pause