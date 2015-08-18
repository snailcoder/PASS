#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include "glm/gtc/matrix_transform.hpp"
#include "model.h"

Model::Model()
  : texture_width_(0), 
    texture_height_(0), 
    texture_size_(0), 
    transform_matrix_(1.0) {
}
Model::Model(const std::string &filename)
  : texture_width_(0), 
    texture_height_(0), 
    texture_size_(0), 
    transform_matrix_(1.0) {
  if (!LoadObj(filename)) {
    std::cerr << "can not load the obj model " << filename << std::endl;
  }
}
Model::Model(const Model &obj)
  : vertices_(obj.vertices_),
    uvs_(obj.uvs_),
    normals_(obj.normals_),
    texture_width_(obj.texture_width_), 
    texture_height_(obj.texture_height_), 
    texture_size_(obj.texture_size_), 
    transform_matrix_(obj.transform_matrix_) {
}
bool Model::LoadObj(const std::string &filename) {
  if (!vertices_.empty() || !uvs_.empty() || !normals_.empty()) {
    return false;
  }
  vertices_.clear();
  uvs_.clear();
  normals_.clear();
  std::ifstream objfile;
  objfile.open(filename.c_str());
  if (!objfile) {
    return false;
  }
  std::vector<glm::vec3> vertices, normals;
  std::vector<glm::vec2> uvs;
  std::vector<unsigned long> vindices, uvindices, nindices;
  std::string line;
  std::string header;
  while (std::getline(objfile, line)) {
    std::istringstream stream(line);
    stream >> header;
    // v: vertex coordinate
    // vt: texture coordinate of vertex
    // vn: normal of vertex
    // f: face
    if (header == "v") { 
      glm::vec3 vertex;
	  stream >> vertex.x >> vertex.y >> vertex.z;
      vertices.push_back(vertex);
    } else if (header == "vt") {
      glm::vec2 uv;
	  stream >> uv.x >> uv.y;
      uvs.push_back(uv);
    } else if (header == "vn") {
	  glm::vec3 normal;
      stream >> normal.x >> normal.y >> normal.z;
      normals.push_back(normal);
    } else if (header == "f") {
      std::string tuple_str[3];
      // The face line, starting with 'f', is comprised of three tuples,
      // each tuple consist of three indices of one a vertex,
      // e.g. 'v' index, 'vt' index and 'vn' index. If you have any questions,
      // I strongly recommend this excellent series of tutorial of OpenGL:
      // http://www.opengl-tutorial.org/
      // In fact, some functions of this project used to render refer to this
      // tutorial in part.
      stream >> tuple_str[0] >> tuple_str[1] >> tuple_str[2];
      std::string index_str;
      unsigned long tuple[3];
	  unsigned long vindex[3], uvindex[3], nindex[3];
      for (int i = 0; i < 3; ++i) {
        std::istringstream index_stream(tuple_str[i]);
        int cnt = 0;
        while (std::getline(index_stream, index_str, '/')) {
          tuple[cnt] = strtoul(index_str.c_str(), NULL, 10);
          ++cnt;
		}
        if (cnt != 3) {
          return false;
		}
        vindex[i] = tuple[0];
        uvindex[i] = tuple[1];
        nindex[i] = tuple[2];
	  }
      vindices.push_back(vindex[0]);
      vindices.push_back(vindex[1]);
      vindices.push_back(vindex[2]);
      uvindices.push_back(uvindex[0]);
      uvindices.push_back(uvindex[1]);
      uvindices.push_back(uvindex[2]);
      nindices.push_back(nindex[0]);
      nindices.push_back(nindex[1]);
      nindices.push_back(nindex[2]);
    }
  }
  // Convert indices to real coordinates. Be careful: indices start from 1
  // so we have to use (index - 1) to access correct coordinate.
  std::size_t size = vindices.size();
  for (std::size_t i = 0; i < size; ++i) {
    glm::vec3 vertex = vertices[vindices[i] - 1];
	glm::vec2 uv = uvs[uvindices[i] - 1];
	glm::vec3 normal = normals[nindices[i] - 1];
	vertices_.push_back(vertex);
	uvs_.push_back(uv);
	normals_.push_back(normal);
  }
  objfile.close();
  return true;
}
bool Model::LoadBMPTexture(const std::string &bmpfile) {
  if (!texture_data_.empty()) {
    return false;
  }
  unsigned char header[54];
  unsigned int data_pos;
  std::ifstream bmp_stream(bmpfile.c_str());
  if (!bmp_stream.is_open()) {
    std::cerr << "Can not open the BMP file: " << bmpfile << std::endl;
    return false;
  }
  bmp_stream.read((char*)header, 54);
  if (!bmp_stream) {
    std::cerr << "Error: only " << bmp_stream.gcount()
		<< "characters could be read from the file" << bmpfile << std::endl;
    return false;
  }
  if (header[0] != 'B' || header[1] != 'M') {
    std::cerr << "Error: not a correct BMP file." << std::endl;
    return false;
  }
  if (*(int*)&(header[28]) != 24 || *(int*)&(header[30]) != 0) {
    std::cerr << "Error: not a correct BMP file." << std::endl;
    return false;
  }
  data_pos = *(int*)&(header[10]);
  texture_size_ = *(int*)&(header[34]);
  texture_width_ = *(int*)&(header[18]);
  texture_height_ = *(int*)&(header[22]);
  if (texture_size_ == 0) {
    texture_size_ = texture_width_ * texture_height_ * 3;
  }
  if (data_pos == 0) {
    data_pos = 54;
  }
  texture_data_.resize(texture_size_);
  bmp_stream.read((char*)(&texture_data_[0]), texture_size_);
  bmp_stream.close();
  return true;
}
Vec3Vector Model::vertices() const {
  return vertices_;
}
Vec2Vector Model::uvs() const {
  return uvs_;
}
Vec3Vector Model::normals() const {
  return normals_;
}
unsigned Model::texture_width() const {
  return texture_width_;
}
unsigned Model::texture_height() const {
  return texture_height_;
}
unsigned Model::texture_size() const {
  return texture_size_;
}
std::vector<unsigned char> Model::texture_data() const {
  return texture_data_;
}
Mat4 Model::transform_matrix() const {
  return transform_matrix_;
}
void Model::TransformIdentity() {
  transform_matrix_ = Mat4(1.0);
}
void Model::translate(const Vec3 &translation) {
  transform_matrix_ = glm::translate(transform_matrix_, translation);
}
void Model::translate(float x, float y, float z) {
  Vec3 translation(x, y, z);
  transform_matrix_ = glm::translate(transform_matrix_, translation);
}
void Model::rotate(float angle, const Vec3 &axis) {
  transform_matrix_ = glm::rotate(transform_matrix_, angle, axis);
}
void Model::rotate(float angle, float x, float y, float z) {
  Vec3 axis(x, y, z);
  transform_matrix_ = glm::rotate(transform_matrix_, angle, axis);
}
void Model::set_translate(const Vec3 &translation) {
  transform_matrix_ = glm::translate(glm::mat4(1.0f), translation);
}
void Model::set_translate(float x, float y, float z) {
  Vec3 translation(x, y, z);
  transform_matrix_ = glm::translate(glm::mat4(1.0f), translation);
}
void Model::set_rotate(float angle, const Vec3 &axis) {
  transform_matrix_ = glm::rotate(glm::mat4(1.0f), angle, axis);
}
void Model::set_rotate(float angle, float x, float y, float z) {
  Vec3 axis(x, y, z);
  transform_matrix_ = glm::rotate(glm::mat4(1.0f), angle, axis);
}