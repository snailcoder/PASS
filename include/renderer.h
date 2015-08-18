#ifndef RENDERER_H_
#define RENDERER_H_

#include <string>
#include <vector>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "common.h"
#include "shader.h"
#include "scene.h"

class Renderer {
 public:
  Renderer();
  ~Renderer();
  typedef GLuint TextureID;
  typedef GLuint MatrixID;
  typedef GLuint ProgramID;
  ProgramID LoadShader(const std::string &vertex_shader, 
                       const std::string &fragment_shader);
  MatrixID LocateMVPMatrix(const std::string &mvp);
  TextureID LocateTextureSampler(const std::string &sampler);
  // Construct a RenderModel object and add it to the RenderModel vector
  void AddRenderModel(Model *model);
  void AddRenderObject(Object *object);
  // Update all RenderModel objects' mvp matrix
  void UpdateMVP();
  void Render();
  Mat4 project_matrix() const;
  Mat4 view_matrix() const;
  void set_project_matrix(float fovy, float aspect, float znear, float zfar);
  void set_view_matrix(const Vec3 &eye, const Vec3 &center, const Vec3 &up);
 private:
  // Enclose a model with some buffer information into RenderModel
  // so that it can be rendered.
  struct RenderModel {
    RenderModel();
    Model *model_;
    GLuint vertex_buffer_;
    GLuint uv_buffer_;
    GLuint texture_;
    Mat4 mvp_matrix_;  // project * view * transform
  };
  std::vector<RenderModel> render_models_;
  Mat4 project_matrix_;
  Mat4 view_matrix_;
  GLuint vao_id_;
  GLuint program_id_;
  GLuint matrix_id_;
  GLuint texture_id_;
};

#endif