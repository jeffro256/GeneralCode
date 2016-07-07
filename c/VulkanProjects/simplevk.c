#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <vulkan/vulkan.h>

#ifndef ARRAYSIZE
#define ARRAYSIZE(x) sizeof(x) / sizeof(x[0])
#endif

#ifdef _WIN32
#pragma comment(linker, "/subsystem:windows")
#endif

#ifdef _WIN32
#define PLATFORM_SURFACE_NAME VK_KHR_WIN32_SURFACE_EXTENSION_NAME
#else
#define PLATFORM_SURFACE_NAME VK_KHR_XCB_SURFACE_EXTENSION_NAME
#endif

#define APPNAME "simpleVK"

VKAPI_ATTR VkBool32 VKAPI_CALL
debugFunc(VkFlags msgFlags, VkDebugReportObjectTypeEXT objectType, uint64_t srcObject, size_t location, 
int32_t msgCode, const char* pLayerPrefix, const char* pMsg, void* pUserData) {
	if (msgFlags & VK_DEBUG_REPORT_ERROR_BIT_EXT) {
		printf("Got error code %d:\n", msgCode);
	}
	else if (msgFlags & VK_DEBUG_REPORT_WARNING_BIT_EXT) {
		printf("Got warning code %d:\n", msgCode);
	}
	else {
		printf("Got message code %d:\n", msgCode);
	}
	
	puts(pMsg);
	fflush(stdout);
	
	return false;
}

int main() {
	VkResult err;
	
	// CREATE INSTANCE
	
	const VkApplicationInfo appInfo = {
		.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pNext = NULL,
		.pApplicationName = APPNAME,
		.applicationVersion = 0,
		.pEngineName = APPNAME,
		.engineVersion = 0,
		.apiVersion = VK_API_VERSION,
	};
	
	const char* layerNames[] = { "VK_LAYER_LUNARG_standard_validation" };
	const char* extensionNames[] = { 
		VK_KHR_SURFACE_EXTENSION_NAME, 
		PLATFORM_SURFACE_NAME, 
		VK_EXT_DEBUG_REPORT_EXTENSION_NAME,
	};
	
	const VkInstanceCreateInfo instanceInfo = {
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pNext = NULL,
		.pApplicationInfo = &appInfo,
		.enabledLayerCount = ARRAYSIZE(layerNames),
		.ppEnabledLayerNames = layerNames,
		.enabledExtensionCount = ARRAYSIZE(extensionNames),
		.ppEnabledExtensionNames = extensionNames,
	};
	
	VkInstance instance;
	err = vkCreateInstance(&instanceInfo, NULL, &instance);
	if (err) return err;
	
	// SET UP DEBUG FUNCTIONS
	PFN_vkCreateDebugReportCallbackEXT createDebugCallback = 
		(PFN_vkCreateDebugReportCallbackEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
	PFN_vkDestroyDebugReportCallbackEXT destroyDebugCallback = 
		(PFN_vkDestroyDebugReportCallbackEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");
	
	const VkDebugReportCallbackCreateInfoEXT debugInfo = {
		.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT,
		.pNext = NULL,
		.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT,
		.pfnCallback = debugFunc,
		.pUserData = NULL,
	};
	
	VkDebugReportCallbackEXT debugCallback;
	if (createDebugCallback) {
		err = createDebugCallback(instance, &debugInfo, NULL, &debugCallback);
		if (err) return err;
	}
	else {
		puts("Could not find vkCreateDebugReportCallbackEXT");
		return -1;
	}
	
	if (!destroyDebugCallback) {
		puts("Could not find vkDestroyDebugReportCallbackEXT");
		return -1;
	}
	
	// GET PHYSICAL DEVICE
	
	uint32_t gpuCount;
	VkPhysicalDevice gpu;
	VkPhysicalDeviceProperties gpuProperties;
	
	err = vkEnumeratePhysicalDevices(instance, &gpuCount, NULL);
	if (err) return err;
	
	if (gpuCount <= 0) {
		puts("Could not find any physical devices!");
		return -1;
	}
	
	printf("There are %u physical devices to choose from.\n", gpuCount);
	
	gpuCount = 1;
	err = vkEnumeratePhysicalDevices(instance, &gpuCount, &gpu);
	if (err) return err;
	
	vkGetPhysicalDeviceProperties(gpu, &gpuProperties);
	
	printf("We got '%s'.\n\n", gpuProperties.deviceName);
	
	// CREATE LOGICAL DEVICE
	
	uint32_t familyCount;
	VkQueueFamilyProperties* families;
	
	vkGetPhysicalDeviceQueueFamilyProperties(gpu, &familyCount, NULL);
	families = malloc(sizeof(VkQueueFamilyProperties) * familyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(gpu, &familyCount, families);
	
	int familyIndex = -1;
	
	for (int i = 0; i < familyCount; i++) {
		if (families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			familyIndex = i;
			break;
		}
	}
	
	if (familyIndex == -1) {
		puts("Could not find a graphics queue family!");
		return -1;
	}
	
	const float queuePriorities[] = { 0.0 };
	const VkDeviceQueueCreateInfo queueInfo = {
		.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
        .pNext = NULL,
        .queueFamilyIndex = familyIndex,
        .queueCount = ARRAYSIZE(queuePriorities),
        .pQueuePriorities = queuePriorities,
	};
	
	const char* deviceExtensionNames[] = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
	VkPhysicalDeviceFeatures deviceFeatures;
	memset(&deviceFeatures, 0, sizeof(VkPhysicalDeviceFeatures));
	const VkDeviceCreateInfo deviceInfo = {
		.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		.pNext = NULL,
		.queueCreateInfoCount = 1,
		.pQueueCreateInfos = &queueInfo,
		.enabledExtensionCount = ARRAYSIZE(deviceExtensionNames),
        .ppEnabledExtensionNames = deviceExtensionNames,
        .pEnabledFeatures = &deviceFeatures,
	};
	
	VkDevice device;
	err = vkCreateDevice(gpu, &deviceInfo, NULL, &device);
	if (err) return err;
	
	puts("We have a device!!!");
	
	// CLEAN UP
	vkDestroyDevice(device, NULL);
	destroyDebugCallback(instance, debugCallback, NULL);
	vkDestroyInstance(instance, NULL);
	
	return 0;
}
