#include"Toolkit.h"

void Toolkit::Print(const String& output)
{
	// Logging appears both in the engine console and stdout
	URHO3D_LOGRAW(output + "\n");
}

Vector3 Toolkit::RotateAngle(Vector3 v, const float angle)
{
	float x = v.x_*cos(angle) - v.y_*sin(angle);
	float y = v.x_*sin(angle) + v.y_*cos(angle);
	return(Vector3(x, y, 0.0f));
}

String Toolkit::CutStringBeforeChar(const String& src, const char& target)
{
	int n = src.Find(target);
	return src.Substring(0, n);
}

String Toolkit::CutStringAfterChar(const String& src, const char& target)
{
	int n = src.Find(target);
	return src.Substring(n+1);
}