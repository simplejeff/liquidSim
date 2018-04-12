#include "FBO.h"

#include "GL/glew.h"

#include "GraphicsDebug.h"
#include "RenderBuffer.h"
#include "DepthBuffer.h"
#include "Texture2D.h"
#include "libs/gl/textures/TextureParametersBuilder.h"


FBO::FBO(int numberOfColorAttachments, DEPTH_STENCIL_ATTACHMENT attachmentType, int width, int height,
         TextureParameters::WRAP_METHOD wrapMethod,
         TextureParameters::FILTER_METHOD filterMethod, GLenum type) :
    m_depthStencilAttachmentType(attachmentType),
    m_handle(0),
    m_width(width),
    m_height(height)
{
    // TODO [Task 2]
    // Generate a new framebuffer using m_handle
    glGenFramebuffers(1, &m_handle);

    bind();
    // TODO [Task 3]
    // Call bind() and fill it in with glBindFramebuffer
    // Call generateColorAttachments() and fill in generateColorAttachment()
    generateColorAttachments(numberOfColorAttachments, wrapMethod, filterMethod, type);
    // TODO [Task 8] Call generateDepthStencilAttachment()
    generateDepthStencilAttachment();
    // This will make sure your framebuffer was generated correctly!
    checkFramebufferStatus();

    // TODO [Task 3] Call unbind() and fill it in
    unbind();
}


FBO::FBO(int width, int height, int numberOfColorAttachments, int numColorComponents, DEPTH_STENCIL_ATTACHMENT attachmentType,
         Texture::FILTER_METHOD filterMethod,
         Texture::WRAP_METHOD wrapMethod, Texture::DATA_TYPE type) :
    m_handle(0),
    m_width(width),
    m_height(height),
    m_depthStencilAttachmentType(attachmentType)
{

    glGenFramebuffers(1, &m_handle);
    bind();
    generateColorAttachments(numberOfColorAttachments, numColorComponents, filterMethod, wrapMethod, type);
    generateDepthStencilAttachment();
    checkFramebufferStatus();
    unbind();
}

FBO::~FBO()
{
    glDeleteFramebuffers(1, &m_handle);
}

void FBO::generateColorAttachments(int count, TextureParameters::WRAP_METHOD wrapMethod,
                                   TextureParameters::FILTER_METHOD filterMethod, GLenum type) {
    std::vector<GLenum> buffers;
    for (int i = 0; i < count; i++) {
        generateColorAttachment(i, wrapMethod, filterMethod, type);
        buffers.push_back(GL_COLOR_ATTACHMENT0 + i);
    }
    // TODO [Task 3] Call glDrawBuffers
    glDrawBuffers(count, &buffers[0]);
}

void FBO::generateColorAttachments(int count, int numComponents, Texture::FILTER_METHOD filterMethod,
                                   Texture::WRAP_METHOD wrapMethod, Texture::DATA_TYPE type) {
    std::vector<GLenum> buffers;
    for (int i = 0; i < count; i++) {
        generateColorAttachment(i, numComponents, filterMethod, wrapMethod, type);
        buffers.push_back(GL_COLOR_ATTACHMENT0 + i);
    }
    glDrawBuffers(count, &buffers[0]);

}

void FBO::generateDepthStencilAttachment() {
    switch(m_depthStencilAttachmentType) {
    case DEPTH_STENCIL_ATTACHMENT::DEPTH_ONLY:
        m_depthAttachment = std::make_unique<DepthBuffer>(m_width, m_height, false);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthAttachment->id());
        break;
    case DEPTH_STENCIL_ATTACHMENT::DEPTH_STENCIL:
        m_depthAttachment = std::make_unique<DepthBuffer>(m_width, m_height, true);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depthAttachment->id());
        break;
    case DEPTH_STENCIL_ATTACHMENT::NONE:
        break;
    }
}

void FBO::generateColorAttachment(int i, TextureParameters::WRAP_METHOD wrapMethod,
                                  TextureParameters::FILTER_METHOD filterMethod, GLenum type) {
    Texture2D tex(nullptr, m_width, m_height, type);
    TextureParametersBuilder builder;

    // TODO [Task 2]
    // - Set the filter method using builder.setFilter() with filterMethod
    // - Set the wrap method using builder.setWrap() with wrapMethod
    builder.setFilter(filterMethod);
    builder.setWrap(wrapMethod);
    TextureParameters parameters = builder.build();
    parameters.applyTo(tex);

    // TODO [Task 3] Call glFramebufferTexture2D using tex.id()
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0+i, GL_TEXTURE_2D, tex.id(), 0);
    m_colorAttachments.push_back(std::move(tex));
}

void FBO::generateColorAttachment(int i, int numComponents, Texture::FILTER_METHOD filterMethod,
                                  Texture::WRAP_METHOD wrapMethod, Texture::DATA_TYPE type) {
    Texture2D tex(nullptr, m_width, m_height, type, numComponents);
    tex.setTextureParams(filterMethod, wrapMethod);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0+i, GL_TEXTURE_2D, tex.id(), 0);
    m_colorAttachments.push_back(std::move(tex));
}

void FBO::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, m_handle);
    glViewport(0, 0, m_width, m_height);
}

void FBO::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

const Texture2D& FBO::getColorAttachment(int i) const {
    return m_colorAttachments.at(i);
}

const RenderBuffer& FBO::getDepthStencilAttachment() const {
    return *(m_depthAttachment.get());
}

size_t FBO::getNumColorAttachments() const {
    return m_colorAttachments.size();
}

void FBO::copyDepthFrom(const FBO &other) {
    glBindFramebuffer(GL_READ_FRAMEBUFFER, other.id());
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_handle);
    glBlitFramebuffer(0, 0, other.width(), other.height(),
                      0, 0, m_width, m_height,
                      GL_DEPTH_BUFFER_BIT,
                      GL_NEAREST);
}

void FBO::copyDepthStencilFrom(const FBO &other) {
    glBindFramebuffer(GL_READ_FRAMEBUFFER, other.id());
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_handle);
    glBlitFramebuffer(0, 0, other.width(), other.height(),
                      0, 0, m_width, m_height,
                      GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT,
                      GL_NEAREST);
}
