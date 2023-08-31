#define GL_SILENCE_DEPRECATION

#include "glwidget.h"

namespace s21 {

GLWidget::GLWidget(S21Controller *controller)
    : QOpenGLWidget(nullptr), controller_(controller) {}

GLWidget::~GLWidget() { cleanup(); }

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
  if (event->buttons() == Qt::LeftButton) {
    mouse_x_coord_rotate_old = mouse_x_coord_rotate_new;
    mouse_y_coord_rotate_old = mouse_y_coord_rotate_new;
    mouse_x_coord_rotate_new = event->pos().y();
    mouse_y_coord_rotate_new = event->pos().x();
    emit MouseRotate();
  } else if (event->buttons() == Qt::MiddleButton) {
    mouse_z_coord_move_old = mouse_z_coord_move_new;
    mouse_z_coord_move_new = event->pos().y();
    emit MouseMoveMiddle();
  } else {
    mouse_x_coord_move_old = mouse_x_coord_move_new;
    mouse_y_coord_move_old = mouse_y_coord_move_new;
    mouse_x_coord_move_new = event->pos().x();
    mouse_y_coord_move_new = event->pos().y();
    emit MouseMove();
  }
}

void GLWidget::mousePressEvent(QMouseEvent *event) {
  if (event->buttons() == Qt::LeftButton) {
    mouse_x_coord_rotate_new = event->pos().y();
    mouse_y_coord_rotate_new = event->pos().x();
  } else if (event->buttons() == Qt::MiddleButton) {
    mouse_z_coord_move_new = event->pos().y();
    mouse_z_coord_move_new = event->pos().y();
  } else {
    mouse_x_coord_move_new = event->pos().x();
    mouse_y_coord_move_new = event->pos().y();
  }
}

void GLWidget::wheelEvent(QWheelEvent *event) {
  if (event->angleDelta().y() == wheel_step_up_) {
    scroll_up = true;
  } else {
    scroll_up = false;
  }
  emit MouseScale();
}

void GLWidget::initializeGL() { initializeOpenGLFunctions(); }

void GLWidget::paintGL() {
  SettingsView();
  if (controller_->GetViewingLine()) {
    glBegin(GL_LINES);
    SwitchColor(controller_->GetColorLines());
    for (int i = 0; i < controller_->GetCountPoligons(); ++i) {
      int k = controller_->GetSizePoligon(i);

      for (int j = 0; (j + 1) < k; ++j) {
        double *first_point_coord = &(controller_->GetValueX(i, j));
        double *second_point_coord = &(controller_->GetValueX(i, j + 1));
        glVertex3d(*first_point_coord, *(first_point_coord + 1),
                   *(first_point_coord + 2));
        glVertex3d(*second_point_coord, *(second_point_coord + 1),
                   *(second_point_coord + 2));
      }
      if (k > 2) {
        double *first_point_coord = &(controller_->GetValueX(i, k - 1));
        double *second_point_coord = &(controller_->GetValueX(i, 0));
        glVertex3d(*first_point_coord, *(first_point_coord + 1),
                   *(first_point_coord + 2));
        glVertex3d(*second_point_coord, *(second_point_coord + 1),
                   *(second_point_coord + 2));
      }
    }
    glEnd();
  }
  if (controller_->GetViewingPoints()) {
    glBegin(GL_POINTS);
    SwitchColor(controller_->GetColorPoints());
    for (int i = 0; i < controller_->GetCountPoligons(); ++i) {
      int k = controller_->GetSizePoligon(i);
      for (int j = 0; j < k; ++j) {
        double *first_point_coord = &(controller_->GetValueX(i, j));
        glVertex3d(*first_point_coord, *(first_point_coord + 1),
                   *(first_point_coord + 2));
      }
    }
    glEnable(GL_POINT);
    glEnd();
  }
}

void GLWidget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void GLWidget::XRotate() { update(); }

QSize GLWidget::minimumSizeHint() const {
  return QSize(min_widget_size_, min_widget_size_);
}

QSize GLWidget::sizeHint() const { return QSize(width(), height()); }

void GLWidget::cleanup() {
  makeCurrent();
  doneCurrent();
  QObject::disconnect(context(), &QOpenGLContext::aboutToBeDestroyed, this,
                      &GLWidget::cleanup);
}

void GLWidget::SwitchBackgroundColor(int color) {
  float r, g, b;
  RGBColors colors;
  colors.GetColor(color, r, g, b);
  glClearColor(r, g, b, 1.0f);
}

void GLWidget::SwitchColor(int color) {
  float r, g, b;
  RGBColors colors;
  colors.GetColor(color, r, g, b);
  glColor4f(r, g, b, 1.0f);
}

void GLWidget::IsometricMode() {
  float aspectRatio =
      static_cast<float>(width()) / static_cast<float>(height());
  double box_space = controller_->GetMoveFactor() * izometric_scale_factor_;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (controller_->GetIsometric()) {
    if (aspectRatio > 1.0f) {
      glOrtho(-aspectRatio * izometric_box_size_ * box_space,
              aspectRatio * izometric_box_size_ * box_space,
              -izometric_box_size_ * box_space, izometric_box_size_ * box_space,
              -izometric_box_depth_, izometric_box_depth_);
    } else {
      glOrtho(-izometric_box_size_ * box_space, izometric_box_size_ * box_space,
              -izometric_box_size_ * box_space / aspectRatio,
              izometric_box_size_ * box_space / aspectRatio,
              -izometric_box_depth_, izometric_box_depth_);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  } else {
    if (aspectRatio > 1.0f) {
      glOrtho(-aspectRatio, aspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);
    } else {
      glOrtho(-1.0f, 1.0f, -1.0f / aspectRatio, 1.0f / aspectRatio, -1.0f,
              1.0f);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluPerspective(view_angle_, 1.0f, view_minimal_space_,
                   izometric_box_depth_);
  }
}

void GLWidget::SettingsView() {
  if (controller_->GetPointShape()) {
    glEnable(GL_POINT_SMOOTH);
  } else {
    glDisable(GL_POINT_SMOOTH);
  }

  glEnable(GL_BLEND);

  glPointSize(controller_->GetPointSize());

  glLineWidth(controller_->GetLineThickness());

  if (controller_->GetLineStipple()) {
    glLineStipple(7, 0xAAAA);
    glEnable(GL_LINE_STIPPLE);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }

  SwitchBackgroundColor(controller_->GetBackgroundColor());
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  IsometricMode();
}

}  // namespace s21
