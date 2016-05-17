//namespace SaNi.Mono.Graphics.Renderables
//{
//public sealed class Sprite
//{
//#region Fields
//private Transform transform;
//private Rectf globalbounds;
//private Texture2D texture;
//private bool visible;
//private Color color;
//#endregion

//#region Properties
//public Transform Transform
//{
//get
//{
//GetTransform(ref transform);
//return transform;
//}
//set
//{
//SetTransform(value);
//}
//}
//public Rectf LocalBounds
//{

//}
//public Rectf GlobalBounds
//{
//get
//{
//GetGlobalBounds(ref globalbounds);
//return globalbounds;
//}

//}
//public Rectf TextureSource
//{

//}
//public Texture2D Texture
//{
//get
//{
//GetTexture(ref texture);
//return texture;
//}
//set
//{
//SetTexture(value);
//}
//}
//public int ID
//{

//}
//public bool Visible
//{
//get
//{
//GetVisible(ref visible);
//return visible;
//}
//set
//{
//SetVisible(value);
//}
//}
//public Color Color
//{
//get
//{
//GetColor(ref color);
//return color;
//}
//set
//{
//SetColor(value);
//}
//}
//#endregion

//public Sprite()
//{
//transform = new Transform();
//globalbounds = new Rectf();
//texture = new Texture2D();
//visible = new bool();
//color = new Color();

//}
//#region Internal get/set methods
//[MethodImpl(MethodImplOptions.InternalCall)]
//private extern void GetTransform(ref Transform value);
//[MethodImpl(MethodImplOptions.InternalCall)]
//private extern void SetTransform(Transform value);


//[MethodImpl(MethodImplOptions.InternalCall)]
//private extern void GetGlobalBounds(ref Rectf value);
//[MethodImpl(MethodImplOptions.InternalCall)]
//private extern void SetGlobalBounds(Rectf value);


//[MethodImpl(MethodImplOptions.InternalCall)]
//private extern void GetTexture(ref Texture2D value);
//[MethodImpl(MethodImplOptions.InternalCall)]
//private extern void SetTexture(Texture2D value);


//[MethodImpl(MethodImplOptions.InternalCall)]
//private extern void GetVisible(ref bool value);
//[MethodImpl(MethodImplOptions.InternalCall)]
//private extern void SetVisible(bool value);

//[MethodImpl(MethodImplOptions.InternalCall)]
//private extern void GetColor(ref Color value);
//[MethodImpl(MethodImplOptions.InternalCall)]
//private extern void SetColor(Color value);
//#endregion

//public  void Destroy()
//{
//}

//~Sprite()
//{
//}

//}
//}
