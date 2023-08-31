#ifndef CPP4_3DVIEWER_V_2_0_SRC_VIEW_H_
#define CPP4_3DVIEWER_V_2_0_SRC_VIEW_H_

#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QMainWindow>
#include <QPainter>

#include "controller.h"
#include "glwidget.h"
#include "qgifimage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class S21View;
}
QT_END_NAMESPACE

namespace s21 {

class S21View : public QMainWindow {
  Q_OBJECT

 public:
  S21View(S21Controller *controller);
  ~S21View();

 private:
  Ui::S21View *ui_;
  S21Controller *controller_;
  GLWidget *glwidget_;
  QDir dir_path_;
  bool is_clicked_l_ = false;
  bool is_clicked_r_ = false;
  bool mouse_enable_ = false;
  double rotate_factor_ = 2.0;
  double scale_down_factor_ = 0.8;
  double scale_up_factor_ = 1.2;

 private slots:
  void FilePushButtonClicked();
  void ShiftWindow();
  void ShiftClear();
  void RotateWindow();
  void RotateClear();
  void ScaleWindow();
  void ScaleClear();
  void SaveImage();
  void ClearImageForGif();
  void SaveImageForGif();
  void CreateGif();
  void UpdateSettings();
  void GetSettings();
  void MouseMove();
  void MouseMoveMiddle();
  void MouseRotate();
  void MouseScale();
  void AffinCommandCancel();
  void AffinCommandRollBack();
  void SetBuzy();
  void SetReady();
  void ButtonsEnable(bool condition);
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V_2_0_SRC_VIEW_H_
