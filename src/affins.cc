#include "affins.h"

namespace s21 {

void Affins::MoveX(double **m, double x_step, int v_count) {
  for (int curr_row = 0; curr_row < v_count; curr_row++) {
    m[curr_row][kXaxis] += x_step;
  }
}

void Affins::MoveY(double **m, double y_step, int v_count) {
  for (int curr_row = 0; curr_row < v_count; curr_row++)
    m[curr_row][kYaxis] += y_step;
}

void Affins::MoveZ(double **m, double z_step, int v_count) {
  for (int curr_row = 0; curr_row < v_count; curr_row++)
    m[curr_row][kZaxis] += z_step;
}

double Affins::GetMoveScale(double min_x, double min_y, double min_z,
                            double max_x, double max_y, double max_z) {
  double x_diff, y_diff, z_diff, res;
  x_diff = fabs(max_x - min_x);
  y_diff = fabs(max_y - min_y);
  z_diff = fabs(max_z - min_z);
  res = x_diff;
  if (y_diff > res) res = y_diff;
  if (z_diff > res) res = z_diff;
  res /= this->KMoveSpeedCorrector;
  return res;
}

void Affins::RotateObjectXaxis(double **m, double angle, int v_count) {
  angle = angle / kOneRadian;
  for (int i = 1; i < v_count; i++) {
    double temp_y = m[i][kYaxis];
    double temp_z = m[i][kZaxis];
    m[i][1] = cos(angle) * (temp_y - m[kObjectCenter][kYaxis]) +
              (-sin(angle)) * (temp_z - m[kObjectCenter][kZaxis]) +
              m[kObjectCenter][1];
    m[i][2] = sin(angle) * (temp_y - m[kObjectCenter][kYaxis]) +
              cos(angle) * (temp_z - m[kObjectCenter][kZaxis]) +
              m[kObjectCenter][2];
  }
}

void Affins::RotateObjectYaxis(double **m, double angle, int v_count) {
  angle = angle / kOneRadian;
  for (int i = 1; i < v_count; i++) {
    double temp_x = m[i][kXaxis];
    double temp_z = m[i][kZaxis];
    m[i][0] = cos(angle) * (temp_x - m[0][kXaxis]) +
              sin(angle) * (temp_z - m[kObjectCenter][kZaxis]) +
              m[kObjectCenter][kXaxis];
    m[i][2] = -sin(angle) * (temp_x - m[0][kXaxis]) +
              cos(angle) * (temp_z - m[kObjectCenter][kZaxis]) +
              m[kObjectCenter][kZaxis];
  }
}

void Affins::RotateObjectZaxis(double **m, double angle, int v_count) {
  angle = angle / kOneRadian;
  for (int i = 1; i < v_count; i++) {
    double temp_x = m[i][kXaxis];
    double temp_y = m[i][kYaxis];
    m[i][0] = cos(angle) * (temp_x - m[kObjectCenter][kXaxis]) +
              (-sin(angle)) * (temp_y - m[kObjectCenter][kYaxis]) + m[0][0];
    m[i][1] = sin(angle) * (temp_x - m[kObjectCenter][kXaxis]) +
              cos(angle) * (temp_y - m[kObjectCenter][kYaxis]) + m[0][kYaxis];
  }
}

void Affins::GetMinMax(double &min_x, double &min_y, double &min_z,
                       double &max_x, double &max_y, double &max_z, double **m,
                       int v_count) {
  min_x = max_x = m[1][kXaxis];
  min_y = max_y = m[1][kYaxis];
  min_z = max_z = m[1][kZaxis];
  for (int i = 1; i < v_count; i++) {
    if (min_x > m[i][kXaxis]) {
      min_x = m[i][kXaxis];
    }
    if (max_x < m[i][kXaxis]) {
      max_x = m[i][kXaxis];
    }
    if (min_y > m[i][kYaxis]) {
      min_y = m[i][kYaxis];
    }
    if (max_y < m[i][kYaxis]) {
      max_y = m[i][kYaxis];
    }
    if (min_z > m[i][kZaxis]) {
      min_z = m[i][kZaxis];
    }
    if (max_z < m[i][kZaxis]) {
      max_z = m[i][kZaxis];
    }
  }
}

void Affins::SetVertPosition(double min_x, double min_y, double min_z,
                             double max_x, double max_y, double max_z,
                             int v_count, double **m) {
  if ((max_z - min_z) > (max_x - min_x)) {
    RotateObjectYaxis(m, kRightAngle, v_count);
    GetMinMax(min_x, min_y, min_z, max_x, max_y, max_z, m, v_count);
  }
  double cam_space_x = max_x - min_x;
  double cam_space_y = max_y - min_y;
  double cam_shift_y = (max_y + min_y) / 2;
  if (cam_space_x > cam_shift_y) {
    for (int i = 0; i < v_count; ++i) {
      m[i][kYaxis] -= cam_shift_y;
      m[i][kZaxis] -= cam_space_x * 2;
    }
  } else {
    for (int i = 0; i < v_count; ++i) {
      m[i][kYaxis] -= cam_shift_y;
      m[i][kZaxis] -= cam_space_y * 2;
    }
  }
}

void Affins::AlignObjectToCenter(double **m, int v_count) {
  for (int i = v_count - 1; i >= 0; i--) {
    m[i][kXaxis] -= m[kObjectCenter][kXaxis];
    m[i][kYaxis] -= m[kObjectCenter][kYaxis];
    m[i][kZaxis] -= m[kObjectCenter][kZaxis];
  }
}

bool Affins::ScaleKoefCheckOk(double &scale_k) {
  return !((scale_k < 0.001 && scale_k >= 0) ||
           (scale_k > -0.001 && scale_k <= 0));
}

void Affins::ScalingObject(double **m, double scale_k, int v_count) {
  if (ScaleKoefCheckOk(scale_k)) {
    for (int i = 1; i < v_count; i++) {
      m[i][kXaxis] = (m[i][kXaxis] - m[kObjectCenter][kXaxis]) * scale_k +
                     m[kObjectCenter][kXaxis];
      m[i][kYaxis] = (m[i][kYaxis] - m[kObjectCenter][kYaxis]) * scale_k +
                     m[kObjectCenter][kYaxis];
      m[i][kZaxis] = (m[i][kZaxis] - m[kObjectCenter][kZaxis]) * scale_k +
                     m[kObjectCenter][kZaxis];
    }
  }
}

void Affins::ScalingObjectXAxis(double **m, double scale_k, int v_count) {
  if (ScaleKoefCheckOk(scale_k)) {
    for (int i = 1; i < v_count; i++) {
      m[i][kXaxis] = (m[i][kXaxis] - m[kObjectCenter][kXaxis]) * scale_k +
                     m[kObjectCenter][kXaxis];
    }
  }
}

void Affins::ScalingObjectYAxis(double **m, double scale_k, int v_count) {
  if (ScaleKoefCheckOk(scale_k)) {
    for (int i = 1; i < v_count; i++) {
      m[i][kYaxis] = (m[i][kYaxis] - m[kObjectCenter][kYaxis]) * scale_k +
                     m[kObjectCenter][kYaxis];
    }
  }
}

void Affins::ScalingObjectZAxis(double **m, double scale_k, int v_count) {
  if (ScaleKoefCheckOk(scale_k)) {
    for (int i = 1; i < v_count; i++) {
      m[i][kZaxis] = (m[i][kZaxis] - m[kObjectCenter][kZaxis]) * scale_k +
                     m[kObjectCenter][kZaxis];
    }
  }
}

void Affins::InitMatrixObjCenter(double **m, int v_count) {
  m[kObjectCenter][kXaxis] = 0;
  m[kObjectCenter][kYaxis] = 0;
  m[kObjectCenter][kZaxis] = 0;
  double min_x = m[1][kXaxis];
  double max_x = m[1][kXaxis];
  double min_y = m[1][kYaxis];
  double max_y = m[1][kYaxis];
  double min_z = m[1][kZaxis];
  double max_z = m[1][kZaxis];
  for (int i = 1; i < v_count; i++) {
    if (min_x > m[i][kXaxis]) min_x = m[i][kXaxis];
    if (max_x < m[i][kXaxis]) max_x = m[i][kXaxis];
    if (min_y > m[i][kYaxis]) min_y = m[i][kYaxis];
    if (max_y < m[i][kYaxis]) max_y = m[i][kYaxis];
    if (min_z > m[i][kZaxis]) min_z = m[i][kZaxis];
    if (max_z < m[i][kZaxis]) max_z = m[i][kZaxis];
  }
  m[kObjectCenter][kXaxis] = min_x + (max_x - min_x) / 2;
  m[kObjectCenter][kYaxis] = min_y + (max_y - min_y) / 2;
  m[kObjectCenter][kZaxis] = min_z + (max_z - min_z) / 2;
}

}  // namespace s21
