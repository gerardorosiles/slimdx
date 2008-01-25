/*
* Copyright (c) 2007 SlimDX Group
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

#include <d3d10.h>
#include <d3dx10.h>

#include "Direct3D10ErrorHandler.h"

#include "RasterizerState.h"
#include "Device.h"

namespace SlimDX
{
namespace Direct3D10
{ 
	RasterizerState::RasterizerState( ID3D10RasterizerState* state )
	{
		if( state == NULL )
			throw gcnew ArgumentNullException( "state" );

		Construct(state);
		
		D3D10_RASTERIZER_DESC desc;
		state->GetDesc( &desc );
		m_Description = gcnew RasterizerStateDescription( desc );
	}
	
	RasterizerState::RasterizerState( IntPtr state )
	{
		Construct( state, NativeInterface );

		D3D10_RASTERIZER_DESC desc;
		InternalPointer->GetDesc( &desc );
		m_Description = gcnew RasterizerStateDescription( desc );
	}

	RasterizerState::RasterizerState( Device^ device, RasterizerStateDescription^ description )
	{
		if( device == nullptr )
			throw gcnew ArgumentNullException( "device" );
		if( description == nullptr )
			throw gcnew ArgumentNullException( "description" );
		
		D3D10_RASTERIZER_DESC desc;
		m_Description = description;
		m_Description->FillNativeObject( desc );
		
		ID3D10RasterizerState* state;
		HRESULT hr = device->InternalPointer->CreateRasterizerState( &desc, &state );
		Direct3D10ErrorHandler::TestForFailure( hr );
		
		Construct(state);
	}
	
	RasterizerStateDescription^ RasterizerState::CloneDescription()
	{
		D3D10_RASTERIZER_DESC desc;
		InternalPointer->GetDesc( &desc );
		return gcnew RasterizerStateDescription( desc );
	}
}
}
