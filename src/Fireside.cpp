/**
 * FIRESIDE.CPP
 * Written by Calvin Bonomo
 * Copyright (c) 2024
 */

#include "Renderer.hpp"

void Fireside::Renderer::RenderScene() 
{
  glCullFace(GL_BACK);
  CheckError();
  glViewport(0, 0, 2048, 2048);
  CheckError();
  glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffers[SHADOW_INDEX]);
  CheckError();
  glClear(GL_DEPTH_BUFFER_BIT);
  CheckError();
  // glCullFace(GL_BACK);
  // CheckError();
  // glViewport(0, 0, m_Width, m_Height);
  // CheckError();
  // glBindFramebuffer(GL_FRAMEBUFFER, 0);
  // CheckError();
  // glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  // CheckError();
  m_SceneData.eye = glm::vec4(m_pCameraObject->GetPosition(), 1);
  m_SceneData.view = glm::inverse(m_pCameraObject->GetModelMatrix());
  m_SceneUBO.EditData(&m_SceneData);
  m_LightUBO.EditData(&m_LightData);
  RenderDrawCallsUnshaded(m_pDefaultShadowShader);

  m_DrawList.Reset();
  glCullFace(GL_FRONT);
  CheckError();
  glViewport(0, 0, m_Width, m_Height);
  CheckError();
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  CheckError();
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  CheckError();
  RenderDrawCalls();
  
  // glBindFramebuffer(GL_FRAMEBUFFER, 0);
  // CheckError();
  // // Bind quad and pp shader
  // glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  // CheckError();

  glFlush();
  CheckError();
  glfwSwapBuffers(m_pWindow);
  glfwPollEvents();  
  m_DrawList.Clear();
}

/** Stop
 * 
 * Description:
 * -----
 * Sets the flag telling the window to close.
 * 
 * Returns:
 * -----
 * `void`
 * 
 * Parameters:
 * -----
 * `void`
 * 
 */
void Fireside::Renderer::Stop() 
{
  glfwSetWindowShouldClose(m_pWindow, GLFW_TRUE);
}

/** ShouldStop
 * 
 * Description:
 * -----
 * Returns whether the close flag is set for the window.
 * 
 * Returns:
 * -----
 * `bool`
 * 
 * Parameters:
 * -----
 * `void`
 * 
 */
bool Fireside::Renderer::ShouldStop() 
{
  return glfwWindowShouldClose(m_pWindow);
}

glm::mat4 Fireside::Renderer::GenerateProjectionMatrix(float ar, CameraSettings settings) 
{
  glm::mat4 proj;
  if (settings.mode == ProjectionMode::PERSPECTIVE)
  {
    proj = glm::perspective(
      settings.fovRadians, 
      ar, 
      settings.zNear, 
      settings.zFar);
  }
  else 
  {
    proj = glm::ortho(settings.left, settings.right, settings.bottom, settings.top, settings.zNear, settings.zFar);
  }
  return proj;
}

void Fireside::Renderer::SetWindowTitle(std::string title) 
{
  if (!m_pWindow)
    return;
  
  glfwSetWindowTitle(m_pWindow, title.c_str());
}

void Fireside::Renderer::SetWindowSize(int width, int height) 
{
  if (!m_pWindow)
    return;

  m_Width = width;
  m_Height = height;

  glfwSetWindowSize(m_pWindow, width, height);
  glViewport(0, 0, width, height);
  CheckError();
  m_SceneData.projection = GenerateProjectionMatrix(height == 0? 1 : (double)width / height, m_CameraSettings);
  m_SceneUBO.EditData(&m_SceneData.projection, 0, sizeof(glm::mat4));
}

int Fireside::Renderer::RegisterKeyListener(Util::key_listener_t listener) 
{
  if (m_KeyListeners.size() == MAX_KEY_LISTENERS)
    return -1;
  
  m_KeyListeners.emplace_back(listener);
  return 0;
}

void Fireside::Renderer::RemoveKeyListener(Util::key_listener_t listener) 
{
  if (m_KeyListeners.size() == 0) 
    return;
  m_KeyListeners.erase(std::find(m_KeyListeners.begin(), m_KeyListeners.end(), listener));
}

int Fireside::Renderer::InitOpenGL() 
{
  if (glfwInit() == GLFW_FALSE) 
  {
    Util::LogError("failed to initialize glfw");
    return 0;
  }
  glfwSetErrorCallback(ErrorCallback);
  return 1;
}

Fireside::Renderer::Renderer(std::string windowTitle, int windowWidth, int windowHeight):
  m_DrawList(MAX_DRAW_CALLS)
{
  if (!InitOpenGL())
  {
    Util::LogError("failed to initialize OpenGL!");
    return;
  }

  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  m_pWindow = glfwCreateWindow(
    windowWidth, 
    windowHeight, 
    windowTitle.c_str(), 
    NULL, 
    NULL);
  
  m_Width = windowWidth;
  m_Height = windowHeight;

  if (m_pWindow == nullptr)
  {
    Util::LogError("unable to create window");
    return;
  }
  
  glfwMakeContextCurrent(m_pWindow);

  #ifdef USEGLEW
  GLenum err = glewInit();

  if (err != GLEW_OK)
  {
    Util::LogError(std::string((char*)glewGetErrorString(err)));
    return;
  }
  #endif

  glfwSetWindowUserPointer(m_pWindow, this);

  // Setup callbacks
  glfwSetKeyCallback(m_pWindow, (GLFWkeyfun)KeyCallback);
  glfwSetFramebufferSizeCallback(m_pWindow, (GLFWframebuffersizefun)FramebufferCallback);

  SetupPipeline();

  glEnable(GL_CULL_FACE);
  CheckError();
  glEnable(GL_DEPTH_TEST);
  CheckError();

  m_pDefaultShadowShader = new Rendering::Program();
  Rendering::Shader shadowVert = Util::IO::LoadShader("built-in/shaders/shadow.vert",
    Util::IO::ShaderType::Vertex);
  Rendering::Shader shadowFrag = Util::IO::LoadShader("built-in/shaders/shadow.frag",
    Util::IO::ShaderType::Fragment);
  m_pDefaultShadowShader->AttachShader(shadowVert);
  m_pDefaultShadowShader->AttachShader(shadowFrag);
  m_pDefaultShadowShader->Link();

  m_pDefaultLitShader = new Rendering::Program();
  Rendering::Shader defaultVert = Util::IO::LoadShader("built-in/shaders/default_lit.vert", 
    Util::IO::ShaderType::Vertex);
  Rendering::Shader defaultFrag = Util::IO::LoadShader("built-in/shaders/default_lit.frag",
    Util::IO::ShaderType::Fragment);
  m_pDefaultLitShader->AttachShader(defaultVert);
  m_pDefaultLitShader->AttachShader(defaultFrag);
  m_pDefaultLitShader->Link();

  m_pCameraObject = std::make_shared<SceneObject>();

  m_CameraSettings.fovRadians = glm::radians(70.0);
  m_CameraSettings.mode = ProjectionMode::PERSPECTIVE;
  m_CameraSettings.zNear = 0.0001;
  m_CameraSettings.zFar = 10000;

  m_LightData.lightDir = glm::vec4(0, 0, -1, 0);
  m_LightData.lightColor = Fireside::Color(glm::vec3(0.75), 1);

  m_SceneData.eye = glm::vec4(m_pCameraObject->GetPosition(), 1.0);
  m_SceneData.projection = GenerateProjectionMatrix(m_Height == 0? 1 : (double)m_Width / m_Height, m_CameraSettings);
  m_SceneData.view = glm::inverse(m_pCameraObject->GetModelMatrix());
  m_SceneData.lightMats[0] = glm::inverse(glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(m_LightData.lightDir), glm::vec3(0, 1, 0)));
  m_SceneData.lightMats[1] = GenerateProjectionMatrix(1, {ProjectionMode::ORTHOGRAPHIC, 0, -5, 5, -5, 5, -5, 5});
  m_LightData.ambientIntensity = 0.2;
  m_SceneUBO = Rendering::UniformBufferObject(&m_SceneData, sizeof(Rendering::SceneData), 0);
  m_LightUBO = Rendering::UniformBufferObject(&m_LightData, sizeof(Rendering::LightData), 1);
  m_pDefaultLitShader->SetUniformBlock("sceneBlock", m_SceneUBO);
  m_pDefaultLitShader->SetUniformBlock("lightBlock", m_LightUBO);
  m_pDefaultShadowShader->SetUniformBlock("sceneBlock", m_SceneUBO);
}

Fireside::Renderer::~Renderer() 
{
  glDeleteFramebuffers(2, m_Framebuffers);
  CheckError();
  glDeleteTextures(2, m_DrawTextures);
  CheckError();
  glfwDestroyWindow(m_pWindow);
}

void Fireside::Renderer::ErrorCallback(int error, const char* description) 
{
  fprintf(stderr, "Renderer error: %s!\n", description);
}

void Fireside::Renderer::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) 
{
  // https://stackoverflow.com/questions/7676971/pointing-to-a-function-that-is-a-class-member-glfw-setkeycallback
  Renderer* pRenderer = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
  auto listeners = pRenderer->m_KeyListeners;
  Util::KeyEvent event(key, scancode, action);
  
  // Use a hashmap and fix this slow thing
  for (auto& listener : listeners) 
    listener(pRenderer, event);
}

void Fireside::Renderer::RenderDrawCalls() 
{
  for (auto& drawCall : m_DrawList)
  {
    drawCall.pProgram->UseProgram();
    drawCall.uFunc(drawCall.pProgram, drawCall.arg);
    drawCall.pProgram->SetUniform("model", drawCall.modelMatrix);
    glActiveTexture(GL_TEXTURE0);
    CheckError();
    glBindTexture(GL_TEXTURE_2D, m_DrawTextures[SHADOW_INDEX]);
    CheckError();
    drawCall.pProgram->SetUniform("shadowMap", 0);

    glBindVertexArray(drawCall.vaoIndex);
    CheckError();
    glDrawArrays(GL_TRIANGLES, 0 , drawCall.count);
    CheckError();
  }
}

void Fireside::Renderer::RenderDrawCallsUnshaded(Rendering::Program* program) 
{
  for (auto& drawCall : m_DrawList)
  {
    program->UseProgram();
    program->SetUniform("model", drawCall.modelMatrix);

    glBindVertexArray(drawCall.vaoIndex);
    CheckError();
    glDrawArrays(GL_TRIANGLES, 0 , drawCall.count);
    CheckError();
  }
}

void Fireside::Renderer::FramebufferCallback(GLFWwindow *window, int width, int height) 
{
  Renderer* renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(window));

  renderer->m_Width = width;
  renderer->m_Height = height;

  renderer->m_SceneData.projection = renderer->GenerateProjectionMatrix(height == 0? 1 : (float)width / height, \
    renderer->m_CameraSettings);
  renderer->m_SceneUBO.EditData(&renderer->m_SceneData.projection, 0, sizeof(glm::mat4));
}

void Fireside::Renderer::SetupPipeline() 
{
  // Create rendering pass objects
  glGenFramebuffers(2, m_Framebuffers);
  CheckError();
  glGenTextures(2, m_DrawTextures);
  CheckError();

  // Setup shadow mapping
  glActiveTexture(GL_TEXTURE0);
  CheckError();
  glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffers[SHADOW_INDEX]);
  CheckError();
  glBindTexture(GL_TEXTURE_2D, m_DrawTextures[SHADOW_INDEX]);
  CheckError();
  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 2048, 2048, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
  CheckError();
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
  CheckError();
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  CheckError();
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  CheckError();
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); 
  CheckError();
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);  
  CheckError();
  glBindTexture(GL_TEXTURE_2D, 0);
  CheckError();
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_DrawTextures[SHADOW_INDEX], 0);
  CheckError();
  glDrawBuffer(GL_NONE);
  CheckError();
  glReadBuffer(GL_NONE);
  CheckError();

  // Setup postprocessing
  // glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_Framebuffers[POSTPASS_INDEX]);
  // CheckError();
  // glBindTexture(GL_TEXTURE_2D, m_DrawTextures[POSTPASS_INDEX]);
  // CheckError();
  // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_FLOAT, NULL);
  // CheckError();
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  // CheckError();
  // glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_DrawTextures[POSTPASS_INDEX], 0);
  // CheckError();
}

void Fireside::Renderer::DrawObject(SceneObject object) 
{
  Rendering::DrawCall dc = object.MakeDrawCall();

  if (!m_DrawList.Append(dc))
    Util::LogError("Failed to add draw call to draw list\n");
}

std::weak_ptr<Fireside::SceneObject> Fireside::Renderer::GetCamera() 
{
  return m_pCameraObject;
}

void Fireside::Renderer::SetFOV(float degrees) 
{
  m_CameraSettings.fovRadians = glm::radians(degrees);
}

void Fireside::Renderer::SetProjectionMode(Fireside::Renderer::ProjectionMode mode) 
{
  m_CameraSettings.mode = mode;
}

void Fireside::Renderer::SetClippingPlane(float near, float far) 
{
  m_CameraSettings.zNear = near;
  m_CameraSettings.zFar = far;
}

Fireside::Rendering::Program* Fireside::Renderer::GetDefaultShaderProgram() 
{
  return m_pDefaultLitShader;
}

void Fireside::Renderer::SetAmbientIntensity(float intensity) 
{
  m_LightData.ambientIntensity = intensity;
  m_LightUBO.EditData(&m_LightData.ambientIntensity, offsetof(Rendering::LightData, ambientIntensity), sizeof(float));
}

void Fireside::Renderer::SetLight(unsigned int index, glm::vec4 pos, Color color, float attenuation) 
{
  if (index >= Rendering::MAX_LIGHTS)
    return;

  m_LightData.lights[index].pos = m_SceneData.view * pos;
  m_LightData.lights[index].color = color;
  m_LightData.lights[index].attenuation = attenuation;

  m_LightUBO.EditData(m_LightData.lights + index, index * sizeof(Rendering::Light), sizeof(Rendering::Light));
}

void Fireside::Renderer::SetSunDir(glm::vec3 dir, glm::vec3 up) 
{
  m_LightData.lightDir = m_SceneData.view * glm::vec4(glm::normalize(dir), 0);
  m_SceneData.lightMats[0] = glm::lookAt(glm::vec3(0), glm::normalize(dir), glm::normalize(up));
  m_LightUBO.EditData(&m_LightData.lightDir, offsetof(Rendering::LightData, lightDir), sizeof(glm::vec4));
  m_SceneUBO.EditData(m_SceneData.lightMats, offsetof(Rendering::SceneData, lightMats), sizeof(glm::mat4));
}

glm::vec3 Fireside::Renderer::GetSunDir() 
{
  return glm::vec3(m_LightData.lightDir);
}

void Fireside::Renderer::SetSunColor(Color color) 
{
  m_LightData.lightColor = color;
  m_LightUBO.EditData(&m_LightData.lightColor, offsetof(Rendering::LightData, lightColor), sizeof(Color));
}
