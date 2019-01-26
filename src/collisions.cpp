//
// Created by sriteja on 23/1/19.
//
#include "main.h"

GLboolean CheckCollision(CircleObject &one, RectangleObject &two) // AABB - Circle collision
{
    // Get center point circle first
    glm::vec2 center(one.Position + one.Radius);
    // Calculate AABB info (center, half-extents)
    glm::vec2 aabb_half_extents(two.Size.x / 2, two.Size.y / 2);
    glm::vec2 aabb_center(
            two.Position.x + aabb_half_extents.x,
            two.Position.y + aabb_half_extents.y
    );
    // Get difference vector between both centers
    glm::vec2 difference = center - aabb_center;
    glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
    // Add clamped value to AABB_center and we get the value of box closest to circle
    glm::vec2 closest = aabb_center + clamped;
    // Retrieve vector between center circle and closest point AABB and check if length <= radius
    difference = closest - center;
    return glm::length(difference) < one.Radius;
}


GLboolean CheckCollision(RectangleObject &one, RectangleObject &two) // AABB - AABB collision
{
    // Collision x-axis?
    bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
                      two.Position.x + two.Size.x >= one.Position.x;
    // Collision y-axis?
    bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
                      two.Position.y + two.Size.y >= one.Position.y;
    // Collision only if on both axes
    return static_cast<GLboolean>(collisionX && collisionY);
}


GLboolean CheckCollision(RectangleObject &one, LineObject &two) {
    bool coll = one.Position.x + one.Size.x >= two.Position.x &&
                two.Position.x + two.Length >= one.Position.x;
    bool co = one.Position.y <= two.Position.y && one.Position.y + one.Size.y >= two.Position.y;
    return static_cast<GLboolean>(coll && co);
}
