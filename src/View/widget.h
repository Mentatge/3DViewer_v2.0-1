#ifndef WIDGET_H
#define WIDGET_H

#include <QColor>
#include <QDebug>
#include <QMatrix4x4>
#include <QMessageBox>
#include <QMouseEvent>
#include <QMoveEvent>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLWidget>
#include <QSettings>
#include <QVector>
#include <QWheelEvent>
#include <iostream>

#include "../Controller/Controller.h"

struct VertexData {  // Структура вершин
                     //    VertexData()
                     //    {
                     //    }

  VertexData(QVector3D p /*, QVector2D t*/) : position(p) /*, texCoord(t)*/ {}

  QVector3D position;  // позиция точки
  //    QVector2D texCoord; // текстурные координаты давай ее нахуй хуйнейм
  //    отсюда и оставим только ебучие координаты нахуй оно нам верно?
};

class Widget : public QOpenGLWidget {
  // Q_OBJECT

 public:
  s21::Controller controller_back;
  void draw();
  Widget(QWidget *parent = nullptr);
  ~Widget();
  int vertex_type = 0;  // можно перекинуть в прайвет и там уже сделать метод
                        // геттер и сеттер и переместить
  int line_type = 0;
  float vertex_size;
  int projection_type = 1;
  QColor color_back;
  QColor color_line;
  QColor color_point;
  QString new_path;
  GLfloat x = 0.f;
  GLfloat y = 0.f;
  GLfloat z = 0.f;
  GLfloat ox = INFINITY;
  GLfloat oy = INFINITY;
  GLfloat oz = INFINITY;  // можно же убрать
  float line_width = 0;

 protected:
  void initializeGL();
  void resizeGL(int w, int h);
  void paintGL();
  void draw_points();
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void wheelEvent(QWheelEvent *event);
  void initShaders();
  void loadOBJ(const QString &path, int *code_error);

 private:
  QMatrix4x4 projectmatrix;
  QOpenGLShaderProgram project_shader;
  QOpenGLBuffer m_arrayBuffer;  // буфер вершин
  QOpenGLBuffer m_indexBuffer;  // индексный буффер
  QVector2D m_mousePosition;
  QQuaternion m_rotation;
  QQuaternion scale_;
  struct Options {
    int projection_type;
    int line_type;
    float color_line[3];
    float line_width;
    float vertex_size;
    float color_vertex[3];
    float color_back[3];
    QString new_path;
  };
  Options sample;
  GLfloat degree = 1.0;
  float aspect = 0;
};

#endif  // WIDGET_H
