namespace SaNi.Mono.Graphics
{
public sealed class Circle
{
#region Properties
public bool Visible
{
get
{
bool value = new bool();
GetVisible(ref value);
return value;
}
set
{
SetVisible(value);
}
}
public float Radius
{
get
{
float value = new float();
GetRadius(ref value);
return value;
}
set
{
SetRadius(value);
}
}
#endregion

public Circle()
{

}
#region Internal get/set methods
[MethodImpl(MethodImplOptions.InternalCall)]
private extern void GetVisible(ref bool value);
[MethodImpl(MethodImplOptions.InternalCall)]
private extern void SetVisible(bool value);

[MethodImpl(MethodImplOptions.InternalCall)]
private extern void GetRadius(ref float value);
[MethodImpl(MethodImplOptions.InternalCall)]
private extern void SetRadius(float value);
#endregion

[MethodImpl(MethodImplOptions.InternalCall)]
private extern void AmIFirst();

[MethodImpl(MethodImplOptions.InternalCall)]
public extern void Draw();

[MethodImpl(MethodImplOptions.InternalCall)]
public extern static bool Destroyed();

~Circle()
{
}

}
}
