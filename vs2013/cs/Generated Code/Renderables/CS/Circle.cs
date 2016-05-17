namespace SaNi.Mono.Graphics.Renderables
{
public sealed class Circle
{
#region Fields
private Transform transform;
private Rectf globalbounds;
private Texture2D texture;
private bool visible;
private float radius;
private float borderthickness;
private Color borderfill;
private Color fill;
#endregion

#region Properties
public Transform Transform
{
get
{
GetTransform(ref transform);
return transform;
}
set
{
SetTransform(value);
}
}
public Rectf LocalBounds
{

}
public Rectf GlobalBounds
{
get
{
GetGlobalBounds(ref globalbounds);
return globalbounds;
}

}
public Rectf TextureSource
{

}
public Texture2D Texture
{
get
{
GetTexture(ref texture);
return texture;
}
set
{
SetTexture(value);
}
}
public int ID
{

}
public bool Visible
{
get
{
GetVisible(ref visible);
return visible;
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
GetRadius(ref radius);
return radius;
}
set
{
SetRadius(value);
}
}
public float BorderThickness
{
get
{
GetBorderThickness(ref borderthickness);
return borderthickness;
}
set
{
SetBorderThickness(value);
}
}
public Color BorderFill
{
get
{
GetBorderFill(ref borderfill);
return borderfill;
}
set
{
SetBorderFill(value);
}
}
public Color Fill
{
get
{
GetFill(ref fill);
return fill;
}
set
{
SetFill(value);
}
}
#endregion

public Circle()
{
transform = new Transform();
globalbounds = new Rectf();
texture = new Texture2D();
visible = new bool();
radius = new float();
borderthickness = new float();
borderfill = new Color();
fill = new Color();

}
#region Internal get/set methods
[MethodImpl(MethodImplOptions.InternalCall)]
private extern void GetTransform(ref Transform value);
[MethodImpl(MethodImplOptions.InternalCall)]
private extern void SetTransform(Transform value);


[MethodImpl(MethodImplOptions.InternalCall)]
private extern void GetGlobalBounds(ref Rectf value);
[MethodImpl(MethodImplOptions.InternalCall)]
private extern void SetGlobalBounds(Rectf value);


[MethodImpl(MethodImplOptions.InternalCall)]
private extern void GetTexture(ref Texture2D value);
[MethodImpl(MethodImplOptions.InternalCall)]
private extern void SetTexture(Texture2D value);


[MethodImpl(MethodImplOptions.InternalCall)]
private extern void GetVisible(ref bool value);
[MethodImpl(MethodImplOptions.InternalCall)]
private extern void SetVisible(bool value);

[MethodImpl(MethodImplOptions.InternalCall)]
private extern void GetRadius(ref float value);
[MethodImpl(MethodImplOptions.InternalCall)]
private extern void SetRadius(float value);

[MethodImpl(MethodImplOptions.InternalCall)]
private extern void GetBorderThickness(ref float value);
[MethodImpl(MethodImplOptions.InternalCall)]
private extern void SetBorderThickness(float value);

[MethodImpl(MethodImplOptions.InternalCall)]
private extern void GetBorderFill(ref Color value);
[MethodImpl(MethodImplOptions.InternalCall)]
private extern void SetBorderFill(Color value);

[MethodImpl(MethodImplOptions.InternalCall)]
private extern void GetFill(ref Color value);
[MethodImpl(MethodImplOptions.InternalCall)]
private extern void SetFill(Color value);
#endregion

public  void Destroy()
{
}

~Circle()
{
}

}
}
