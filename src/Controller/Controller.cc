#include "Controller.h"

/// @brief Поворот модели относительно оси ox через контроллер
/// @param angle угол поворота
void s21::Controller::controller_rotation_by_ox(GLfloat angle) {
  model_.rotation_by_ox(angle);
}
/// @brief Поворот модели относительно оси oу через контроллер
/// @param angle угол поворота
void s21::Controller::controller_rotation_by_oy(GLfloat angle) {
  model_.rotation_by_oy(angle);
}

/// @brief Поворот модели относительно оси oz через контроллер
/// @param angle угол поворота
void s21::Controller::controller_rotation_by_oz(GLfloat angle) {
  model_.rotation_by_oz(angle);
}
/// @brief вызов парсера контроллером
/// @param filename имя файла
void s21::Controller::controller_parser(std::string filename) {
  model_.parser(filename);
}
/// @brief получение контроллером QVectror полигонов
/// @return возвращает вектор полигонов
QVector<GLuint> const &s21::Controller::controller_get_polygons() {
  return model_.get_polygons();
}
/// @brief получение контроллером QVectror вершин
/// @return возвращает вектор вершин
QVector<GLfloat> const &s21::Controller::controller_get_vertixes() {
  return model_.get_vertixes();
}
/// @brief получает размер вектора полигонов
/// @return размер вектора полигонов
int s21::Controller::get_poligons() {
  return (int)model_.get_polygons().length();
}
/// @brief получает размер вектора вершин
/// @return размер вектора вершин
int s21::Controller::get_vertixes() {
  return (int)model_.get_vertixes().length();
}
