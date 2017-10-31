/*
KVMGFX Client - A KVM Client for VGA Passthrough
Copyright (C) 2017 Geoffrey McRae <geoff@hostfission.com>

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place, Suite 330, Boston, MA 02111-1307 USA
*/

#pragma once
#include "ICapture.h"
#include "MTMemcpy.h"

#define W32_LEAN_AND_MEAN
#include <Windows.h>

#include <NvFBC\nvFBC.h>
#include <NvFBC\nvFBCToSys.h>

namespace Capture
{
  class NvFBC : public ICapture
  {
  public:
    NvFBC();
    ~NvFBC();

    bool Initialize();
    void DeInitialize();
    enum FrameType GetFrameType();
    enum FrameComp GetFrameCompression();
    size_t GetMaxFrameSize();
    bool GrabFrame(struct FrameInfo & frame);

  private:
    bool m_initialized;
    HMODULE  m_hDLL;
    MTMemcpy m_memcpy;

    NvFBC_CreateFunctionExType    m_fnCreateEx;
    NvFBC_SetGlobalFlagsType      m_fnSetGlobalFlags;
    NvFBC_GetStatusExFunctionType m_fnGetStatusEx;
    NvFBC_EnableFunctionType      m_fnEnable;

    DWORD m_maxCaptureWidth, m_maxCaptureHeight;
    NvFBCToSys * m_nvFBC;
    void * m_frameBuffer;
    NvFBCFrameGrabInfo m_grabInfo;
    NVFBC_TOSYS_GRAB_FRAME_PARAMS m_grabFrameParams;
  };
};