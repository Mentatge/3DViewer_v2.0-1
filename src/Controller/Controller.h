#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../Model/3DViewer_v2.0.h"

namespace s21 {

class Controller {
 public:
  Controller(){};
  ~Controller(){};
  void controller_rotation_by_ox(GLfloat angle);
  void controller_rotation_by_oy(GLfloat angle);
  void controller_rotation_by_oz(GLfloat angle);
  void controller_parser(std::string filename);
  int get_poligons();
  int get_vertixes();
  QVector<GLuint> const &controller_get_polygons();
  QVector<GLfloat> const &controller_get_vertixes();

 private:
  s21::back model_;
};
}  // namespace s21

#endif
