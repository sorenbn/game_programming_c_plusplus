#pragma once

struct Vector2
{
	float x;
	float y;
};

inline Vector2 vector2_zero()
{
	return Vector2{ 0.0f, 0.0f };
}