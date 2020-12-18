/*
MIT License

Copyright(c) 2020 megai2

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/
#include "stdafx.h"

using namespace d912pxy::extras::IFrameMods;

StateHolder::StateHolder(const d912pxy_replay_thread_context& rpState, uint32_t statesToBeChanged)
	: prevState(rpState)
	, restorationMask(statesToBeChanged)
{
}

StateHolder::~StateHolder()
{
	if (restorationMask & ST_PSO)
		prevState.cl->SetPipelineState(prevState.pso);

	if (restorationMask & ST_INDEX)
		prevState.tracked.indexBuf->IFrameBindIB(prevState.cl);

	if (restorationMask & ST_VSTREAM0)
	{
		prevState.tracked.streams[0].buffer->IFrameBindVB(
			prevState.tracked.streams[0].stride,
			0,
			prevState.tracked.streams[0].offset,
			prevState.cl
		);
	}

	if (restorationMask & ST_PRIMTOPO)
	{
		prevState.cl->IASetPrimitiveTopology((D3D12_PRIMITIVE_TOPOLOGY)prevState.tracked.primType);
	}
}
