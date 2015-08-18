/*
 * Copyright (C) 2015 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ANDROID_DRM_COMPOSITION_H_
#define ANDROID_DRM_COMPOSITION_H_

#include "drm_hwcomposer.h"
#include "drmdisplaycomposition.h"
#include "drmplane.h"
#include "importer.h"

#include <deque>
#include <map>
#include <vector>

#include <hardware/hardware.h>
#include <hardware/hwcomposer.h>

namespace android {

struct DrmCompositionDisplayLayersMap {
  int display;
  size_t num_layers;
  hwc_layer_1_t *layers;
  size_t *layer_indices;
};

class DrmComposition {
 public:
  DrmComposition(DrmResources *drm, Importer *importer);

  int Init();

  int SetLayers(size_t num_displays,
                const DrmCompositionDisplayLayersMap *maps);
  int SetDpmsMode(int display, uint32_t dpms_mode);

  std::unique_ptr<DrmDisplayComposition> TakeDisplayComposition(int display);
  DrmDisplayComposition *GetDisplayComposition(int display);
  int DisableUnusedPlanes();

 private:
  DrmComposition(const DrmComposition &) = delete;

  DrmResources *drm_;
  Importer *importer_;

  std::vector<DrmPlane *> primary_planes_;
  std::vector<DrmPlane *> overlay_planes_;

  /*
   * This _must_ be read-only after it's passed to QueueComposition. Otherwise
   * locking is required to maintain consistency across the compositor threads.
   */
  std::map<int, std::unique_ptr<DrmDisplayComposition>> composition_map_;
};
}

#endif  // ANDROID_DRM_COMPOSITION_H_
