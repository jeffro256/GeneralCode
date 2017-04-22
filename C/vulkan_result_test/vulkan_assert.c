#include <stdio.h>
#include <stdlib.h>

#include "vulkan/vulkan.h"
#include "vulkan_assert.h"
#include "vulkan_result.h"

void vulkan_assert(VkResult result) {
    if (result) {
        fprintf(stderr, "Exiting because of error '%s' (code: %d)\n", vkGetResultString(result), (int) result);
        exit(result);
    }
}
