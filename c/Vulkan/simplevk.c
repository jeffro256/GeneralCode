#include <vulkan/vulkan.h>

#define ARRAYSIZE(x) sizeof(x) / sizeof(x[0])

int main() {
	VkResult err;
	
	const char* const appName = "simplest";
	
	const VkApplicationInfo appInfo = {
		.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pNext = NULL,
		.pApplicationName = appName,
		.applicationVersion = 0,
		.pEngineName = appName,
		.engineVersion = 0,
		.apiVersion = VK_API_VERSION_1_0,
	};
	
	const char** layerNames = { "VK_LAYER_LUNARG_standard_validation" };
	const char** extensionNames = { VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_XCB_SURFACE_EXTENSION_NAME };
	
	const VKInstanceCreateInfo instanceInfo = {
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
	
	puts("No errors so far!");
	
	return 0;
}