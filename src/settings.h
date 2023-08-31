#ifndef CPP4_3DVIEWER_V_2_0_SRC_SETTINGS_H_
#define CPP4_3DVIEWER_V_2_0_SRC_SETTINGS_H_

#include <fstream>

namespace s21 {

class S21Settings {
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

  void SetupSettingsFunction(std::string filename);
  void SaveSettingsFunction(std::string filename);
  int GetViewingPoints();
  int GetPointShape();
  int GetPointSize();
  int GetColorPoints();
  int GetViewingLine();
  int GetLineStipple();
  int GetLineThickness();
  int GetColorLines();
  int GetBackgroundColor();
  int GetIsometric();

  void SetViewingPoints(int value);
  void SetPointShape(int value);
  void SetPointSize(int value);
  void SetColorPoints(int value);
  void SetViewingLine(int value);
  void SetLineStipple(int value);
  void SetLineThickness(int value);
  void SetColorLines(int value);
  void SetBackgroundColor(int value);
  void SetIsometric(int value);

 private:
  struct Settings {
    int point_view_;
    int point_shape_;
    int point_size_;
    int point_color_;
    int line_view_;
    int line_stipple_;
    int line_thickness_;
    int lines_color_;
    int background_color_;
    int isometric_;
  };

  int ReadSettingsFromFile(std::string filename);

  Settings settings_;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_v_2_0_SRC_SETTINGS_H_
