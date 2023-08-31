#include "commands.h"

namespace s21 {

ICommand::ICommand(Affins *affins) : aff_(affins) {
  memento_ = new S21Memento();
}

ICommand::~ICommand() {
  if (memento_) {
    delete memento_;
    memento_ = nullptr;
  }
}

void CommandMoveX::ExecOn(double **matrix, double step_value, int v_count) {
  aff_->MoveX(matrix, step_value, v_count);
  memento_->shift_x_value_ += step_value;
}

void CommandMoveX::ExecOff(double **matrix, double step_value, int v_count) {
  aff_->MoveX(matrix, step_value * (-1), v_count);
  memento_->shift_x_value_ -= step_value;
}

double CommandMoveX::getActionValue() { return memento_->shift_x_value_; }

void CommandMoveY::ExecOn(double **matrix, double step_value, int v_count) {
  aff_->MoveY(matrix, step_value, v_count);
  memento_->shift_y_value_ += step_value;
}

void CommandMoveY::ExecOff(double **matrix, double step_value, int v_count) {
  aff_->MoveY(matrix, step_value * (-1), v_count);
  memento_->shift_y_value_ -= step_value;
}

double CommandMoveY::getActionValue() { return memento_->shift_y_value_; }

void CommandMoveZ::ExecOn(double **matrix, double step_value, int v_count) {
  aff_->MoveZ(matrix, step_value, v_count);
  memento_->shift_z_value_ += step_value;
}

void CommandMoveZ::ExecOff(double **matrix, double step_value, int v_count) {
  aff_->MoveZ(matrix, step_value * (-1), v_count);
  memento_->shift_z_value_ -= step_value;
}

double CommandMoveZ::getActionValue() { return memento_->shift_z_value_; }

void CommandRotateX::ExecOn(double **matrix, double step_value, int v_count) {
  aff_->RotateObjectXaxis(matrix, step_value, v_count);
  memento_->rotate_x_value_ += step_value;
}

void CommandRotateX::ExecOff(double **matrix, double step_value, int v_count) {
  aff_->RotateObjectXaxis(matrix, step_value * (-1), v_count);
  memento_->rotate_x_value_ -= step_value;
}

double CommandRotateX::getActionValue() { return 1.0; }

void CommandRotateY::ExecOn(double **matrix, double step_value, int v_count) {
  aff_->RotateObjectYaxis(matrix, step_value, v_count);
  memento_->rotate_y_value_ += step_value;
}

void CommandRotateY::ExecOff(double **matrix, double step_value, int v_count) {
  aff_->RotateObjectYaxis(matrix, step_value * (-1), v_count);
  memento_->rotate_y_value_ -= step_value;
}

double CommandRotateY::getActionValue() { return 1.0; }

void CommandRotateZ::ExecOn(double **matrix, double step_value, int v_count) {
  aff_->RotateObjectZaxis(matrix, step_value, v_count);
  memento_->rotate_z_value_ += step_value;
}

void CommandRotateZ::ExecOff(double **matrix, double step_value, int v_count) {
  aff_->RotateObjectZaxis(matrix, step_value * (-1), v_count);
  memento_->rotate_z_value_ -= step_value;
}

double CommandRotateZ::getActionValue() { return 1.0; }

void CommandScale::ExecOn(double **matrix, double step_value, int v_count) {
  aff_->ScalingObject(matrix, step_value, v_count);
  memento_->scale_common_value_ *= step_value;
}

void CommandScale::ExecOff(double **matrix, double step_value, int v_count) {
  aff_->ScalingObject(matrix, 1 / step_value, v_count);
  memento_->scale_common_value_ /= step_value;
}

double CommandScale::getActionValue() { return memento_->scale_common_value_; }

void CommandXScale::ExecOn(double **matrix, double step_value, int v_count) {
  aff_->ScalingObjectXAxis(matrix, step_value, v_count);
  memento_->scale_x_value_ *= step_value;
}

void CommandXScale::ExecOff(double **matrix, double step_value, int v_count) {
  aff_->ScalingObjectXAxis(matrix, 1 / step_value, v_count);
  memento_->scale_x_value_ /= step_value;
}

double CommandXScale::getActionValue() { return memento_->scale_x_value_; }

void CommandYScale::ExecOn(double **matrix, double step_value, int v_count) {
  aff_->ScalingObjectYAxis(matrix, step_value, v_count);
  memento_->scale_y_value_ *= step_value;
}

void CommandYScale::ExecOff(double **matrix, double step_value, int v_count) {
  aff_->ScalingObjectYAxis(matrix, 1 / step_value, v_count);
  memento_->scale_y_value_ /= step_value;
}

double CommandYScale::getActionValue() { return memento_->scale_y_value_; }

void CommandZScale::ExecOn(double **matrix, double step_value, int v_count) {
  aff_->ScalingObjectZAxis(matrix, step_value, v_count);
  memento_->scale_z_value_ *= step_value;
}

void CommandZScale::ExecOff(double **matrix, double step_value, int v_count) {
  aff_->ScalingObjectZAxis(matrix, 1 / step_value, v_count);
  memento_->scale_z_value_ /= step_value;
}

double CommandZScale::getActionValue() { return memento_->scale_z_value_; }

}  // namespace s21
