#ifndef CPP4_3DVIEWER_V_2_0_SRC_MEMENTO_H
#define CPP4_3DVIEWER_V_2_0_SRC_MEMENTO_H

namespace s21 {

class S21Memento {
 private:
  friend class CommandMoveX;
  friend class CommandMoveY;
  friend class CommandMoveZ;
  friend class CommandRotateX;
  friend class CommandRotateY;
  friend class CommandRotateZ;
  friend class CommandScale;
  friend class CommandXScale;
  friend class CommandYScale;
  friend class CommandZScale;
  friend class Multipult;

  double shift_x_value_ = 0;
  double shift_y_value_ = 0;
  double shift_z_value_ = 0;
  double rotate_x_value_ = 0;
  double rotate_y_value_ = 0;
  double rotate_z_value_ = 0;
  double scale_common_value_ = 1;
  double scale_x_value_ = 1;
  double scale_y_value_ = 1;
  double scale_z_value_ = 1;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V_2_0_SRC_MEMENTO_H
