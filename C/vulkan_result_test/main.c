#include <stdio.h>

#include "vulkan/vulkan.h"
#include "vulkan_result.h"
#include "vulkan_assert.h"

int main() {
    puts(vkGetResultString(VK_SUCCESS));    
    puts(vkGetResultString(VK_NOT_READY));
    puts(vkGetResultString(VK_TIMEOUT));
    puts(vkGetResultString(VK_EVENT_SET));
    puts(vkGetResultString(VK_EVENT_RESET));
    puts(vkGetResultString(VK_INCOMPLETE));
    puts(vkGetResultString(VK_ERROR_OUT_OF_HOST_MEMORY));
    puts(vkGetResultString(VK_ERROR_OUT_OF_DEVICE_MEMORY));
    puts(vkGetResultString(VK_ERROR_INITIALIZATION_FAILED));
    puts(vkGetResultString(VK_ERROR_DEVICE_LOST));
    puts(vkGetResultString(VK_ERROR_MEMORY_MAP_FAILED));
    puts(vkGetResultString(VK_ERROR_LAYER_NOT_PRESENT));
    puts(vkGetResultString(VK_ERROR_EXTENSION_NOT_PRESENT));
    puts(vkGetResultString(VK_ERROR_FEATURE_NOT_PRESENT));
    puts(vkGetResultString(VK_ERROR_INCOMPATIBLE_DRIVER));
    puts(vkGetResultString(VK_ERROR_TOO_MANY_OBJECTS));
    puts(vkGetResultString(VK_ERROR_FORMAT_NOT_SUPPORTED));

    vulkan_assert(VK_ERROR_OUT_OF_DEVICE_MEMORY);

    return 0;
}
