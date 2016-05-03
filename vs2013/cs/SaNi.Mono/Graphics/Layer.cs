using SaNi.Mono.Graphics.Renderables;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace SaNi.Mono.Graphics
{
    public sealed class Layer
    {
        #region Fields
        private readonly uint ptr;

        private List<IRenderable> elements;

        private bool destroyed;
        #endregion

        #region Properties
        public string Name
        {
            get
            {
                var value = string.Empty;

                GetName(ref value);

                return value;
            }
            set
            {
                SetName(value);
            }
        }
        public float Order
        {
            get
            {
                var value = 0.0f;

                GetOrder(ref value);

                return value;
            }
            set
            {
                SetOrder(value);
            }
        }
        public bool Visible
        {
            get
            {
                var value = false;

                GetVisible(ref value);

                return value;
            }
        }
        public LayerType Type
        {
            get
            {
                byte value = 0;

                GetType(ref value);

                return (LayerType)value;
            }
        }
        public IEnumerable<IRenderable> Elements
        {
            get
            {
                return elements;
            }
        }
        public int ElementsCount
        {
            get
            {
                var count = 0;

                GetElementsCount(ref count);

                return count;
            }
        }
        #endregion

        private Layer(string name, LayerType type)
        {
            Instantiate(name, type, ref ptr);

            elements = new List<IRenderable>();
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void Instantiate(string name, LayerType type, ref uint ptr);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void Release();

        #region Internal get/set methods
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetName(ref string value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetName(string value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetOrder(ref float value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetOrder(float value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetVisible(ref bool value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetVisible(bool value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetType(ref byte value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetElementsCount(ref int value);
        #endregion

        private void ReleaseElements()
        {
            foreach (var element in elements) element.Destroy();
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void InternalAdd(IRenderable element);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void InternalRemove(IRenderable element);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern void Hide();
        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern void Show();

        public void Add(IRenderable element)
        {
            Console.WriteLine("add");

            Thread.Sleep(2500);
            elements.Add(element);
            Console.WriteLine("d add");

            Console.WriteLine("i add");
            InternalAdd(element);

            Console.WriteLine("d i add");
        }
        public void Add(IEnumerable<IRenderable> elements)
        {
            foreach (var element in elements) Add(element);
        }

        public void Remove(IRenderable element)
        {
            elements.Remove(element);

            InternalRemove(element);
        }
        public void Remove(IEnumerable<IRenderable> elements, bool destroy = false)
        {
            foreach (var element in elements)
            {
                Remove(element);

                if (destroy) element.Destroy();
            }
        }

        public bool Contains(IRenderable renderable)
        {
            return elements.Contains(renderable);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern void MoveElementsTo(Layer target);

        private void Destroy()
        {
            if (destroyed) return;

            foreach (var element in elements) element.Destroy();

            Release();

            GC.SuppressFinalize(this);


            Console.WriteLine("LAYER CTOR");

            destroyed = true;
        }

        ~Layer()
        {
            Console.WriteLine("LAYER CTOR");
            if (destroyed) return;

            Destroy();
        }
    }
}
