/*
// Copyright (c) 2016 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
*/

#ifndef COMMON_COMPOSITOR_GL_GLSURFACE_H_
#define COMMON_COMPOSITOR_GL_GLSURFACE_H_

#include "nativesurface.h"

#include "shim.h"

namespace hwcomposer {

class GLSurface : public NativeSurface {
 public:
  GLSurface() = default;
  ~GLSurface() override;
  GLSurface(uint32_t width, uint32_t height);

  bool MakeCurrent() override;

 private:
  bool InitializeGPUResources();
  GLuint fb_ = 0;
};

}  // namespace hwcomposer
#endif  // COMMON_COMPOSITOR_GL_GLSURFACE_H_
