/*
 * Copyright 2010, The Android Open Source Project
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef DrawExtra_h
#define DrawExtra_h

#include "config.h"

#include "Color.h"
#include "IntPoint.h"
#include "IntRect.h"
#include "wtf/HashMap.h"
#include "wtf/Vector.h"

// Color of the ring copied from framework's holo_light
#define COLOR_HOLO_LIGHT 0x6633B5E5
// Color of the ring copied from framework's holo_dark
#define COLOR_HOLO_DARK 0x660099CC

class SkCanvas;
class SkRegion;

namespace WebCore {
    class LayerAndroid;
    class GLExtras;
}

using namespace WebCore;

namespace android {

class DrawExtra {
public:
    virtual ~DrawExtra() {}
    virtual void draw(SkCanvas*, LayerAndroid*) {}
    virtual void drawGL(GLExtras*, const LayerAndroid*) {}
};

// A helper extra that has a SkRegion per LayerAndroid
class RegionLayerDrawExtra : public DrawExtra {
public:
    RegionLayerDrawExtra();
    virtual ~RegionLayerDrawExtra();

    void addHighlightRegion(const LayerAndroid* layer, const Vector<IntRect>& rects,
                            const IntPoint& additionalOffset = IntPoint());
    virtual void draw(SkCanvas*, LayerAndroid*);
    virtual void drawGL(GLExtras*, const LayerAndroid*);

private:
    SkRegion* getHighlightRegionsForLayer(const LayerAndroid* layer);

    typedef HashMap<int, SkRegion* > HighlightRegionMap;
    HighlightRegionMap m_highlightRegions;
    Color m_highlightColor;
};

}

#endif
