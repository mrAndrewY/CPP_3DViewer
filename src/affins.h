#ifndef CPP4_3DVIEWER_V_2_0_SRC_AFFINS_H_
#define CPP4_3DVIEWER_V_2_0_SRC_AFFINS_H_

#include <math.h>

namespace s21 {

class Affins {
 public:
  void MoveX(double **m, double x_step, int v_count);
  void MoveY(double **m, double y_step, int v_count);
  void MoveZ(double **m, double z_step, int v_count);
  void RotateObjectXaxis(double **m, double angle, int v_count);
  void RotateObjectYaxis(double **m, double angle, int v_count);
  void RotateObjectZaxis(double **m, double angle, int v_count);
  void ScalingObject(double **m, double scale_k, int v_count);
  void ScalingObjectXAxis(double **m, double scale_k, int v_count);
  void ScalingObjectYAxis(double **m, double scale_k, int v_count);
  void ScalingObjectZAxis(double **m, double scale_k, int v_count);
  void AlignObjectToCenter(double **m, int v_count);
  void InitMatrixObjCenter(double **m, int v_count);
  void GetMinMax(double &min_x, double &min_y, double &min_z, double &max_x,
                 double &max_y, double &max_z, double **m, int v_count);
  void SetVertPosition(double min_x, double min_y, double min_z, double max_x,
                       double max_y, double max_z, int v_count, double **m);
  double GetMoveScale(double min_x, double min_y, double min_z, double max_x,
                      double max_y, double max_z);

 private:
  enum AxisName { kXaxis = 0, kYaxis = 1, kZaxis = 2 };
  enum ObjectCenter { kObjectCenter = 0 };
  enum Angle { kRightAngle = 90 };

  bool ScaleKoefCheckOk(double &scale_k);

  constexpr static double KMoveSpeedCorrector = 1000;
  const static int KRightAngle = 90;
  constexpr static double kOneRadian = 57.2958;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V_2_0_SRC_AFFINS_H_
