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

#include <windows.h>
#include <mmreg.h>
#include <dsound.h>
#include <d3dx9.h>

#include "../ComObject.h"
#include "../Result.h"
#include "Enums.h"
#include "DirectSoundException.h"
#include "SoundEffectDistortion.h"

using namespace System;
using namespace System::IO;

namespace SlimDX
{
namespace DirectSound
{
	DistortionParameters::DistortionParameters( const DSFXDistortion &value )
	{
		Gain = value.fGain;
		Edge = value.fEdge;
		PostEQCenterFrequency = value.fPostEQCenterFrequency;
		PostEQBandwidth = value.fPostEQBandwidth;
		PreLowpassCutoff = value.fPreLowpassCutoff;
	}

	DSFXDistortion DistortionParameters::Marshal()
	{
		DSFXDistortion result;
		result.fGain = Gain;
		result.fEdge = Edge;
		result.fPostEQCenterFrequency = PostEQCenterFrequency;
		result.fPostEQBandwidth = PostEQBandwidth;
		result.fPreLowpassCutoff = PreLowpassCutoff;

		return result;
	}

	SoundEffectDistortion::SoundEffectDistortion( System::IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	SoundEffectDistortion::SoundEffectDistortion( IDirectSoundFXDistortion *pointer )
	{
		if( pointer == NULL )
			throw gcnew System::ArgumentNullException();

		IDirectSoundFXDistortion8* result;
		HRESULT hr = pointer->QueryInterface( IID_IDirectSoundFXDistortion8, reinterpret_cast<void**>( &result ) );
		if( RECORD_DSOUND( hr ).IsFailure )
			throw gcnew DirectSoundException( Result::Last );

		Construct( result );
	}

	SoundEffectDistortion^ SoundEffectDistortion::FromPointer( IDirectSoundFXDistortion* pointer )
	{
		SoundEffectDistortion^ tableEntry = safe_cast<SoundEffectDistortion^>( ObjectTable::Find( static_cast<System::IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			pointer->Release();
			return tableEntry;
		}

		return gcnew SoundEffectDistortion( pointer );
	}

	SoundEffectDistortion^ SoundEffectDistortion::FromPointer( System::IntPtr pointer )
	{
		SoundEffectDistortion^ tableEntry = safe_cast<SoundEffectDistortion^>( ObjectTable::Find( static_cast<System::IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew SoundEffectDistortion( pointer );
	}

	SoundEffectDistortion::~SoundEffectDistortion()
	{
		Destruct();
	}

	DistortionParameters SoundEffectDistortion::AllParameters::get()
	{
		DSFXDistortion result;
		HRESULT hr = InternalPointer->GetAllParameters( &result );
		RECORD_DSOUND( hr );

		return DistortionParameters( result );
	}

	void SoundEffectDistortion::AllParameters::set( DistortionParameters value )
	{
		DSFXDistortion result = value.Marshal();
		HRESULT hr = InternalPointer->SetAllParameters( &result );
		RECORD_DSOUND( hr );
	}
}
}