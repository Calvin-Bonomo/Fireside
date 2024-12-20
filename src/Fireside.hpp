/**
 * FIRESIDE.HPP
 * Written by Calvin Bonomo
 * Copyright (c) 2024
 */

#ifndef RENDERER
#define RENDERER

#include <stdio.h>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "VertexArrayObject.hpp"
#include "DrawList.hpp"

static inline void CheckGL() 
{
    int err;
    while ((err = glGetError()) != GL_NO_ERROR)
    {
      fprintf(stderr, "GL Error: %x @ %u in %s\n", err, __LINE__, __FILE__);
    }
}

namespace Fireside 
{
  class Renderer 
  {
  private: // Member variables
    GLFWwindow* m_pWindow;
    unsigned int m_Width, m_Height;

  public:
    Renderer(std::string title, int width, int height);
    ~Renderer();

    void Stop();
    bool ShouldStop();

    void SetWindowTitle(std::string title);
    void SetWindowSize(int width, int height);

    int RegisterKeyListener(Util::key_listener_t listener);
    void RemoveKeyListener(Util::key_listener_t listener);

    void DrawObject(SceneObject object);
    void RenderScene();

    std::weak_ptr<SceneObject> GetCamera();
    void SetFOV(float degrees);
    void SetProjectionMode(ProjectionMode mode);
    void SetClippingPlane(float near, float far);
    Rendering::Program* GetDefaultShaderProgram();

    void SetAmbientIntensity(float intensity);
    void SetLight(unsigned int index, glm::vec4 pos, Color color, float attenuation);
    void SetSunDir(glm::vec3 dir, glm::vec3 up = glm::vec3(0, 1, 0));
    glm::vec3 GetSunDir();
    void SetSunColor(Color color);

    glm::mat4 GenerateProjectionMatrix(float ar, CameraSettings settings);

    void RenderDrawCalls();
    void RenderDrawCallsUnshaded(Rendering::Program* program);

  private:
    void SetupPipeline();

    int InitOpenGL();

    // Callbacks
    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void ErrorCallback(int error, const char* description);
    static void FramebufferCallback(GLFWwindow* window, int width, int height);
  };
}

#endif