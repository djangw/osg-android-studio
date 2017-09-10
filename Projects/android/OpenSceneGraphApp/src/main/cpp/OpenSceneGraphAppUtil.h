
/*
This file is part of OpenSceneGraph cross-platform guide:
  https://github.com/OGStudio/openscenegraph-cross-platform-guide

Copyright (C) 2017 Opensource Game Studio

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#ifndef OPENSCENEGRAPH_CROSS_PLATFORM_GUIDE_FUNCTIONS_H
#define OPENSCENEGRAPH_CROSS_PLATFORM_GUIDE_FUNCTIONS_H

#include <osg/Notify>

// Convert NotifySeverity enum value to string.
std::string logLevelToString(osg::NotifySeverity severity)
{
    switch (severity)
    {
        case osg::DEBUG_FP:
            // Verbose.
            return "V";
        case osg::DEBUG_INFO:
            // Debug.
            return "D";
        case osg::NOTICE:
        case osg::INFO:
            // Info.
            return "I";
        case osg::WARN:
            // Warning.
            return "W";
        case osg::FATAL:
        case osg::ALWAYS:
            // Error.
            return "E";
    }
}

#include <cstdarg>

// Construct a string using printf-like syntax.
std::string printfString(const char *fmt, ...)
{
    const int PRINTF_STRING_MAX_STRLEN = 1024;
    va_list args;
    char msg[PRINTF_STRING_MAX_STRLEN];
    va_start(args, fmt);
    vsnprintf(msg, PRINTF_STRING_MAX_STRLEN, fmt, args);
    va_end(args);
    return msg;
}

// BEGIN FEATURE LOGGING_ANDROID
#include <android/log.h>
// END   FEATURE LOGGING_ANDROID

// Platform specific logging.
void platformLog(const char *message)
{
// BEGIN FEATURE LOGGING_ANDROID
    __android_log_write(ANDROID_LOG_ERROR, "OSG", message);
// END   FEATURE LOGGING_ANDROID
}

#include <osg/Camera>

// Configure camera with common defaults.
void setupCamera(
    osg::Camera *cam,
    osg::GraphicsContext *gc,
    double fovy,
    int width,
    int height)
{
    // Provide GC.
    cam->setGraphicsContext(gc);
    // Viewport must have the same size.
    cam->setViewport(new osg::Viewport(0, 0, width, height));
    // Clear depth and color buffers each frame.
    cam->setClearMask(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    // Aspect ratio.
    float aspect = static_cast<float>(width) / static_cast<float>(height);
    // Configure projection.
    cam->setProjectionMatrixAsPerspective(30, aspect, 1, 1000);
}



#include <osg/Program>

// Fragment shader to display everything in red colour.
static const char shaderFragment[] =
    "void main() {                             \n"
    "  gl_FragColor = vec4(0.5, 0.3, 0.3, 1.0);\n"
    "}                                         \n";
// Geometry shader to pass geometry vertices to fragment shader.
static const char shaderVertex[] =
    "void main() {                                              \n"
    "  gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;  \n"
    "}                                                          \n";

osg::Program *createShaderProgram(
    const std::string &vertexShader,
    const std::string &fragmentShader)
{
    // Load shaders.
    osg::Shader *vs = new osg::Shader(osg::Shader::VERTEX, vertexShader);
    osg::Shader *fs = new osg::Shader(osg::Shader::FRAGMENT, fragmentShader);
    // Compile shaders and compose shader program.
    osg::Program *prog = new osg::Program;
    prog->addShader(vs);
    prog->addShader(fs);
    return prog;
}

#endif // OPENSCENEGRAPH_CROSS_PLATFORM_GUIDE_FUNCTIONS_H

