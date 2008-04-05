/*
* Copyright (c) 2007-2008 SlimDX Group
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
#pragma once

#include "Enums.h"
#include "Direct3D.h"
#include "VertexDeclaration.h"

#include "../Viewport.h"

#include "../math/Plane.h"

#include "PaletteEntry.h"
#include "Light.h"
#include "PatchInfo.h"
#include "Material.h"
#include "PresentParameters.h"
#include "GammaRamp.h"
#include "ClipStatus.h"
#include "CreationParameters.h"
#include "RasterStatus.h"

namespace SlimDX
{
	value class Matrix;

	namespace Direct3D9
	{
		ref class IndexBuffer;
		ref class VertexBuffer;
		ref class BaseTexture;
		ref class Texture;
		ref class Surface;
		ref class PixelShader;
		ref class VertexShader;
		ref class SwapChain;
		ref class StateBlock;

		/// <summary>
		/// Applications use the methods of the Device to perform DrawPrimitive-based rendering, create resources,
		/// work with system-level variables, adjust gamma ramp levels, work with palettes, and create shaders.
		/// </summary>
		/// <unmanaged>IDirect3DDevice9</unmanaged>
		public ref class Device : public ComObject
		{
			COMOBJECT(IDirect3DDevice9, Device);

		public:
			/// <summary>
			/// Initializes a new instance of the <see cref="SlimDX.Direct3D9.Device"/> class.
			/// </summary>
			/// <param name="adapter">Ordinal number that denotes the display adapter.</param>
			/// <param name="deviceType">Denotes the desired device type. If the desired device type is not available, device creation will fail.</param>
			/// <param name="controlHandle">Specifies the target window for Direct3D rendering.</param>
			/// <param name="createFlags">Combination of one or more options that control device creation.</param>
			/// <param name="presentParameters">Describes the presentation parameters for the device being created.</param>
			Device( int adapter, DeviceType deviceType, System::IntPtr controlHandle, CreateFlags createFlags, PresentParameters^ presentParameters );
			
			/// <summary>
			/// Constructs a new instance of the <see cref="Device"/> class using the specified pointer to a
			/// previously constructed unmanaged object.
			/// </summary>
			/// <returns>The newly constructed object.</returns>
			static Device^ FromPointer( System::IntPtr pointer );

			/// <summary>
			/// Determines whether the specified query type is supported by the device.
			/// </summary>
			/// <param name="type">The query type to check.</param>
			/// <returns><c>true</c> if the query is supported; otherwise, <c>false</c>.</returns>
			bool IsQuerySupported( QueryType type );

			/// <summary>
			/// Evicts all managed resources, including both Direct3D and driver-managed resources.
			/// </summary>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result EvictManagedResources();

			/// <summary>
			/// Reports on the device's ability to render the current texture-blending operations and arguments in a single pass.
			/// </summary>
			/// <returns>The number of passes required to complete the desired effect.</returns>
			int ValidateDevice();

			/// <summary>
			/// Reports the current cooperative-level status of the device.
			/// </summary>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result TestCooperativeLevel();

			/// <summary>
			/// Resets the device.
			/// </summary>
			/// <param name="presentParameters">A set of new presentation parameters to apply to the device.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result Reset( PresentParameters^ presentParameters );

			/// <summary>
			/// Clears one or more surfaces such as a render target, a stencil buffer, and a depth buffer.
			/// </summary>
			/// <param name="clearFlags">Flags that specify which surfaces will be cleared.</param>
			/// <param name="color">The color that will be used to fill the cleared render target.</param>
			/// <param name="zdepth">The value that will be used to fill the cleared depth buffer.</param>
			/// <param name="stencil">The value that will be used to fill the cleared stencil buffer.</param>
			/// <param name="rectangles">The areas on the surfaces that will be cleared.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result Clear( ClearFlags clearFlags, Color4 color, float zdepth, int stencil, array<System::Drawing::Rectangle>^ rectangles );
			
			/// <summary>
			/// Clears one or more surfaces such as a render target, a stencil buffer, and a depth buffer.
			/// </summary>
			/// <param name="clearFlags">Flags that specify which surfaces will be cleared.</param>
			/// <param name="color">The color that will be used to fill the cleared render target.</param>
			/// <param name="zdepth">The value that will be used to fill the cleared depth buffer.</param>
			/// <param name="stencil">The value that will be used to fill the cleared stencil buffer.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result Clear( ClearFlags clearFlags, Color4 color, float zdepth, int stencil );
			
			/// <summary>
			/// Begins a scene.
			/// </summary>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result BeginScene();
			
			/// <summary>
			/// Ends a scene.
			/// </summary>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result EndScene();

			/// <summary>
			/// Presents the contents of the next buffer in the sequence of back buffers to the screen.
			/// </summary>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result Present();

			/// <summary>
			/// Presents the contents of the first swap chain in the device. 
			/// </summary>
			/// <param name="flags">Flags used to specify how the swap chain should be presented.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result Present( SlimDX::Direct3D9::Present flags );

			/// <summary>
			/// Presents the contents of the next buffer in the sequence of back buffers to the screen.
			/// </summary>
			/// <param name="sourceRectangle">The area of the back buffer that should be presented.</param>
			/// <param name="destinationRectangle">The area of the front buffer that should receive the result of the presentation.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result Present( System::Drawing::Rectangle sourceRectangle, System::Drawing::Rectangle destinationRectangle );
			
			/// <summary>
			/// Presents the contents of the next buffer in the sequence of back buffers to the screen.
			/// </summary>
			/// <param name="sourceRectangle">The area of the back buffer that should be presented.</param>
			/// <param name="destinationRectangle">The area of the front buffer that should receive the result of the presentation.</param>
			/// <param name="windowOverride">The destination window whose client area is taken as the target for this presentation.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result Present( System::Drawing::Rectangle sourceRectangle, System::Drawing::Rectangle destinationRectangle, System::IntPtr windowOverride );
			
			/// <summary>
			/// Presents the contents of the next buffer in the sequence of back buffers to the screen.
			/// </summary>
			/// <param name="sourceRectangle">The area of the back buffer that should be presented.</param>
			/// <param name="destinationRectangle">The area of the front buffer that should receive the result of the presentation.</param>
			/// <param name="windowOverride">The destination window whose client area is taken as the target for this presentation.</param>
			/// <param name="region">Specifies a region on the back buffer that contains the minimal amount of pixels that need to be updated.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result Present( System::Drawing::Rectangle sourceRectangle, System::Drawing::Rectangle destinationRectangle, System::IntPtr windowOverride, System::Drawing::Region^ region );

			/// <summary>
			/// Retrieves a back buffer from the device's swap chain.
			/// </summary>
			/// <param name="swapChain">The desired swap chain.</param>
			/// <param name="backBuffer">Index of the back buffer object to return.</param>
			/// <returns>The requested back buffer surface.</returns>
			Surface^ GetBackBuffer( int swapChain, int backBuffer );

			/// <summary>
			/// Retrieves a render target surface.
			/// </summary>
			/// <param name="index">The index of the render target.</param>
			/// <returns>A surface representing the desired render target.</returns>
			Surface^ GetRenderTarget( int index );

			/// <summary>
			/// Gets a reference to the specified swap chain.
			/// </summary>
			/// <param name="swapChainIndex">The index of the desired swap chain.</param>
			/// <returns>The requested swap chain reference.</returns>
			SwapChain^ GetSwapChain( int swapChainIndex );

			/// <summary>
			/// Gets information describing the raster of the monitor on which the swap chain is presented.
			/// </summary>
			/// <param name="swapChain">The swap chain whose raster status is to be retrieved.</param>
			/// <returns>The raster status of the specified swap chain.</returns>
			RasterStatus GetRasterStatus( int swapChain );

			/// <summary>
			/// Retrieve's the display mode's spatial resolution, color resolution, and refresh frequency.
			/// </summary>
			/// <param name="swapChain">The index of the swap chain whose display mode is to be retrieved.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			DisplayMode GetDisplayMode( int swapChain );

			/// <summary>
			/// Gets the currently set user-defined clipping plane.
			/// </summary>
			/// <param name="index">Index of the desired clipping plane.</param>
			/// <returns>The requested clipping plane.</returns>
			Plane GetClipPlane( int index );

			/// <summary>
			/// Retrieves a render-state value for the device.
			/// </summary>
			/// <typeparam name="T">The type of the data being returned.</typeparam>
			/// <param name="state">The render state whose value is being requested.</param>
			/// <returns>The value of the requested render state.</returns>
			generic<typename T> where T : value class
				T GetRenderState( RenderState state );

			/// <summary>
			/// Retrieves a render-state value for the device.
			/// </summary>
			/// <param name="state">The render state whose value is being requested.</param>
			/// <returns>The value of the requested render state.</returns>
			int GetRenderState( RenderState state );

			/// <summary>
			/// Retrieves a sampler state value for the device.
			/// </summary>
			/// <typeparam name="T">The type of the data being returned.</typeparam>
			/// <param name="sampler">The sampler stage index.</param>
			/// <param name="type">The sampler state whose value is being requested.</param>
			/// <returns>The value of the requested sampler state.</returns>
			generic<typename T> where T : value class
				T GetSamplerState( int sampler, SamplerState type );

			/// <summary>
			/// Retrieves a sampler state value for the device.
			/// </summary>
			/// <param name="sampler">The sampler stage index.</param>
			/// <param name="type">The sampler state whose value is being requested.</param>
			/// <returns>The value of the requested sampler state.</returns>
			int GetSamplerState( int sampler, SamplerState type );

			/// <summary>
			/// Retrieves a texture stage state value for the device.
			/// </summary>
			/// <typeparam name="T">The type of the data being returned.</typeparam>
			/// <param name="stage">The texture stage.</param>
			/// <param name="type">The texture stage state whose value is being requested.</param>
			/// <returns>The value of the requested texture stage state.</returns>
			generic<typename T> where T : value class
				T GetTextureStageState( int stage, TextureStage type );

			/// <summary>
			/// Retrieves a texture stage state value for the device.
			/// </summary>
			/// <param name="stage">The texture stage.</param>
			/// <param name="type">The texture stage state whose value is being requested.</param>
			/// <returns>The value of the requested texture stage state.</returns>
			int GetTextureStageState( int stage, TextureStage type );

			/// <summary>
			/// Gets the texture assigned to the specified stage.
			/// </summary>
			/// <returns>The texture assigned to the specified stage.</returns>
			BaseTexture^ GetTexture( int stage );

			/// <summary>
			/// Retrieves a vertex buffer bound to the specified data stream.
			/// </summary>
			/// <param name="stream">A zero-based index specifying the data stream.</param>
			/// <param name="streamData">A vertex buffer representing the data stream.</param>
			/// <param name="offsetInBytes">The offset from the beginning of the stream to the beginning of vertex data, measured in bytes.</param>
			/// <param name="stride">The stride of the vertex data, in bytes.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result GetStreamSource( int stream, [Out] VertexBuffer^% streamData, [Out] int% offsetInBytes, [Out] int% stride );
			
			/// <summary>
			/// Gets the stream source frequency divider value.
			/// </summary>
			/// <param name="stream">A zero-based index specifying the data stream.</param>
			/// <returns>The frequency divider value.</returns>
			int GetStreamSourceFrequency( int stream );

			/// <summary>
			/// Generates a copy of the device's front buffer and places that copy into the specified surface.
			/// </summary>
			/// <param name="swapChain">Index of the swap chain whose front buffer is to be copied.</param>
			/// <param name="destinationSurface">The surface that will receive the copy of the front buffer.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result GetFrontBufferData( int swapChain, Surface^ destinationSurface );

			/// <summary>
			/// Copies the render-target data from device memory to system memory.
			/// </summary>
			/// <param name="renderTarget">A surface representing the render target.</param>
			/// <param name="destinationSurface">The surface which will receive the copy of the render target.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result GetRenderTargetData( Surface^ renderTarget, Surface^ destinationSurface );

			/// <summary>
			/// Sets a single device render-state parameter.
			/// </summary>
			/// <param name="state">The render state that is being modified.</param>
			/// <param name="value">The new value for the state.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result SetRenderState( RenderState state, int value );
			
			/// <summary>
			/// Sets a single device render-state parameter.
			/// </summary>
			/// <param name="state">The render state that is being modified.</param>
			/// <param name="value">The new value for the state.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result SetRenderState( RenderState state, bool value );
			
			/// <summary>
			/// Sets a single device render-state parameter.
			/// </summary>
			/// <param name="state">The render state that is being modified.</param>
			/// <param name="value">The new value for the state.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result SetRenderState( RenderState state, float value );
			
			/// <summary>
			/// Sets a single device render-state parameter.
			/// </summary>
			/// <typeparam name="T">The type of the render state value.</typeparam>
			/// <param name="state">The render state that is being modified.</param>
			/// <param name="value">The new value for the state.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			generic<typename T> where T : System::Enum
				Result SetRenderState( RenderState state, T value );

			/// <summary>
			/// Gets the individual color elements of the specified palette.
			/// </summary>
			/// <param name="paletteNumber">The palette whose color elements will be retrieved.</param>
			/// <returns>The individual color elements of the specified palette.</returns>
			array<PaletteEntry>^ GetPaletteEntries( int paletteNumber );

			/// <summary>
			/// Sets palette entries.
			/// </summary>
			/// <param name="paletteNumber">An ordinal number identifying the particular palette upon which the operation is to be performed.
			/// <param name="entries">The individual entries of the palette that are to be set. The length of the array is assumed to be 256.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result SetPaletteEntries( int paletteNumber, array<PaletteEntry>^ entries );

			/// <summary>
			/// Retrives the gamma correction ramp for the specified swap chain.
			/// </summary>
			/// <param name="swapChain">The swap chain whose gamma ramp is to be retrieved.</param>
			/// <returns>The requested gamma correction ramp.</returns>
			GammaRamp^ GetGammaRamp( int swapChain );

			/// <summary>
			/// Sets the gamma correction ramp for the specified swap chain.
			/// </summary>
			/// <param name="swapChain">The swap chain whose gamma ramp is to be set.</param>
			/// <param name="ramp">The gamma correction ramp.</param>
			/// <param name="calibrate"><c>true</c> to calibrate the gamma data, <c>false</c> to just submit it to the device.</param>
			void SetGammaRamp( int swapChain, GammaRamp^ ramp, bool calibrate );

			/// <summary>
			/// Sets the state value for the currently assigned texture.
			/// </summary>
			/// <param name="stage">Zero-based stage identifier for the texture. Devices can have up to eight textures, so the maximum value allowed is 7.</param>
			/// <param name="type">The texture state to set.</param>
			/// <param name="value">The new value for the state.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result SetTextureStageState( int stage, TextureStage type, int value );
			
			/// <summary>
			/// Sets the state value for the currently assigned texture.
			/// </summary>
			/// <param name="stage">Zero-based stage identifier for the texture. Devices can have up to eight textures, so the maximum value allowed is 7.</param>
			/// <param name="type">The texture state to set.</param>
			/// <param name="textureOperation">The new value for the state.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result SetTextureStageState( int stage, TextureStage type, TextureOperation textureOperation );
			
			/// <summary>
			/// Sets the state value for the currently assigned texture.
			/// </summary>
			/// <param name="stage">Zero-based stage identifier for the texture. Devices can have up to eight textures, so the maximum value allowed is 7.</param>
			/// <param name="type">The texture state to set.</param>
			/// <param name="textureArgument">The new value for the state.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result SetTextureStageState( int stage, TextureStage type, TextureArgument textureArgument );
			
			/// <summary>
			/// Sets the state value for the currently assigned texture.
			/// </summary>
			/// <param name="stage">Zero-based stage identifier for the texture. Devices can have up to eight textures, so the maximum value allowed is 7.</param>
			/// <param name="type">The texture state to set.</param>
			/// <param name="textureTransform">The new value for the state.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result SetTextureStageState( int stage, TextureStage type, TextureTransform textureTransform );
			
			/// <summary>
			/// Sets the state value for the currently assigned texture.
			/// </summary>
			/// <param name="stage">Zero-based stage identifier for the texture. Devices can have up to eight textures, so the maximum value allowed is 7.</param>
			/// <param name="type">The texture state to set.</param>
			/// <param name="value">The new value for the state.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result SetTextureStageState( int stage, TextureStage type, float value );

			/// <summary>
			/// Sets a sampler state's value.
			/// </summary>
			/// <param name="sampler">The sampler stage index.</param>
			/// <param name="type">The sampler state whose value is to be set.</param>
			/// <param name="value">The new value for the sampler state.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result SetSamplerState( int sampler, SamplerState type, int value );

			/// <summary>
			/// Sets a sampler state's value.
			/// </summary>
			/// <param name="sampler">The sampler stage index.</param>
			/// <param name="type">The sampler state whose value is to be set.</param>
			/// <param name="value">The new value for the sampler state.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result SetSamplerState( int sampler, SamplerState type, float value );

			/// <summary>
			/// Sets a sampler state's value.
			/// </summary>
			/// <param name="sampler">The sampler stage index.</param>
			/// <param name="type">The sampler state whose value is to be set.</param>
			/// <param name="textureAddress">The new value for the sampler state.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result SetSamplerState( int sampler, SamplerState type, TextureAddress textureAddress );

			/// <summary>
			/// Sets a sampler state's value.
			/// </summary>
			/// <param name="sampler">The sampler stage index.</param>
			/// <param name="type">The sampler state whose value is to be set.</param>
			/// <param name="textureFilter">The new value for the sampler state.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result SetSamplerState( int sampler, SamplerState type, TextureFilter textureFilter );

			/// <summary>
			/// Enables or disables a set of lighting parameters.
			/// </summary>
			/// <param name="lightIndex">The index of the light whose state is to be changed.</param>
			/// <param name="enable"><c>true</c> if the light should be enabled; otherwise, <c>false</c>.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result EnableLight( int lightIndex, bool enable );

			/// <summary>
			/// Gets a value indicating whether the specified light is enabled.
			/// </summary>
			/// <param name="lightIndex">The index of the light whose status is to be queried.</param>
			/// <returns><c>true</c> if the specified light is enabled; otherwise, <c>false</c>.</returns>
			bool IsLightEnabled( int lightIndex );

			/// <summary>
			/// Assigns a set of lighting properties to the device.
			/// </summary>
			/// <param name="lightIndex">Index of the light whose properties are to be set.</param>
			/// <param name="lightData">A <see cref="Light"/> structure which represents the light properties.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result SetLight( int lightIndex, Light lightData );

			/// <summary>
			/// Retrievs a set of lighting properties that are used by the device.
			/// </summary>
			/// <param name="lightIndex">Index of the light to be retrieved.</param>
			/// <returns>A <see cref="Light"/> structure describing the requested light.</returns>
			Light GetLight( int lightIndex );

			/// <summary>
			/// Sets a Windows Forms cursor as the device cursor.
			/// </summary>
			/// <param name="cursor">The cursor to set.</param>
			/// <param name="addWatermark"><c>true</c> to add a watermark to the cursor; otherwise, <c>false</c>.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result SetCursor( System::Windows::Forms::Cursor^ cursor, bool addWatermark );

			/// <summary>
			/// Sets the current cursor position.
			/// </summary>
			/// <param name="x">The new X-position of the cursor, in virtual desktop coordinates.</param>
			/// <param name="y">The new Y-position of the cursor, in virtual desktop coordinates.</param>
			/// <param name="immediateUpdate"><c>true</c> to force the cursor to update every time the monitor refreshes; otherwise, <c>false</c> to have the cursor update whenever <see cref="Device.Present"/> is called.</param>
			void SetCursorPosition( int x, int y, bool immediateUpdate );

			/// <summary>
			/// Sets the current cursor position.
			/// </summary>
			/// <param name="position">The position of the cursor, in virtual desktop coordinates.</param>
			/// <param name="immediateUpdate"><c>true</c> to force the cursor to update every time the monitor refreshes; otherwise, <c>false</c> to have the cursor update whenever <see cref="Device.Present"/> is called.</param>
			void SetCursorPosition( System::Drawing::Point position, bool immediateUpdate ) { SetCursorPosition( position.X, position.Y, immediateUpdate ); }
			
			/// <summary>
			/// Sets properties for the cursor.
			/// </summary>
			/// <param name="hotspotX">X-coordinate offset (in pixels) that marks the center of the cursor.</param>
			/// <param name="hotspotY">Y-coordinate offset (in pixels) that marks the center of the cursor.</param>
			/// <param name="cursorBitmap">The image data used to draw the cursor.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result SetCursorProperties( int hotspotX, int hotspotY, Surface^ cursorBitmap );
			
			/// <summary>
			/// Sets properties for the cursor.
			/// </summary>
			/// <param name="hotspot">The offset (in pixels) that marks the center of the cursor.</param>
			/// <param name="cursorBitmap">The image data used to draw the cursor.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result SetCursorProperties( System::Drawing::Point hotspot, Surface^ cursorBitmap ) { return SetCursorProperties( hotspot.X, hotspot.Y, cursorBitmap ); }

			/// <summary>
			/// Sets a single device transformation state.
			/// </summary>
			/// <param name="state">The transformation state which is to be set.</param>
			/// <param name="value">The new value for the transformation state.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result SetTransform( TransformState state, Matrix value );

			/// <summary>
			/// Retrieves a matrix describing the transformation state.
			/// </summary>
			/// <param name="state">The device state variable that is being retrieved.</param>
			/// <returns>The transformation matrix for the specified state.</returns>
			Matrix GetTransform( TransformState state );

			/// <summary>
			/// Sets a single device transformation state.
			/// </summary>
			/// <param name="index">The transformation state which is to be set.</param>
			/// <param name="value">The new value for the transformation state.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result SetTransform( int index, Matrix value );

			/// <summary>
			/// Retrieves a matrix describing the transformation state.
			/// </summary>
			/// <param name="index">The device state variable that is being retrieved.</param>
			/// <returns>The transformation matrix for the specified state.</returns>
			Matrix GetTransform( int index );
			
			/// <summary>
			/// Multiplies a device's world, view, or projection matrix by the specified matrix.
			/// </summary>
			/// <param name="state">The transformation state whose matrix is to be modified.</param>
			/// <param name="value">The matrix to multiply with the device transform.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result MultiplyTransform( TransformState state, Matrix value );

			/// <summary>
			/// Binds a vertex buffer to a device data stream.
			/// </summary>
			/// <param name="stream">The stream index to bind.</param>
			/// <param name="streamData">The stream data to bind.</param>
			/// <param name="offsetInBytes">Offset from the beginning of the stream to the beginning of the vertex data, in bytes.</param>
			/// <param name="stride">The stride of the vertex data.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result SetStreamSource( int stream, VertexBuffer^ streamData, int offsetInBytes, int stride );
			
			/// <summary>
			/// Sets the stream source frequency divider value. This may be used to draw several instances of geometry.
			/// </summary>
			/// <param name="stream">The stream index.</param>
			/// <param name="frequency">The new frequency divider.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result SetStreamSourceFrequency( int stream, int frequency );
			
			/// <summary>
			/// Assigns a texture to a stage.
			/// </summary>
			/// <param name="sampler">Zero-based sampler index.</param>
			/// <param name="texture">The texture that is to be bound.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result SetTexture( int sampler, BaseTexture^ texture );

			/// <summary>
			/// Sets a new render target for the device.
			/// </summary>
			/// <param name="targetIndex">Index of the render target.</param>
			/// <param name="target">The new render target.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result SetRenderTarget( int targetIndex, Surface^ target );

			/// <summary>
			/// This method allows the use of GDI dialog boxes in full-screen mode applications.
			/// </summary>
			/// <param name="enableDialogs"><c>true</c> to enable GDI dialogs, <c>false</c> to disable them.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result SetDialogBoxMode( bool enableDialogs );

			/// <summary>
			/// Sets the current user-defined clip plane.
			/// </summary>
			/// <param name="index">The index of the clipping plane to set.</param>
			/// <param name="clipPlane">The new clipping plane data.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result SetClipPlane( int index, Plane clipPlane );

			/// <summary>
			/// Gets a boolean vertex shader constant.
			/// </summary>
			/// <param name="startRegister">The register number containing the first constant value.</param>
			/// <param name="count">Number of values in the constant.</param>
			/// <returns>An array of boolean constants.</returns>
			array<bool>^ GetVertexShaderBooleanConstant( int startRegister, int count );

			/// <summary>
			/// Gets a floating point vertex shader constant.
			/// </summary>
			/// <param name="startRegister">The register number containing the first constant value.</param>
			/// <param name="count">Number of values in the constant.</param>
			/// <returns>An array of floating point constants.</returns>
			array<float>^ GetVertexShaderFloatConstant( int startRegister, int count );

			/// <summary>
			/// Gets an integer vertex shader constant.
			/// </summary>
			/// <param name="startRegister">The register number containing the first constant value.</param>
			/// <param name="count">Number of values in the constant.</param>
			/// <returns>An array of integer constants.</returns>
			array<int>^ GetVertexShaderIntegerConstant( int startRegister, int count );

			/// <summary>
			/// Gets a boolean pixel shader constant.
			/// </summary>
			/// <param name="startRegister">The register number containing the first constant value.</param>
			/// <param name="count">Number of values in the constant.</param>
			/// <returns>An array of boolean constants.</returns>
			array<bool>^ GetPixelShaderBooleanConstant( int startRegister, int count );

			/// <summary>
			/// Gets a floating point pixel shader constant.
			/// </summary>
			/// <param name="startRegister">The register number containing the first constant value.</param>
			/// <param name="count">Number of values in the constant.</param>
			/// <returns>An array of floating point constants.</returns>
			array<float>^ GetPixelShaderFloatConstant( int startRegister, int count );

			/// <summary>
			/// Gets an integer pixel shader constant.
			/// </summary>
			/// <param name="startRegister">The register number containing the first constant value.</param>
			/// <param name="count">Number of values in the constant.</param>
			/// <returns>An array of integer constants.</returns>
			array<int>^ GetPixelShaderIntegerConstant( int startRegister, int count );

			/// <summary>
			/// Sets a vertex shader constant.
			/// </summary>
			/// <param name="startRegister">Register number that will contain the first constant value.</param>
			/// <param name="data">The constant data.</param>
			/// <param name="offset">The offset into the data where constants will start being retrieved.</param>
			/// <param name="count">The number of constants to set.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result SetVertexShaderConstant( int startRegister, array<bool>^ data, int offset, int count );
			
			/// <summary>
			/// Sets a vertex shader constant.
			/// </summary>
			/// <param name="startRegister">Register number that will contain the first constant value.</param>
			/// <param name="data">The constant data.</param>
			/// <param name="offset">The offset into the data where constants will start being retrieved.</param>
			/// <param name="count">The number of constants to set.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result SetVertexShaderConstant( int startRegister, array<float>^ data, int offset, int count );
			
			/// <summary>
			/// Sets a vertex shader constant.
			/// </summary>
			/// <param name="startRegister">Register number that will contain the first constant value.</param>
			/// <param name="data">The constant data.</param>
			/// <param name="offset">The offset into the data where constants will start being retrieved.</param>
			/// <param name="count">The number of constants to set.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result SetVertexShaderConstant( int startRegister, array<int>^ data, int offset, int count );
			
			/// <summary>
			/// Sets a vertex shader constant.
			/// </summary>
			/// <param name="startRegister">Register number that will contain the first constant value.</param>
			/// <param name="data">The constant data.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result SetVertexShaderConstant( int startRegister, array<bool>^ data ) { return SetVertexShaderConstant( startRegister, data, 0, 0 ); }
			
			/// <summary>
			/// Sets a vertex shader constant.
			/// </summary>
			/// <param name="startRegister">Register number that will contain the first constant value.</param>
			/// <param name="data">The constant data.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result SetVertexShaderConstant( int startRegister, array<float>^ data ) { return SetVertexShaderConstant( startRegister, data, 0, 0 ); }
			
			/// <summary>
			/// Sets a vertex shader constant.
			/// </summary>
			/// <param name="startRegister">Register number that will contain the first constant value.</param>
			/// <param name="data">The constant data.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result SetVertexShaderConstant( int startRegister, array<int>^ data ) { return SetVertexShaderConstant( startRegister, data, 0, 0 ); }

			/// <summary>
			/// Sets a pixel shader constant.
			/// </summary>
			/// <param name="startRegister">Register number that will contain the first constant value.</param>
			/// <param name="data">The constant data.</param>
			/// <param name="offset">The offset into the data where constants will start being retrieved.</param>
			/// <param name="count">The number of constants to set.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result SetPixelShaderConstant( int startRegister, array<bool>^ data, int offset, int count );

			/// <summary>
			/// Sets a pixel shader constant.
			/// </summary>
			/// <param name="startRegister">Register number that will contain the first constant value.</param>
			/// <param name="data">The constant data.</param>
			/// <param name="offset">The offset into the data where constants will start being retrieved.</param>
			/// <param name="count">The number of constants to set.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result SetPixelShaderConstant( int startRegister, array<float>^ data, int offset, int count );

			/// <summary>
			/// Sets a pixel shader constant.
			/// </summary>
			/// <param name="startRegister">Register number that will contain the first constant value.</param>
			/// <param name="data">The constant data.</param>
			/// <param name="offset">The offset into the data where constants will start being retrieved.</param>
			/// <param name="count">The number of constants to set.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result SetPixelShaderConstant( int startRegister, array<int>^ data, int offset, int count );

			/// <summary>
			/// Sets a pixel shader constant.
			/// </summary>
			/// <param name="startRegister">Register number that will contain the first constant value.</param>
			/// <param name="data">The constant data.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result SetPixelShaderConstant( int startRegister, array<bool>^ data ) { return SetPixelShaderConstant( startRegister, data, 0, 0 ); }
			
			/// <summary>
			/// Sets a pixel shader constant.
			/// </summary>
			/// <param name="startRegister">Register number that will contain the first constant value.</param>
			/// <param name="data">The constant data.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result SetPixelShaderConstant( int startRegister, array<float>^ data ) { return SetPixelShaderConstant( startRegister, data, 0, 0 ); }
			
			/// <summary>
			/// Sets a pixel shader constant.
			/// </summary>
			/// <param name="startRegister">Register number that will contain the first constant value.</param>
			/// <param name="data">The constant data.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result SetPixelShaderConstant( int startRegister, array<int>^ data ) { return SetPixelShaderConstant( startRegister, data, 0, 0 ); }

			/// <summary>
			/// Signals Direct3D to begin recording a device-state block.
			/// </summary>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result BeginStateBlock();
			
			/// <summary>
			/// Signals Direct3D to stop recording a device-state block.
			/// </summary>
			/// <returns>The recorded device-state block.</returns>
			StateBlock^ EndStateBlock();

			/// <summary>
			/// Applies the vertex processing defined by the vertex shader to the set of input data streams,
			/// generating a single stream of interleaved vertex data to the destination vertex buffer.
			/// </summary>
			/// <param name="sourceStartIndex">Index of the first vertex to load.</param>
			/// <param name="destinationIndex">Index of the first vertex in the destination vertex buffer into which the results are placed.</param>
			/// <param name="vertexCount">Number of vertices to process.</param>
			/// <param name="destinationBuffer">The destination for the output vertex stream.</param>
			/// <param name="vertexDeclaration">The output vertex declaration.</param>
			/// <param name="flags">Vertex processing options.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result ProcessVertices( int sourceStartIndex, int destinationIndex, int vertexCount, VertexBuffer^ destinationBuffer, SlimDX::Direct3D9::VertexDeclaration^ vertexDeclaration, LockFlags flags );

			/// <summary>
			/// Renders non-indexed geometric primitives using data from the current input streams.
			/// </summary>
			/// <param name="primitiveType">Specifies the type of primitive to render.</param>
			/// <param name="startIndex">Index of the first vertex to use.</param>
			/// <param name="primitiveCount">The number of primitives to render. The number of vertices used is a function of the primitive count and the primitive type.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result DrawPrimitives( PrimitiveType primitiveType, int startIndex, int primitiveCount );
			
			/// <summary>
			/// Renders the specified geometric primitive using data from the current input streams.
			/// </summary>
			/// <param name="primitiveType">Specifies the type of primitive to render.</param>
			/// <param name="baseVertexIndex">Offset from the start of the vertex buffer to the first vertex.</param>
			/// <param name="minimumVertexIndex">Minimum vertex index for vertices used during this call. This is a zero-based index relative to <paramref name="baseVertexIndex">.</param>
			/// <param name="vertexCount">The number of vertices to render.</param>
			/// <param name="startIndex">Index of the first index to use when accessing the vertex buffer.</param>
			/// <param name="primitiveCount">The number of primitives to render. The number of vertices used is a function of the primitive count and the primitive type.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result DrawIndexedPrimitives( PrimitiveType primitiveType, int baseVertexIndex, int minimumVertexIndex, int vertexCount, int startIndex, int primitiveCount );

			/// <summary>
			/// Renders non-indexed geometric primitives using user-supplied data.
			/// </summary>
			/// <typeparam name="T">The type of the user-supplied vertices.</param>
			/// <param name="primitiveType">Specifies the type of primitive to render.</param>
			/// <param name="startIndex">Index of the first vertex to use.</param>
			/// <param name="primitiveCount">The number of primitives to render. The number of vertices used is a function of the primitive count and the primitive type.</param>
			/// <param name="data">User-supplied vertex data.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			generic<typename T> where T : value class
			Result DrawUserPrimitives( PrimitiveType primitiveType, int startIndex, int primitiveCount, array<T>^ data );

			/// <summary>
			/// Renders the specified geometric primitive using user-supplied data.
			/// </summary>
			/// <typeparam name="S">The type of the data contained in the index data.</typeparam>
			/// <typeparam name="T">The type of the data contained in the vertex data.</typeparam>
			/// <param name="primitiveType">Specifies the type of primitive to render.</param>
			/// <param name="minimumVertexIndex">Minimum vertex index for vertices used during this call.</param>
			/// <param name="vertexCount">The number of vertices to render.</param>
			/// <param name="primitiveCount">The number of primitives to render. The number of vertices used is a function of the primitive count and the primitive type.</param>
			/// <param name="indexData">User-supplied index data.</param>
			/// <param name="indexDataFormat">The format of the supplied index data.</param>
			/// <param name="vertexData">User-supplied vertex data.</param>
			/// <param name="vertexStride">The number of bytes of data for each vertex.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			generic<typename S, typename T> where S : value class where T : value class
			Result DrawIndexedUserPrimitives( PrimitiveType primitiveType, int minimumVertexIndex, int vertexCount, int primitiveCount, array<S>^ indexData, Format indexDataFormat, array<T>^ vertexData, int vertexStride );

			/// <summary>
			/// Draws a triangular patch using the currently set streams.
			/// </summary>
			/// <param name="handle">Handle to the triangular patch to draw.</param>
			/// <param name="segmentCounts">An array of three floating point values that identify the number of segments on each edge of the triangular patch.</param>
			/// <param name="info">Information on how to draw the triangular patch.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result DrawTrianglePatch( int handle, array<float>^ segmentCounts, TrianglePatchInfo info );
			
			/// <summary>
			/// Draws a triangular patch using the currently set streams.
			/// </summary>
			/// <param name="handle">Handle to the triangular patch to draw.</param>
			/// <param name="segmentCounts">An array of three floating point values that identify the number of segments on each edge of the triangular patch.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result DrawTrianglePatch( int handle, array<float>^ segmentCounts );
			
			/// <summary>
			/// Draws a rectangular patch using the currently set streams.
			/// </summary>
			/// <param name="handle">Handle to the rectangular patch to draw.</param>
			/// <param name="segmentCounts">An array of four floating point values that identify the number of segments on each edge of the rectangular patch.</param>
			/// <param name="info">Information on how to draw the rectangular patch.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result DrawRectanglePatch( int handle, array<float>^ segmentCounts, RectanglePatchInfo info );
			
			/// <summary>
			/// Draws a rectangular patch using the currently set streams.
			/// </summary>
			/// <param name="handle">Handle to the rectangular patch to draw.</param>
			/// <param name="segmentCounts">An array of four floating point values that identify the number of segments on each edge of the rectangular patch.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result DrawRectanglePatch( int handle, array<float>^ segmentCounts );
			
			/// <summary>
			/// Frees a cached high-order patch.
			/// </summary>
			/// <param name="handle">Handle of the cached high-order patch to delete.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result DeletePatch( int handle );

			/// <summary>
			/// Copys the contents of the source surface to the destination surface.
			/// </summary>
			/// <param name="source">The source surface.</param>
			/// <param name="sourceRectangle">The area on the source surface that is to be copied.</param>
			/// <param name="destination">The destination surface.</param>
			/// <param name="destinationRectangle">The area on the destination surface where data will be copied.</param>
			/// <param name="filter">The filter that will be used when the data is being stretched.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result StretchRectangle( Surface^ source, System::Drawing::Rectangle sourceRectangle, Surface^ destination, System::Drawing::Rectangle destinationRectangle, TextureFilter filter );
			
			/// <summary>
			/// Copys the contents of the source surface to the destination surface.
			/// </summary>
			/// <param name="source">The source surface.</param>
			/// <param name="destination">The destination surface.</param>
			/// <param name="filter">The filter that will be used when the data is being stretched.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result StretchRectangle( Surface^ source, Surface^ destination, TextureFilter filter );

			/// <summary>
			/// Copies rectangular subsets of pixels from one surface to another.
			/// </summary>
			/// <param name="source">The source surface.</param>
			/// <param name="sourceRectangle">The area on the source surface that is to be copied.</param>
			/// <param name="destination">The destination surface.</param>
			/// <param name="destinationPoint">The location on the destination surface where data will be copied.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result UpdateSurface( Surface^ source, System::Drawing::Rectangle sourceRectangle, Surface^ destination, System::Drawing::Point destinationPoint );
			
			/// <summary>
			/// Copies rectangular subsets of pixels from one surface to another.
			/// </summary>
			/// <param name="source">The source surface.</param>
			/// <param name="destination">The destination surface.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result UpdateSurface( Surface^ source, Surface^ destination );

			/// <summary>
			/// Updates the dirty portions of a texture.
			/// </summary>
			/// <param name="sourceTexture">The source texture.</param>
			/// <param name="destinationTexture">The destination texture.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result UpdateTexture( BaseTexture^ sourceTexture, BaseTexture^ destinationTexture );
			
			/// <summary>
			/// Fills a rectangular area of a surface with the specified color.
			/// </summary>
			/// <param name="destinationSurface">The surface that will be filled.</param>
			/// <param name="destinationRectangle">The area on the surface that will be filled.</param>
			/// <param name="color">The color used for filling.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result ColorFill( Surface^ destinationSurface, System::Drawing::Rectangle destinationRectangle, Color4 color );
			
			/// <summary>
			/// Fills a rectangular area of a surface with the specified color.
			/// </summary>
			/// <param name="destinationSurface">The surface that will be filled.</param>
			/// <param name="color">The color used for filling.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result ColorFill( Surface^ destinationSurface, Color4 color );

			/// <summary>
			/// Enables or disables render-to-vertex-buffer mode.
			/// </summary>
			/// <param name="enableR2VB"><c>true</c> to enable render-to-vertex-buffer mode, <c>false</c> to disable it.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result SetR2VBMode( bool enableR2VB );

			/// <summary>
			/// Binds a render target to a vertex stream.
			/// </summary>
			/// <param name="sampler">The sampler that will be used to bind the render target.</param>
			/// <param name="r2vbTarget">The target of the binding operation.</param>
			/// <param name="stream">The stream index that will be bound to the texture.</param>
			/// <param name="stride">The stride of the vertex data.</param>
			/// <param name="dummyVertexBuffer">A vertex buffer that is used to fill a required parameter in <see cref="Device.SetStreamSource"/>.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result BindRenderTargetToVertexStream( R2VBSampler sampler, Texture^ r2vbTarget, int stream, int stride, VertexBuffer^ dummyVertexBuffer );
			
			/// <summary>
			/// Unbinds a previously bound vertex buffer as a render target.
			/// </summary>
			/// <param name="stream">The vertex stream that should be unbound.
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result RestoreVertexStream( int stream );

			/// <summary>
			/// Gets the capabilities of the rendering device.
			/// </summary>
			property Capabilities^ Capabilities
			{
				SlimDX::Direct3D9::Capabilities^ get();
			}

			/// <summary>
			/// Gets the parameters used to create the device.
			/// </summary>
			property CreationParameters CreationParameters
			{
				SlimDX::Direct3D9::CreationParameters get();
			}

			/// <summary>
			/// Gets the current clip status.
			/// </summary>
			property ClipStatus ClipStatus
			{
				SlimDX::Direct3D9::ClipStatus get();
				void set( SlimDX::Direct3D9::ClipStatus value );
			}

			/// <summary>
			/// Gets or sets the current fixed-function vertex format.
			/// </summary>
			property VertexFormat VertexFormat
			{
				SlimDX::Direct3D9::VertexFormat get();
				void set( SlimDX::Direct3D9::VertexFormat value );
			}

			/// <summary>
			/// Gets or sets the current vertex declaration.
			/// </summary>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			property SlimDX::Direct3D9::VertexDeclaration^ VertexDeclaration
			{
				SlimDX::Direct3D9::VertexDeclaration^ get();
				void set( SlimDX::Direct3D9::VertexDeclaration^ value );
			}

			/// <summary>
			/// Gets or sets the vertex processing mode.
			/// </summary>
			/// <value><c>true</c> if the device is using software vertex processing; otherwise, <c>false</c>.</value>
			property bool SoftwareVertexProcessing
			{
				bool get();
				void set( bool value );
			}

			/// <summary>
			/// Gets or sets the current material properties used by the device.
			/// </summary>
			property Material Material
			{
				SlimDX::Direct3D9::Material get();
				void set( SlimDX::Direct3D9::Material value );
			}

			/// <summary>
			/// Gets or sets the currently active viewport.
			/// </summary>
			property SlimDX::Viewport Viewport
			{
				SlimDX::Viewport get();
				void set( SlimDX::Viewport value );
			}

			/// <summary>
			/// Gets or sets the current scissor rectangle.
			/// </summary>
			property System::Drawing::Rectangle ScissorRect
			{
				System::Drawing::Rectangle get();
				void set( System::Drawing::Rectangle value );
			}

			/// <summary>
			/// Gets an estimate of the amount of available texture memory.
			/// </summary>
			/// <value>The amount of available texture memory, rounded to the nearest MB.</value>
			property long AvailableTextureMemory
			{
				long get();
			}

			/// <summary>
			/// Gets or sets a value indicating whether the cursor should be shown.
			/// </summary>
			property bool ShowCursor
			{
				bool get();
				void set( bool show );
			}

			/// <summary>
			/// Gets the number of implicitly created swap chains.
			/// </summary>
			property int SwapChainCount
			{
				int get();
			}

			/// <summary>
			/// Gets or sets the current N-patch mode segments.
			/// </summary>
			/// <value>The number of subdivision segments. If the value is less than 1.0, N-patches are disabled.</value>
			property float NPatchMode
			{
				float get();
				void set( float value );
			}

			/// <summary>
			/// Gets or sets the index of the current texture palette.
			/// </summary>
			/// <returns>An index into the list of possible texture palettes.</returns>
			property int CurrentTexturePalette
			{
				int get();
				void set( int value );
			}

			/// <summary>
			/// Gets the current driver version.
			/// </summary>
			property DriverLevel DriverLevel
			{
				SlimDX::Direct3D9::DriverLevel get();
			}

			/// <summary>
			/// Gets the vertex shader version.
			/// </summary>
			property System::String^ VertexShaderProfile
			{
				System::String^ get();
			}

			/// <summary>
			/// Gets the pixel shader version.
			/// </summary>
			property System::String^ PixelShaderProfile
			{
				System::String^ get();
			}

			/// <summary>
			/// Gets or sets the current depth-stencil surface.
			/// </summary>
			property Surface^ DepthStencilSurface
			{
				Surface^ get();
				void set( Surface^ value );
			}

			/// <summary>
			/// Gets or sets the current index data.
			/// </summary>
			property IndexBuffer^ Indices
			{
				IndexBuffer^ get();
				void set( IndexBuffer^ value );
			}

			/// <summary>
			/// Gets or sets the currently active vertex shader.
			/// </summary>
			property VertexShader^ VertexShader
			{
				SlimDX::Direct3D9::VertexShader^ get();
				void set( SlimDX::Direct3D9::VertexShader^ value );
			}

			/// <summary>
			/// Gets or sets the currently active pixel shader.
			/// </summary>
			property PixelShader^ PixelShader
			{
				SlimDX::Direct3D9::PixelShader^ get();
				void set( SlimDX::Direct3D9::PixelShader^ value );
			}
		};
	}
}
