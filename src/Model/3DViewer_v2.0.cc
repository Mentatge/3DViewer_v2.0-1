#include "3DViewer_v2.0.h"

/// @brief парсер файла
/// @param filename имя файла
void s21::back::parser(std::string filename) {
  std::string str_buffer;

  std::ifstream file(filename);
  if (file.is_open()) {
    if (file.peek() != EOF) {
      file.clear();
      file.seekg(0L, std::ios_base::beg);
      if (vertexes_.size() != 0) {
        vertexes_.clear();
      }
      if (polygons_.size() != 0) {
        polygons_.clear();
      }

      while (std::getline(file, str_buffer)) {
        const char *buffer = str_buffer.c_str();
        QString buffer1 = QString::fromStdString(str_buffer);
        if (buffer[0] == 'v' && buffer[1] == ' ') {
          QStringList list = buffer1.split(' ');
          int i = 1;
          if (buffer[1] == ' ' && buffer[2] == ' ') {
            i++;
          }
          for (; i < list.count(); i++) {
            vertexes_.push_back(list[i].toFloat());
          }
        } else if (buffer[0] == 'f' && buffer[1] == ' ') {
          std::string fValue(buffer);
          GetFNumFromStr_(fValue);
        }
      }
      normalisation();
    } else {
      throw std::invalid_argument("error of file");
    }
    file.close();
  } else {
    throw std::invalid_argument("error of file");
  }
}
/// @brief парсер для F флагов
/// @param str строка для парсера
void s21::back::GetFNumFromStr_(std::string str) {
  size_t counter = 0;
  std::string::iterator it_buf;
  std::string numbers("0123456789");
  bool flag = 1;
  str = str.substr(str.find(' ') + 1, str.size() - str.find(' ') - 1);

  while (flag) {
    if (counter != 0 && str.find_first_of(numbers) != std::string::npos) {
      polygons_.push_back(std::stoi(str) - 1);
    }
    it_buf = std::find(str.begin(), str.end(), ' ');
    if (it_buf == str.end() ||
        str.find_first_of(numbers) == std::string::npos) {
      flag = 0;
    } else {
      polygons_.push_back(std::stoi(str) - 1);
      str = str.substr(str.find(' ') + 1, str.size() - str.find(' ') - 1);
    }
    counter++;
  }
}

/// @brief функция по возврату вектора полигонов
/// @return вектор полигонов
QVector<GLuint> const &s21::back::get_polygons() { return polygons_; }

/// @brief функция по возврату вектора вершин
/// @return  вектор вершин
QVector<GLfloat> const &s21::back::get_vertixes() { return vertexes_; }

/// @brief функция нормализации значения от 0 до 1
void s21::back::normalisation() {
  double max = 0;
  for (auto i : vertexes_) {
    if (fabs(i) > max) {
      max = fabs(i);
    }
  }
  size_t size = vertexes_.size();
  for (GLuint i = 0; i < size; i++) {
    vertexes_[i] /= max;
  }
}

/// @brief поворот фигуры относительно оси ох
/// @param angle угол поворота
void s21::back::rotation_by_ox(GLfloat angle) {
  angle = qDegreesToRadians(angle);
  for (GLuint i = 0; i < vertexes_.size(); i = i + 3) {
    vertexes_[i + 1] =
        vertexes_[i + 1] * cos(angle) - vertexes_[i + 2] * cos(angle);
    vertexes_[i + 2] =
        vertexes_[i + 2] * cos(angle) + vertexes_[i + 2] * cos(angle);
  }
}

/// @brief поворот фигуры относительно оси оу
/// @param angle угол поворота
void s21::back::rotation_by_oy(GLfloat angle) {
  angle = qDegreesToRadians(angle);
  for (unsigned int i = 0; i < vertexes_.size(); i += 3) {
    float temp_x = vertexes_[i];
    float temp_z = vertexes_[i + 2];
    vertexes_[i] = cos(angle) * temp_x - sin(angle) * temp_z;
    vertexes_[i + 2] = sin(angle) * temp_x + cos(angle) * temp_z;
  }
}

/// @brief поворот фигуры относительно оси oz
/// @param angle угол поворота
void s21::back::rotation_by_oz(GLfloat angle) {
  angle = qDegreesToRadians(angle);
  for (unsigned int i = 0; i < vertexes_.size(); i += 3) {
    float temp_x = vertexes_[i];
    float temp_y = vertexes_[i + 1];
    vertexes_[i] = cos(angle) * temp_x - sin(angle) * temp_y;
    vertexes_[i + 1] = sin(angle) * temp_x + cos(angle) * temp_y;
  }
}
