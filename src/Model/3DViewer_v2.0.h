#ifndef S21_3DVIEWER_V2_H
#define S21_3DVIEWER_V2_H

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <QString>
#include <QStringList>
#include <QVector>
#include <QtMath>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>

#ifdef __linux__
#include <GL/gl.h>
#elif __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#endif
// #include <GL/gl.h>
// #include <OpenGL/gl.h>
// #include <OpenGL/glext.h>

namespace s21 {

class back {
 private:
  QVector<GLuint> polygons_;
  QVector<GLfloat> vertexes_;
  void normalisation();
  void GetFNumFromStr_(std::string str);

 public:
  back(){};
  ~back() = default;
  void rotation_by_ox(GLfloat angle);
  void rotation_by_oy(GLfloat angle);
  void rotation_by_oz(GLfloat angle);
  QVector<GLuint> const &get_polygons();
  QVector<GLfloat> const &get_vertixes();
  void parser(std::string filename);
};

}  // namespace s21

#endif
