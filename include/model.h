#ifndef MODEL_H_
#define MODEL_H_

#include <string>
#include "common.h"

// Model is the basic component of object in the Scene. It contains some
// graphics parameters such as vertices, textures, transformation matrix...
// Actually, a model is a renderable entity. Sample usage:
// Model model(objfile);  // Load vertices, uvs and normals from obj file
// model.LoadBMPTexture(bmpfile); // Load textures from bmp file

class Model {
 public:
  Model();
  Model(const std::string &filename);
  Model(const Model &model);
  // Load model from obj file
  bool LoadObj(const std::string &filename);
  // Load texture from bmp file 
  bool LoadBMPTexture(const std::string &bmpfile); 
  Vec3Vector vertices() const;
  Vec2Vector uvs() const;
  Vec3Vector normals() const;
  unsigned texture_width() const;
  unsigned texture_height() const;
  unsigned texture_size() const;
  std::vector<unsigned char> texture_data() const;
  Mat4 transform_matrix() const;
  // Set transform_matrix_ to be identity matrix
  void TransformIdentity();
  // Translate the model by multiplying transform_matrix_ by translation matrix
  void translate(const Vec3 &translation);
  void translate(float x, float y, float z);
  // Rotate the model by multiplying transform_matrix_ by rotation matrix
  void rotate(float angle, const Vec3 &axis);
  void rotate(float angle, float x, float y, float z);
  void set_translate(const Vec3 &translation);
  void set_translate(float x, float y, float z);
  void set_rotate(float angle, const Vec3 &axis);
  void set_rotate(float angle, float x, float y, float z);
 protected:
  Vec3Vector vertices_;  // Vertex coordinates
  Vec2Vector uvs_;  // Texture coordinates of vertex
  Vec3Vector normals_;  // Normal of vertex
  unsigned texture_width_;
  unsigned texture_height_;
  unsigned texture_size_;
  std::vector<unsigned char> texture_data_;
  Mat4 transform_matrix_;  // Transformation matrix
};

#endif