#include "widget.h"

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent), m_indexBuffer(QOpenGLBuffer::IndexBuffer) {}

Widget::~Widget() {}
/// @brief  инициализация гл
void Widget::initializeGL() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  initShaders();
}
/// @brief  изменение размеров рисунка
/// @param w ширина
/// @param h высота
void Widget::resizeGL(int w, int h) {
  float aspect = qreal(w) / qreal(h ? h : 1);
  projectmatrix.setToIdentity();
  if (projection_type == 1) {
    projectmatrix.perspective(45.0f, aspect, 0.8f, 1000.0f);
    projectmatrix.translate(0.0, 0.0, -2.0);
  } else if (projection_type == 0) {
    projectmatrix.ortho(-1.0f, 1.0f, -1.0f, 1.f, 0.1f, 1000.0f);
  }
}
/// @brief  отрисовка шейдеров
void Widget::paintGL() {
  sample.color_back[0] = color_back.red();
  sample.color_back[1] = color_back.green();
  sample.color_back[2] = color_back.blue();
  sample.color_line[0] = color_line.red();
  sample.color_line[1] = color_line.green();
  sample.color_line[2] = color_line.blue();
  float as = aspect;
  glClearColor(sample.color_back[0] / 255, sample.color_back[1] / 255,
               sample.color_back[2] / 255, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  QMatrix4x4 modelViewMatrix;
  QVector4D f_color(sample.color_line[0] / 255, sample.color_line[1] / 255,
                    sample.color_line[2] / 255, 1.0f);
  modelViewMatrix.setToIdentity();
  glLineWidth((GLfloat)line_width);
  //;
  if (projection_type == 1) {
    modelViewMatrix.perspective(45.0f, as, 0.8f, 1000.0f);
    modelViewMatrix.translate(0.0, 0.0, -2.0);
  } else if (projection_type == 0) {
    modelViewMatrix.ortho(-1.0f, 1.0f, -1.0f, 1.f, 0.1, 1000.0f);
  }
  modelViewMatrix.rotate(m_rotation);
  update();
  if (z == 0. && x == 0. && y == 0.) {
    modelViewMatrix.scale(degree);
  } else {
    modelViewMatrix.translate(x, y, z);
  }

  project_shader.bind();
  project_shader.setUniformValue("qt_ModelViewProjectionMatrix",
                                 projectmatrix * modelViewMatrix);
  m_arrayBuffer.bind();
  int verloc = project_shader.attributeLocation("qt_Vertex");
  project_shader.enableAttributeArray(verloc);
  project_shader.setAttributeBuffer(verloc, GL_FLOAT, 0, 3, 0);
  m_indexBuffer.bind();
  if (vertex_type != 0) {
    draw_points();
  }
  project_shader.setUniformValue("color", f_color);
  if (line_type == 1) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(7, 0x3333);
  }
  glDrawElements(GL_LINES, m_indexBuffer.size(), GL_UNSIGNED_INT, nullptr);
}
/// @brief  функция для нажатия на изображения мышкой
/// @param event событие
void Widget::mousePressEvent(QMouseEvent *event) {
  if (event->buttons() == Qt::LeftButton) {
    m_mousePosition = QVector2D(event->pos());
  }
}
/// @brief поворот изображения мышкой
/// @param event событие
void Widget::mouseMoveEvent(QMouseEvent *event) {
  if (event->buttons() != Qt::LeftButton) return;

  QVector2D diff = QVector2D(event->pos()) - m_mousePosition;
  m_mousePosition = QVector2D(event->pos());
  float anqle = diff.length() / 2.0;

  QVector3D axis = QVector3D(diff.y(), diff.x(), 0.0);

  m_rotation = QQuaternion::fromAxisAndAngle(axis, anqle) * m_rotation;

  update();
}
/// @brief приближение изображения сышкой
/// @param event событие
void Widget::wheelEvent(QWheelEvent *event) {
  GLfloat new_degree = event->angleDelta().y() / 100;
  if (new_degree > 0) {
    degree *= 1.1;
  }
  if (new_degree < 0) {
    degree *= 0.9;
  }
  update();
}
/// @brief инициализация шейдеров
void Widget::initShaders() {
  if (!project_shader.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                              ":/vshader.vsh"))
    close();

  if (!project_shader.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                              ":/fshader.fsh"))
    close();

  if (!project_shader.link()) close();
}

void Widget::draw_points() {
  if (vertex_type == 2)
    glEnable(GL_POINT_SMOOTH);
  else if (vertex_type == 1)
    glDisable(GL_POINT_SMOOTH);

  sample.color_vertex[0] = color_point.red();
  sample.color_vertex[1] = color_point.green();
  sample.color_vertex[2] = color_point.blue();
  glPointSize(vertex_size);
  QVector4D g_color(sample.color_vertex[0] / 255, sample.color_vertex[1] / 255,
                    sample.color_vertex[2] / 255, 1.0f);
  project_shader.setUniformValue("color", g_color);
  glDrawElements(GL_POINTS, m_indexBuffer.size(), GL_UNSIGNED_INT, nullptr);
}
/// @brief  основная функция отрисовки изображения
void Widget::draw() {
  m_indexBuffer.destroy();
  m_arrayBuffer.destroy();

  const QString path = new_path;

  try {
    controller_back.controller_parser(new_path.toStdString());
    if (ox != 0.) {
      controller_back.controller_rotation_by_ox(ox);
    }
    if (oy != 0.) {
      controller_back.controller_rotation_by_oy(oy);
    }
    if (oz != 0.) {
      controller_back.controller_rotation_by_oz(oz);
    }
    m_arrayBuffer.create();
    m_arrayBuffer.bind();

    m_arrayBuffer.allocate(
        controller_back.controller_get_vertixes().constData(),
        controller_back.controller_get_vertixes().size() * sizeof(GLfloat));
    m_arrayBuffer.release();
    m_indexBuffer.create();
    m_indexBuffer.bind();
    m_indexBuffer.allocate(
        controller_back.controller_get_polygons().constData(),
        controller_back.get_poligons() * sizeof(GLuint));
    m_indexBuffer.release();
  } catch (const std::invalid_argument &error) {
    QMessageBox msgBox;
    msgBox.setText("Logical errors.");
    msgBox.exec();
  }
}
