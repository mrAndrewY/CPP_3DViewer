#ifndef CPP4_3DVIEWER_V_2_0_SRC_MODEL_H_
#define CPP4_3DVIEWER_V_2_0_SRC_MODEL_H_

#include <fstream>
#include <string>

#include "multipult.h"

namespace s21 {

class S21Model {
 public:
  enum CodeError {
    err_ok,
    err_file_open,
    err_file_empty,
    err_file_fault,
    err_count_poligon,
    err_vertices,
    err_polygons
  };

  S21Model();
  ~S21Model();

  int FillData(std::string name_file);
  double &GetAxisValue(int n_poligon, int num_vertices, int num_axis);
  int GetCountVectices();
  int GetCountPoligons();
  int GetSizePoligons(int n_poligon);
  void AffinCommand(int command, double value);
  void AffinCommandCancel();
  void AffinCommandRollBack();
  double GetMoveScale();

 private:
  struct PoligonsData {
    int *array;
    int count_points;
  };

  struct ObjectData {
    int vertices_count_{};
    int poligons_count_{};
    double **matrix_{nullptr};
    PoligonsData *array_poligons_{nullptr};
  };

  int CheckOpenFile(std::string name_file);
  int CountVerticesAndPoligons(std::string name_file);
  int CreateData(std::string name_file);
  int CreateArrayPoligons(std::string str, int num_array, int count_row);
  int GetCountAndDigit(std::string str, size_t &pos, int &count, int &digit);
  void DeleteData();
  void CreateMultipult();

  double min_x_ = 0, min_y_ = 0, min_z_ = 0, max_x_ = 0, max_y_ = 0, max_z_ = 0,
         move_scale_ = 1;
  ObjectData data_;
  Multipult *multipult_{nullptr};
  Affins *affins_{nullptr};
  std::string name_file_ = "";
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V_2_0_SRC_MODEL_H_
