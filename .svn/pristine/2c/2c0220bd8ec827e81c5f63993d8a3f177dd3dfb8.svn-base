#include "WindowSurface.h"

vk::raii::SurfaceKHR fWindowSurface::CreateWIN32(vk::raii::Instance &vulkanInstance, HWND &windowHandle)
{
	vk::Win32SurfaceCreateInfoKHR createInfo{};
	createInfo.hinstance = GetModuleHandle(nullptr);
	createInfo.hwnd		 = windowHandle;	

	return vulkanInstance.createWin32SurfaceKHR(createInfo);    
}
