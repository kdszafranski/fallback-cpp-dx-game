#pragma once

namespace TSMath {
	/// <summary>
	/// Clamps value between 0 and 1 and returns value. If the value is negative then zero is returned. If value is greater than one then one is returned.
	/// </summary>
	/// <param name="x"></param>
	/// <returns></returns>
	float clampHighLow(float x)
	{
		if (x < 0) x = 0.0f;
		if (x > 1) x = 1.0f;
		return x;
	}
}