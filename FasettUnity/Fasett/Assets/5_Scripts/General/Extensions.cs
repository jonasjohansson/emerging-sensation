using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public static class Extensions {

	//Even though they are used like normal methods, extension
	//methods must be declared static. Notice that the first
	//parameter has the 'this' keyword followed by a Transform
	//variable. This variable denotes which class the extension
	//method becomes a part of.
	public static GradientAlphaKey Lerp(this GradientAlphaKey low, GradientAlphaKey high, float value)
	{
		float time = Mathf.Lerp(low.time, high.time, value);
		float alpha = Mathf.Lerp(low.alpha, high.alpha, value);
		return new GradientAlphaKey(alpha, time);
	}
}