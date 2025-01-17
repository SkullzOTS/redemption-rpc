/*
 * Copyright (c) 2010-2022 OTClient <https://github.com/edubart/otclient>
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

#include "declarations.h"

class Texture
{
public:
    Texture();
    Texture(const Size& size);
    Texture(const ImagePtr& image, bool buildMipmaps = false, bool compress = false, bool canSuperimposed = false, bool load = true);
    virtual ~Texture();

    void uploadPixels(const ImagePtr& image, bool buildMipmaps = false, bool compress = false);
    void updateImage(const ImagePtr& image) { m_image = image; }
    void bind();
    void copyFromScreen(const Rect& screenRect);
    virtual bool buildHardwareMipmaps();

    virtual void setSmooth(bool smooth);
    virtual void setRepeat(bool repeat);
    void setUpsideDown(bool upsideDown);
    void setTime(ticks_t time) { m_time = time; }

    uint32_t getId() { return m_id; }
    uint32_t getUniqueId() const { return m_uniqueId; }
    ticks_t getTime() { return m_time; }
    int getWidth() { return m_size.width(); }
    int getHeight() { return m_size.height(); }
    const Size& getSize() { return m_size; }
    const Matrix3& getTransformMatrix() { return m_transformMatrix; }
    bool isEmpty() { return m_id == 0; }
    bool hasRepeat() { return m_repeat; }
    bool hasMipmaps() { return m_hasMipmaps; }
    virtual bool isAnimatedTexture() { return false; }
    bool isOpaque() const { return m_opaque; }
    bool canSuperimposed() const { return m_canSuperimposed; }

    void create();

protected:
    void createTexture();
    bool setupSize(const Size& size);
    void setupWrap();
    void setupFilters();
    void setupTranformMatrix();
    void setupPixels(int level, const Size& size, uint8_t* pixels, int channels = 4, bool compress = false);

    const uint32_t m_uniqueId;

    uint32_t m_id{ 0 };
    ticks_t m_time{ 0 };
    Size m_size;

    Matrix3 m_transformMatrix;

    ImagePtr m_image;

    bool m_hasMipmaps{ false };
    bool m_smooth{ false };
    bool m_upsideDown{ false };
    bool m_repeat{ false };
    bool m_opaque{ false };
    bool m_canSuperimposed{ false };
    bool m_compress{ false };
    bool m_buildMipmaps{ false };
};
