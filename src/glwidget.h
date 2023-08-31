#ifndef CPP4_3DVIEWER_V_2_0_SRC_GLWIDGET_H_
#define CPP4_3DVIEWER_V_2_0_SRC_GLWIDGET_H_

#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>

#include "color.h"
#include "controller.h"

#ifdef Q_OS_MAC
#include <glu.h>
#else
#include <GL/glu.h>
#endif

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

namespace s21 {

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

 public:
  GLWidget(S21Controller *controller = nullptr);
  ~GLWidget();

  QSize minimumSizeHint() const override;
  QSize sizeHint() const override;

  double mouse_x_coord_move_old = 0;
  double mouse_y_coord_move_old = 0;
  double mouse_z_coord_move_old = 0;
  double mouse_x_coord_move_new = 0;
  double mouse_y_coord_move_new = 0;
  double mouse_z_coord_move_new = 0;
  double mouse_x_coord_rotate_old = 0;
  double mouse_y_coord_rotate_old = 0;
  double mouse_x_coord_rotate_new = 0;
  double mouse_y_coord_rotate_new = 0;
  bool scroll_up = false;

 public slots:
  void cleanup();
  void XRotate();

 signals:
  void MouseMove();
  void MouseMoveMiddle();
  void MouseRotate();
  void MouseScale();

 protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int width, int height) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;

 private:
  void SwitchBackgroundColor(int color);
  void SwitchColor(int color);
  void SettingsView();
  void IsometricMode();

  int wheel_step_up_ = 120;
  int min_widget_size_ = 50;
  float izometric_box_size_ = 500;
  float izometric_box_depth_ = 1000000;
  float view_angle_ = 45;
  float view_minimal_space_ = 0.01;
  float izometric_scale_factor_ = 1.5;

  S21Controller *controller_;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V_2_0_SRC_GLWIDGET_H_
