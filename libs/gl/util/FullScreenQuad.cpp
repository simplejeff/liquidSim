#include "FullScreenQuad.h"

#include <vector>

#include "src/engine/graphics/VBO.h"
#include "src/engine/graphics/VBO_attrib_marker.h"
#include "src/engine/graphics/VAO.h"
#include "src/engine/graphics/shader_attrib_locations.h"

FullScreenQuad::FullScreenQuad()
{
    float data[] = { -1.0f,  1.0f,   0.0f, 1.0f,
                     -1.0f, -1.0f,   0.0f, 0.0f,
                      1.0f,  1.0f,   1.0f, 1.0f,
                      1.0f, -1.0f,   1.0f, 0.0f };

    std::vector<VBOAttribMarker> attribs;
    attribs.push_back(VBOAttribMarker(ShaderAttrib::POSITION, 2, 0));
    attribs.push_back(VBOAttribMarker(ShaderAttrib::TEXCOORD0, 2, 2*sizeof(float)));
    VBO vbo(data, sizeof(data), attribs, VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLE_STRIP);
    m_vao = std::make_unique<VAO>(vbo, 4);
}

void FullScreenQuad::draw() {
    m_vao->bind();
    m_vao->draw();
    m_vao->unbind();
}
