#ifndef CPP4_3DVIEWER_V_2_0_SRC_CONTROLLER_H_
#define CPP4_3DVIEWER_V_2_0_SRC_CONTROLLER_H_

#include "model.h"
#include "settings.h"

namespace s21 {

class S21Controller {
 public:
  S21Controller(S21Model *model, S21Settings *settings)
      : model_(model), settings_(settings) {}
  ~S21Controller() {}

  int SetData(std::string str_file_name);
  double GetMoveFactor();
  double &GetValueX(int n_poligon, int n_vertices);
  double GetValueY(int n_poligon, int n_vertices);
  double GetValueZ(int n_poligon, int n_vertices);
  int GetCountVectices();
  int GetCountPoligons();
  int GetSizePoligon(int n_poligon);
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
  void AffinCommand(int command, double value);
  void AffinCommandCancel();
  void AffinCommandRollBack();

 private:
  S21Model *model_;
  S21Settings *settings_;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V_2_0_SRC_CONTROLLER_H_
