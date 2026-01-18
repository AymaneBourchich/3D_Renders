#pragma once
#include <glm/glm.hpp>

namespace Color
{
    // Primary
    inline constexpr glm::vec3 RED{1.0f, 0.0f, 0.0f};
    inline constexpr glm::vec3 GREEN{0.0f, 1.0f, 0.0f};
    inline constexpr glm::vec3 BLUE{0.0f, 0.0f, 1.0f};

    // Secondary
    inline constexpr glm::vec3 CYAN{0.0f, 1.0f, 1.0f};
    inline constexpr glm::vec3 MAGENTA{1.0f, 0.0f, 1.0f};
    inline constexpr glm::vec3 YELLOW{1.0f, 1.0f, 0.0f};

    // Neutral
    inline constexpr glm::vec3 WHITE{1.0f, 1.0f, 1.0f};
    inline constexpr glm::vec3 BLACK{0.0f, 0.0f, 0.0f};
    inline constexpr glm::vec3 GRAY{0.5f, 0.5f, 0.5f};

    // Extra (nice for debugging)
    inline constexpr glm::vec3 ORANGE{1.0f, 0.5f, 0.0f};
}
