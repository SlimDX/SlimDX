﻿/*
* Copyright (c) 2007-2009 SlimDX Group
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/
using System;

namespace SlimDX2.Direct3D9
{
    public partial class VertexDeclaration
    {
        /// <summary>	
        /// Create a vertex shader declaration from the device and the vertex elements.	
        /// </summary>	
        /// <remarks>	
        ///  See the {{Vertex Declaration (Direct3D 9)}} page for a detailed description of how to map vertex declarations between different versions of DirectX. 	
        /// </remarks>	
        /// <param name="elements"> An array of <see cref="SlimDX2.Direct3D9.VertexElement"/> vertex elements. </param>
        /// <returns><see cref="VertexDeclaration"/> If the method succeeds</returns>
        /// <unmanaged>HRESULT IDirect3DDevice9::CreateVertexDeclaration([In, Buffer] const D3DVERTEXELEMENT9* pVertexElements,[None] IDirect3DVertexDeclaration9** ppDecl)</unmanaged>
        public VertexDeclaration(Device device, VertexElement[] elements)
        {
            VertexDeclaration temp;
            device.CreateVertexDeclaration(elements, out temp);
            NativePointer = temp.NativePointer;
        }
    }
}
