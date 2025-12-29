#pragma once
#include <glm/glm.hpp>

namespace Color
{
    // Primary
    inline constexpr glm::vec3 Red     {1.0f, 0.0f, 0.0f};
    inline constexpr glm::vec3 Green   {0.0f, 1.0f, 0.0f};
    inline constexpr glm::vec3 Blue    {0.0f, 0.0f, 1.0f};

    // Secondary
    inline constexpr glm::vec3 Cyan    {0.0f, 1.0f, 1.0f};
    inline constexpr glm::vec3 Magenta {1.0f, 0.0f, 1.0f};
    inline constexpr glm::vec3 Yellow  {1.0f, 1.0f, 0.0f};

    // Neutral
    inline constexpr glm::vec3 White   {1.0f, 1.0f, 1.0f};
    inline constexpr glm::vec3 Black   {0.0f, 0.0f, 0.0f};
    inline constexpr glm::vec3 Gray    {0.5f, 0.5f, 0.5f};

    // Extra (nice for debugging)
    inline constexpr glm::vec3 Orange  {1.0f, 0.5f, 0.0f};
}
