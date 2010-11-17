﻿// Copyright (c) 2007-2010 SlimDX Group
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
using System;
using SlimDX.XIDL;

namespace SlimDX.Generator
{
    internal partial class Program
    {
        public CSharpFunctionGroup D3DCommonFunctionGroup;

        public void MapDirect3DCommon()
        {
            // Global namespace for Direct3D Commmon classes (Direct3D10 and Direct3D11)
            string assemblyName = Global.Name;
            string namespaceName = Global.Name + ".Direct3D";

            gen.MapIncludeToNamespace("d3dcommon", assemblyName, namespaceName, "Direct3D");

            group.FindContext.Add("d3dcommon");

            // --------------------------------------------------------------------------------------------------------
            // D3DCommon Enumerations
            // --------------------------------------------------------------------------------------------------------              
            group.TagName<CppEnum>(@"^D3D(.*)", "$1", false);
            group.TagName<CppEnumItem>(@"^D3D(.*)", "$1", false);

            group.Remove<CppEnumItem>(@"D3D(\d+)_PRIMITIVE_TOPOLOGY_.*");
            group.Remove<CppEnumItem>(@"D3D(\d+)_PRIMITIVE_.*");

            group.Remove<CppEnumItem>(@"D3D(\d+)_SRV_DIMENSION_.*");
            group.Remove<CppEnumItem>(@"D3D(\d+_1)_SRV_DIMENSION_.*");

            group.Remove<CppEnumItem>(@"^D3D(\d+)_SVC_.*");
            group.Remove<CppEnumItem>(@"^D3D(\d+)_SVF_.*");
            group.Remove<CppEnumItem>(@"^D3D(\d+)_SVT_.*");
            group.Remove<CppEnumItem>(@"^D3D(\d+)_SIF_.*");
            group.Remove<CppEnumItem>(@"^D3D(\d+)_SIT_.*");
            group.Remove<CppEnumItem>(@"^D3D(\d+)_CT_.*");
            group.Remove<CppEnumItem>(@"^D3D(\d+)_NAME_.*");
            group.Remove<CppEnumItem>(@"^D3D(\d+)_INCLUDE_.*");
            group.Remove<CppEnumItem>(@"^D3D(\d+)_RETURN_TYPE_.*");
            group.Remove<CppEnumItem>(@"^D3D(\d+)_TESSELLATOR_OUTPUT_.*");
            group.Remove<CppEnumItem>(@"^D3D(\d+)_TESSELLATOR_DOMAIN_.*");
            group.Remove<CppEnumItem>(@"^D3D(\d+)_TESSELLATOR_PARTITIONING_.*");
            group.Remove<CppEnumItem>(@"^D3D(\d+)_REGISTER_COMPONENT_.*");

            group.TagName<CppEnum>(@"^D3D_PRIMITIVE$", @"InputPrimitive");
            group.TagName<CppEnumItem>(@"^D3D_FEATURE_LEVEL_(.*)", @"Level_$1", true);

            group.TagName<CppEnum>(@"^D3D_PRIMITIVE_TOPOLOGY$", "PrimitiveTopology");
            group.TagName<CppEnumItem>(@"^D3D_PRIMITIVE_TOPOLOGY_(.*)", "$1", false);

            group.TagName<CppEnum>(@"^D3D_SRV_DIMENSION$","ShaderResourceViewDimension");
            group.TagName<CppEnumItem>(@"^D3D_SRV_DIMENSION_(.*)$", "$1", false);


            group.TagName<CppEnumItem>(@"^D3D_PRIMITIVE_TOPOLOGY_(\d+)_CONTROL_POINT_PATCHLIST", "PatchListWith$1ControlPoints");
            group.TagName<CppEnumItem>(@"^D3D_PRIMITIVE_(\d+)_CONTROL_POINT_PATCH", "PatchWith$1ControlPoints");

            group.TagName<CppEnumItem>(@"^D3D_SVC_(.*)", "$1", false);
            group.TagName<CppEnumItem>(@"^D3D_SVF_(.*)", "$1", false);
            group.TagName<CppEnumItem>(@"^D3D_SVT_(.*)", "$1", false);
            group.TagName<CppEnumItem>(@"^D3D_SIF_(.*)", "$1", false);
            group.TagName<CppEnumItem>(@"^D3D_SIT_(.*)", "$1", false);
            group.TagName<CppEnumItem>(@"^D3D_CT_(.*)", "$1", false);

            group.TagName<CppEnum>(@"^D3D_DRIVER_TYPE$", "DriverType");
            group.TagName<CppEnumItem>(@"^D3D_DRIVER_TYPE_(.*)", "$1", false);

            group.TagName<CppEnum>(@"^D3D_NAME$", "ParameterName");
            group.TagName<CppEnumItem>(@"^D3D_NAME_(.*)", "$1", false);

            group.TagName<CppEnum>(@"^D3DCOMPILER_STRIP_FLAGS$", "StripFlags");

            group.TagName<CppEnum>(@"^D3D_INCLUDE_TYPE$", "IncludeType");
            group.TagName<CppEnumItem>(@"^D3D_INCLUDE_(.*)", "$1", false);

            group.TagName<CppEnumItem>(@"^D3D_RETURN_TYPE_(.*)", "$1", false);

            group.TagName<CppEnumItem>(@"^D3D_TESSELLATOR_OUTPUT_(.*)", "$1", false);

            group.TagName<CppEnumItem>(@"^D3D_TESSELLATOR_DOMAIN_(.*)", "$1", false);

            group.TagName<CppEnumItem>(@"^D3D_TESSELLATOR_PARTITIONING_(.*)", "$1", false);

            group.TagName<CppEnum>(@"^D3D_REGISTER_COMPONENT_TYPE$", "RegisterComponentType");
            group.TagName<CppEnumItem>(@"^D3D_REGISTER_COMPONENT_(.*)", "$1", false);

            // --------------------------------------------------------------------------------------------------------
            // D3DCommon Structures
            // --------------------------------------------------------------------------------------------------------
            // Those interfaces are only used as callback
            group.TagName<CppStruct>(@"^D3D(.*)", "$1", false);

            // --------------------------------------------------------------------------------------------------------
            // D3DCommon Interfaces
            // --------------------------------------------------------------------------------------------------------
            // Those interfaces are only used as callback
            group.TagName<CppInterface>(@"^ID3DInclude", "Include");
            group.TagCallback(@"^ID3DInclude$");

            group.TagName<CppInterface>(@"^ID3D10Blob", "Blob");

            // --------------------------------------------------------------------------------------------------------
            // D3DCommon Functions
            // --------------------------------------------------------------------------------------------------------
            D3DCommonFunctionGroup = gen.CreateFunctionGroup(assemblyName, namespaceName, "D3DCommon");


            group.FindContext.Clear();
        }
    }
}