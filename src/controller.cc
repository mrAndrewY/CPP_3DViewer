#include "controller.h"

namespace s21 {

int S21Controller::SetData(std::string str_file_name) {
  return model_->FillData(str_file_name);
}

double S21Controller::GetMoveFactor() { return model_->GetMoveScale(); }

double& S21Controller::GetValueX(int n_poligon, int n_vertices) {
  return model_->GetAxisValue(n_poligon, n_vertices, 0);
}

double S21Controller::GetValueY(int n_poligon, int n_vertices) {
  return model_->GetAxisValue(n_poligon, n_vertices, 1);
}

double S21Controller::GetValueZ(int n_poligon, int n_vertices) {
  return model_->GetAxisValue(n_poligon, n_vertices, 2);
}

int S21Controller::GetCountVectices() { return model_->GetCountVectices(); }

int S21Controller::GetCountPoligons() { return model_->GetCountPoligons(); }

int S21Controller::GetSizePoligon(int n_poligon) {
  return model_->GetSizePoligons(n_poligon);
}

void S21Controller::SetupSettingsFunction(std::string filename) {
  return settings_->SetupSettingsFunction(filename);
}

void S21Controller::SaveSettingsFunction(std::string filename) {
  return settings_->SaveSettingsFunction(filename);
}

int S21Controller::GetViewingPoints() { return settings_->GetViewingPoints(); }

int S21Controller::GetPointShape() { return settings_->GetPointShape(); }

int S21Controller::GetPointSize() { return settings_->GetPointSize(); }

int S21Controller::GetColorPoints() { return settings_->GetColorPoints(); }

int S21Controller::GetViewingLine() { return settings_->GetViewingLine(); }

int S21Controller::GetLineStipple() { return settings_->GetLineStipple(); }

int S21Controller::GetLineThickness() { return settings_->GetLineThickness(); }

int S21Controller::GetColorLines() { return settings_->GetColorLines(); }

int S21Controller::GetBackgroundColor() {
  return settings_->GetBackgroundColor();
}

int S21Controller::GetIsometric() { return settings_->GetIsometric(); }

void S21Controller::SetViewingPoints(int value) {
  settings_->SetViewingPoints(value);
}

void S21Controller::SetPointShape(int value) {
  settings_->SetPointShape(value);
}

void S21Controller::SetPointSize(int value) { settings_->SetPointSize(value); }

void S21Controller::SetColorPoints(int value) {
  settings_->SetColorPoints(value);
}

void S21Controller::SetViewingLine(int value) {
  settings_->SetViewingLine(value);
}

void S21Controller::SetLineStipple(int value) {
  settings_->SetLineStipple(value);
}

void S21Controller::SetLineThickness(int value) {
  settings_->SetLineThickness(value);
}

void S21Controller::SetColorLines(int value) {
  settings_->SetColorLines(value);
}

void S21Controller::SetBackgroundColor(int value) {
  settings_->SetBackgroundColor(value);
}

void S21Controller::SetIsometric(int value) { settings_->SetIsometric(value); }

void S21Controller::AffinCommand(int command, double value) {
  model_->AffinCommand(command, value);
}

void S21Controller::AffinCommandCancel() { model_->AffinCommandCancel(); };

void S21Controller::AffinCommandRollBack() { model_->AffinCommandRollBack(); };

}  // namespace s21
