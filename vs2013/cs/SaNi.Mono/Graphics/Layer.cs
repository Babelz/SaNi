﻿using SaNi.Mono.Graphics.Renderables;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Graphics
{
    public sealed class Layer
    {
        #region Fields
        private readonly uint ptr;

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
        public IRenderable[] Renderables
        {
            get
            {
                IRenderable[] renderables = null;

                GetRenderables(ref renderables);

                return renderables;
            }
        }
        #endregion

        private Layer(string name, LayerType type)
        {
            Instantiate(name, type, ref ptr);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void Instantiate(string name, LayerType type, ref uint ptr);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void Release(uint ptr);

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
        private extern void GetType(ref byte type);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetRenderables(ref IRenderable[] renderables);

        private void ReleaseElements()
        {
            foreach (var element in Renderables) element.Destroy();
        }
        #endregion

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern void Hide();
        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern void Show();

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern void Add(IRenderable renderable);

        public void Add(IEnumerable<IRenderable> elements)
        {
            foreach (var element in elements) Add(element);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern void Remove(IRenderable renderable);

        public void Remove(IEnumerable<IRenderable> elements, bool destroy = false)
        {
            foreach (var element in elements)
            {
                Remove(element);

                if (destroy) element.Destroy();
            }
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern void Contains(IRenderable renderable);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern void MoveElementsTo(Layer target);

        void Destroy()
        {
            if (destroyed) return;

            var elements = Renderables();

            for (var i = 0; i < elements.Length; i++) elements[i].Destroy();

            Release(ptr);

            GC.SuppressFinalize(this);

            destroyed = true;
        }

        ~Layer()
        {
            if (destroyed) return;

            Destroy();
        }
    }
}
