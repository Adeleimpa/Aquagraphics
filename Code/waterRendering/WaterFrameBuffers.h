/*
// Code adapted from ThinMatrix 
// Tutorial series about programming 3D water using OpenGL!
*/

#ifndef WATER_FB_H
#define WATER_FB_H

#include <iostream>
#include <glm/glm.hpp>

class WaterFrameBuffers {

private:
    const int SCR_WIDTH = 800;
    const int SCR_HEIGHT = 600;

    GLuint reflectionFrameBuffer;
    GLuint reflectionTexture;
    GLuint reflectionDepthBuffer;

    GLuint refractionFrameBuffer;
    GLuint refractionTexture;
    GLuint refractionDepthTexture;

    GLuint originalFrameBuffer;

public:
    WaterFrameBuffers() {
        glGetIntegerv(GL_FRAMEBUFFER_BINDING, (GLint*)&originalFrameBuffer);

        initialiseReflectionFrameBuffer();
        initialiseRefractionFrameBuffer();
    }

    ~WaterFrameBuffers() {
        cleanUp();
    }

    void bindReflectionFrameBuffer() {
        bindFrameBuffer(reflectionFrameBuffer, SCR_WIDTH, SCR_HEIGHT);
    }

    void bindRefractionFrameBuffer() {
        bindFrameBuffer(refractionFrameBuffer, SCR_WIDTH, SCR_HEIGHT);
    }

    void unbindCurrentFrameBuffer() {
        glBindFramebuffer(GL_FRAMEBUFFER, originalFrameBuffer); // todo generates error
        glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    }

    GLuint getReflectionTexture() {
        return reflectionTexture;
    }

    GLuint getRefractionTexture() {
        return refractionTexture;
    }

    GLuint getRefractionDepthTexture() {
        return refractionDepthTexture;
    }

private:
    void initialiseReflectionFrameBuffer() {
        reflectionFrameBuffer = createFrameBuffer();
        reflectionTexture = createTextureAttachment(SCR_WIDTH, SCR_HEIGHT);
        reflectionDepthBuffer = createDepthBufferAttachment(SCR_WIDTH, SCR_HEIGHT);
        unbindCurrentFrameBuffer();
    }

    void initialiseRefractionFrameBuffer() {
        refractionFrameBuffer = createFrameBuffer();
        refractionTexture = createTextureAttachment(SCR_WIDTH, SCR_HEIGHT);
        refractionDepthTexture = createDepthTextureAttachment(SCR_WIDTH, SCR_HEIGHT);
        unbindCurrentFrameBuffer();
    }

    void bindFrameBuffer(GLuint frameBuffer, int width, int height) {
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
        glViewport(0, 0, width, height);
    }

    GLuint createFrameBuffer() {
        GLuint frameBuffer;
        glGenFramebuffers(1, &frameBuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
        glDrawBuffer(GL_COLOR_ATTACHMENT0); // for off-screen rendering, specifies the color attachement where the renderering is written
        return frameBuffer;
    }

    GLuint createTextureAttachment(int width, int height) {
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
        return texture;
    }

    GLuint createDepthTextureAttachment(int width, int height) {
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture, 0);
        return texture;
    }

    GLuint createDepthBufferAttachment(int width, int height) {
        GLuint depthBuffer;
        glGenRenderbuffers(1, &depthBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
        return depthBuffer;
    }

    void cleanUp() {
        glDeleteFramebuffers(1, &reflectionFrameBuffer);
        glDeleteTextures(1, &reflectionTexture);
        glDeleteRenderbuffers(1, &reflectionDepthBuffer);
        glDeleteFramebuffers(1, &refractionFrameBuffer);
        glDeleteTextures(1, &refractionTexture);
        glDeleteTextures(1, &refractionDepthTexture);
    }
};

#endif // WATER_FB_H
