#include "model.h"

namespace s21 {

S21Model::S21Model() : affins_(new Affins) {}

S21Model::~S21Model() {
  DeleteData();
  delete affins_;
  if (multipult_) delete multipult_;
}

int S21Model::FillData(std::string name_file) {
  int err = err_ok;
  if (name_file != name_file_) {
    name_file_ = name_file;
    if (data_.vertices_count_ != 0 && data_.poligons_count_ != 0) {
      DeleteData();
    }
    err = CheckOpenFile(name_file);
    if (!err) {
      err = CountVerticesAndPoligons(name_file);
      if (!err) {
        if (data_.poligons_count_ > 0) {
          data_.array_poligons_ = new PoligonsData[data_.poligons_count_]();
        }
        data_.matrix_ = new double *[data_.vertices_count_ + 1] { nullptr };
        for (int i = 0; i < data_.vertices_count_ + 1; ++i) {
          data_.matrix_[i] = new double[3]();
        }
        err = CreateData(name_file);
        if (err) {
          DeleteData();
        } else {
          delete multipult_;
          CreateMultipult();
          affins_->InitMatrixObjCenter(data_.matrix_,
                                       data_.vertices_count_ + 1);
          affins_->GetMinMax(min_x_, min_y_, min_z_, max_x_, max_y_, max_z_,
                             data_.matrix_, data_.vertices_count_ + 1);
          affins_->SetVertPosition(min_x_, min_y_, min_z_, max_x_, max_y_,
                                   max_z_, data_.vertices_count_ + 1,
                                   data_.matrix_);
          move_scale_ = affins_->GetMoveScale(min_x_, min_y_, min_z_, max_x_,
                                              max_y_, max_z_);
        }
      }
    }
  }
  return err;
}

int S21Model::CheckOpenFile(std::string name_file) {
  int err = err_ok;
  std::ifstream file(name_file);
  if (!file) {
    err = err_file_open;
  } else {
    std::string line;
    std::getline(file, line);
    if (line.empty()) {
      err = err_file_empty;
    }
  }
  file.close();
  return err;
}

int S21Model::CountVerticesAndPoligons(std::string name_file) {
  int err = err_ok, vertices = 0, poligons = 0;
  std::ifstream file(name_file);
  std::string line;
  while (std::getline(file, line)) {
    if (line[0] == 'v' && line[1] == ' ') {
      vertices++;
    } else if (line[0] == 'f' && line[1] == ' ') {
      poligons++;
    }
  }
  file.close();
  if (vertices) {
    data_.vertices_count_ = vertices;
    data_.poligons_count_ = poligons;

  } else {
    err = err_vertices;
  }
  return err;
}

int S21Model::CreateData(std::string name_file) {
  int err = err_ok, count_row = 1, num_array = 0;
  double digit_x = 0, digit_y = 0, digit_z = 0;
  std::ifstream file(name_file);
  std::string line;
  setlocale(LC_ALL, "C");
  while (!err && std::getline(file, line)) {
    size_t shift = 2;
    if (line[0] == 'v' && line[1] == ' ') {
      try {
        size_t temp_shift = 0;
        digit_x = std::stod(line.substr(shift), &temp_shift);
        shift += temp_shift;
        digit_y = std::stod(line.substr(shift), &temp_shift);
        shift += temp_shift;
        digit_z = std::stod(line.substr(shift), &temp_shift);
      } catch (...) {
        err = err_vertices;
      }
      if (!err) {
        data_.matrix_[count_row][0] = digit_x;
        data_.matrix_[count_row][1] = digit_y;
        data_.matrix_[count_row][2] = digit_z;
        count_row++;
      }
    } else if (line[0] == 'f' && line[1] == ' ') {
      err = CreateArrayPoligons(line, num_array, count_row - 1);
      if (!err) {
        num_array++;
      } else if (err == err_count_poligon) {
        err = err_ok;
      }
    }
  }
  file.close();
  return err;
}

int S21Model::CreateArrayPoligons(std::string str, int num_array,
                                  int count_row) {
  int err = err_ok, count = 0, digit = 0;
  size_t shift = 2;
  while (!err && !str.substr(shift).empty()) {
    err = GetCountAndDigit(str, shift, count, digit);
  }
  digit = 0;
  if (!err && count > 1) {
    data_.array_poligons_[num_array].array = new int[count]();
    data_.array_poligons_[num_array].count_points = count;
    shift = 2;
    count = 0;
    while (!err && !str.substr(shift).empty()) {
      int last_count = count;
      err = GetCountAndDigit(str, shift, count, digit);
      if (!err && digit < 0) {
        digit = count_row + 1 + digit;
      }
      if (!err && (digit < 1 || digit > count_row)) {
        err = err_polygons;
      }
      if (last_count != count) {
        data_.array_poligons_[num_array].array[count - 1] = digit;
      }
    }
  } else if (count < 2) {
    data_.poligons_count_ -= 1;
    err = err_count_poligon;
  }
  return err;
}

int S21Model::GetCountAndDigit(std::string str, size_t &pos, int &count,
                               int &digit) {
  int err = err_ok;
  size_t shift = 0;
  if (str[pos] == 47 || str[pos] == 13 || str[pos] == 32) {
    while (str[pos] != 32 && str[pos] != 0 && str[pos] != 13) {
      pos++;
    }
  } else {
    try {
      digit = std::stoi(str.substr(pos), &shift);
    } catch (...) {
      err = err_polygons;
    }
    if (!err) {
      count++;
      pos += (shift - 1);
    }
  }
  if (str[pos] != '\0') {
    pos++;
  }
  return err;
}

void S21Model::DeleteData() {
  if (data_.matrix_ != nullptr) {
    for (int i = 0; i < data_.vertices_count_ + 1; ++i) {
      delete[] data_.matrix_[i];
    }
    delete[] data_.matrix_;
  }
  if (data_.array_poligons_ != nullptr) {
    for (int i = 0; i < data_.poligons_count_; ++i) {
      delete[] data_.array_poligons_[i].array;
    }
    delete[] data_.array_poligons_;
  }
  data_.vertices_count_ = 0;
  data_.poligons_count_ = 0;
  data_.matrix_ = nullptr;
  data_.array_poligons_ = nullptr;
}

double &S21Model::GetAxisValue(int n_poligon, int num_vertices, int num_axis) {
  return data_
      .matrix_[data_.array_poligons_[n_poligon].array[num_vertices]][num_axis];
}

int S21Model::GetCountVectices() { return data_.vertices_count_; }

int S21Model::GetCountPoligons() { return data_.poligons_count_; }

int S21Model::GetSizePoligons(int n_poligon) {
  return data_.array_poligons_[n_poligon].count_points;
}

void S21Model::CreateMultipult() {
  multipult_ = new Multipult(affins_, data_.matrix_, data_.vertices_count_ + 1);
}

void S21Model::AffinCommand(int command, double value) {
  multipult_->PressOnCommand(command, value);
}

void S21Model::AffinCommandCancel() { multipult_->PressCanselCommand(); }

void S21Model::AffinCommandRollBack() { multipult_->PressRollBackCommand(); }

double S21Model::GetMoveScale() { return move_scale_; }

}  // namespace s21
