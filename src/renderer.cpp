#include <iostream>
#include <fstream>
#include "glm/gtx/transform.hpp"
#include "renderer.h"

Renderer::RenderModel::RenderModel() 
  : model_(NULL), 
    vertex_buffer_(0), 
    uv_buffer_(0), 
    texture_(0), 
	mvp_matrix_(1.0) {
}
Renderer::Renderer()
  : vao_id_(0), 
    program_id_(0), 
    matrix_id_(0), 
    texture_id_(0) {
  set_view_matrix(Vec3(4, 3, 4), Vec3(0, 0, 0), Vec3(0, 1, 0));
  set_project_matrix(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

  glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glGenVertexArrays(1, &vao_id_);
  glBindVertexArray(vao_id_);
}
Renderer::~Renderer() {
  for (std::vector<RenderModel>::iterator iter = render_models_.begin(); 
	  iter != render_models_.end(); ++iter) {
    glDeleteBuffers(1, &(iter->vertex_buffer_));
    glDeleteBuffers(1, &(iter->uv_buffer_));
  }
  glDeleteProgram(program_id_);
  glDeleteTextures(1, &texture_id_);
  glDeleteVertexArrays(1, &vao_id_);
}
Renderer::ProgramID Renderer::LoadShader(const std::string &vertex_shader, 
                                         const std::string &fragment_shader) {
  if (program_id_ != 0) {
    return 0;
  }
  GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

  std::ifstream vertex_shader_stream(vertex_shader.c_str());
  if (!vertex_shader_stream.is_open()) {
    std::cerr << "Can not open the shader file: " 
        << vertex_shader << std::endl;
    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);
    return 0;
  }
  std::string vertex_shader_code;
  std::string vline;
  while (getline(vertex_shader_stream, vline)) {
    vertex_shader_code += vline + "\n";
  }
  vertex_shader_stream.close();


  std::ifstream fragment_shader_stream(fragment_shader.c_str());
  if (!fragment_shader_stream.is_open()) {
    std::cerr << "Can not open the shader file: " 
        << fragment_shader << std::endl;
    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);
    return 0;
  }
  std::string fragment_shader_code;
  std::string fline;
  while (getline(fragment_shader_stream, fline)) {
    fragment_shader_code += fline + "\n";
  }
  fragment_shader_stream.close();

  GLint log_length;
  GLint result = GL_FALSE;

  const char *vertex_shader_source = vertex_shader_code.c_str();
  glShaderSource(vertex_shader_id, 1, &vertex_shader_source, NULL);
  glCompileShader(vertex_shader_id);
  glGetShaderiv(vertex_shader_id, GL_INFO_LOG_LENGTH, &log_length);
  if (log_length > 0) {
    GLchar *infolog = new GLchar[log_length + 1];
    glGetShaderInfoLog(vertex_shader_id, log_length, NULL, infolog);
    //std::cout << infolog << std::endl;
    delete[] infolog;
  }
  glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &result);
  if (!result) {
    std::cerr << "Failed to compile vertex shader." << std::endl;
    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);
    return 0;
  }

  const char *fragment_shader_source = fragment_shader_code.c_str();
  glShaderSource(fragment_shader_id, 1, &fragment_shader_source, NULL);
  glCompileShader(fragment_shader_id);
  glGetShaderiv(fragment_shader_id, GL_INFO_LOG_LENGTH, &log_length);
  if (log_length > 0) {
    GLchar *infolog = new GLchar[log_length + 1];
    glGetShaderInfoLog(fragment_shader_id, log_length, NULL, infolog);
    //std::cout << infolog << std::endl;
    delete[] infolog;
  }
  glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &result);
  if (!result) {
    std::cerr << "Failed to compile fragment shader." << std::endl;
    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);
    return 0;
  }

  program_id_ = glCreateProgram();

  glAttachShader(program_id_, vertex_shader_id);
  glAttachShader(program_id_, fragment_shader_id);
  glLinkProgram(program_id_);
  glGetProgramiv(program_id_, GL_INFO_LOG_LENGTH, &log_length);
  if (log_length > 0) {
    GLchar *infolog = new GLchar[log_length + 1];
    glGetProgramInfoLog(program_id_, log_length, NULL, infolog);
    std::cout << infolog << std::endl;
    delete[] infolog;
  }
  glGetProgramiv(program_id_, GL_LINK_STATUS, &result);
  if (!result) {
    std::cerr << "Failed to link shader to program." << std::endl;
    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);
    return 0;
  }

  glDeleteShader(vertex_shader_id);
  glDeleteShader(fragment_shader_id);

  return program_id_;
}
Renderer::TextureID Renderer::LocateTextureSampler(
    const std::string &sampler) {
  if (program_id_ == 0) {
    return 0;
  }
  return texture_id_ = glGetUniformLocation(program_id_, sampler.c_str());
}
Renderer::MatrixID Renderer::LocateMVPMatrix(const std::string &mvp) {
  if (program_id_ == 0) {
    return 0;
  }
  return matrix_id_ = glGetUniformLocation(program_id_, mvp.c_str());
}
void Renderer::AddRenderModel(Model *model) {
  RenderModel rmod;
  rmod.model_ = model;

  Vec3Vector vertices = model->vertices();
  glGenBuffers(1, &rmod.vertex_buffer_);
  glBindBuffer(GL_ARRAY_BUFFER, rmod.vertex_buffer_);
  glBufferData(GL_ARRAY_BUFFER, 
               vertices.size() * sizeof(Vec3), 
               &vertices[0], 
               GL_STATIC_DRAW);

  Vec2Vector uvs = model->uvs();
  glGenBuffers(1, &rmod.uv_buffer_);
  glBindBuffer(GL_ARRAY_BUFFER, rmod.uv_buffer_);
  glBufferData(GL_ARRAY_BUFFER,
               uvs.size() * sizeof(Vec2), 
               &uvs[0], 
               GL_STATIC_DRAW);

  if (model->texture_size() != 0) {
    std::vector<unsigned char> texture_data = model->texture_data();
    unsigned width = model->texture_width();
    unsigned height = model->texture_height();
    glGenTextures(1, &rmod.texture_);
    glBindTexture(GL_TEXTURE_2D, rmod.texture_);
    glTexImage2D(GL_TEXTURE_2D, 
                 0, 
                 GL_RGB, 
                 width, 
                 height, 
                 0, 
                 GL_BGR, 
                 GL_UNSIGNED_BYTE, 
                 &texture_data[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  Mat4 transform_matrix = model->transform_matrix();
  rmod.mvp_matrix_ = project_matrix_ * view_matrix_ * transform_matrix;
  render_models_.push_back(rmod);
}
void Renderer::AddRenderObject(Object *object) {
  std::vector<Model*> models = object->components();
  for (std::vector<Model*>::iterator iter = models.begin();
	  iter != models.end(); ++iter) {
    AddRenderModel(*iter);
  }
}
void Renderer::UpdateMVP() {
  for (std::vector<RenderModel>::iterator iter = render_models_.begin();
	  iter != render_models_.end(); ++iter) {
    Mat4 transform_matrix = iter->model_->transform_matrix();
    iter->mvp_matrix_ = project_matrix_ * view_matrix_ * transform_matrix;
  }
}
void Renderer::Render() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glUseProgram(program_id_);

  for (std::vector<RenderModel>::iterator iter = render_models_.begin();
	  iter != render_models_.end(); ++iter) {
    glUniformMatrix4fv(matrix_id_, 1, GL_FALSE, &(iter->mvp_matrix_[0][0]));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, iter->texture_);
    glUniform1i(texture_id_, 0);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, iter->vertex_buffer_);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, iter->uv_buffer_);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glDrawArrays(GL_TRIANGLES, 0, iter->model_->vertices().size());
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
  }
}
Mat4 Renderer::project_matrix() const {
  return project_matrix_;
}
Mat4 Renderer::view_matrix() const {
  return view_matrix_;
}
void Renderer::set_project_matrix(float fovy, 
                                  float aspect, 
                                  float znear, 
                                  float zfar) {
  project_matrix_ = glm::perspective(fovy, aspect, znear, zfar);
}
void Renderer::set_view_matrix(const Vec3 &eye, 
                               const Vec3 &center, 
                               const Vec3 &up) {
  view_matrix_ = glm::lookAt(eye, center, up);
}