/*
MIT License

Copyright(c) 2018-2019 megai2

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

UINT d912pxy_cbuffer::memUsage_V = 0;
UINT d912pxy_cbuffer::memUsage_UL = 0;

d912pxy_cbuffer::d912pxy_cbuffer(UINT length, bool isUpload, const wchar_t* name) : d912pxy_resource(RTID_CBUFFER, PXY_COM_OBJ_NOVTABLE, name)
{
	if ((length & 0xFF) != 0)
	{
		length = (length & ~0xFF) + 0x100;
	}

	dHeap = 0;

	if (isUpload)
	{
		d12res_buffer(length, D3D12_HEAP_TYPE_UPLOAD);
		memUsage_UL += length;
		LOG_ERR_THROW(m_res->Map(0, 0, (void**)&pointers.host));
	}
	else {
		d12res_uav_buffer(length, D3D12_HEAP_TYPE_DEFAULT);
		memUsage_V += length;
		pointers.dev = GetVA_GPU();
	}

	LOG_DX_SET_NAME(m_res, name);		
}

d912pxy_cbuffer::~d912pxy_cbuffer()
{
	//megai2: we never see this reported 
	//memUsage_V -= iSize;
	//memUsage_UL -= iSize;
}

void d912pxy_cbuffer::UploadTarget(ID3D12GraphicsCommandList* cl, d912pxy_cbuffer * target, UINT offset, UINT size)
{	
	cl->CopyBufferRegion(target->GetD12Obj(), offset, m_res, 0, size);	
}
