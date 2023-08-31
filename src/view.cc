#include "view.h"

#include "ui_view.h"

namespace s21 {

S21View::S21View(S21Controller *controller)
    : QMainWindow(nullptr), ui_(new Ui::S21View), controller_(controller) {
  ui_->setupUi(this);
  dir_path_ = QCoreApplication::applicationDirPath();
  QString file_name = dir_path_.path() + "/settings.txt";
  glwidget_ = new GLWidget(controller_);
  controller_->SetupSettingsFunction(file_name.toLocal8Bit().toStdString());
  LineAndPointColor lp_color;
  BackgroundColor bg_color;
  ColorComboBox l_color_add(&lp_color, ui_->lines_color);
  ColorComboBox p_color_add(&lp_color, ui_->points_color);
  ColorComboBox bg_color_add(&bg_color, ui_->back_color);
  GetSettings();
  ui_->w->addWidget(glwidget_);
  ButtonsEnable(false);

  connect(
      ui_->points_shape,
      static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
      this, &S21View::UpdateSettings);
  connect(ui_->openFile, &QPushButton::clicked, this,
          &S21View::FilePushButtonClicked);
  connect(ui_->save_image, &QPushButton::clicked, this, &S21View::SaveImage);
  connect(ui_->create_gif, &QPushButton::clicked, this, &S21View::CreateGif);
  connect(ui_->save_image_for_gif, &QPushButton::clicked, this,
          &S21View::SaveImageForGif);
  connect(ui_->clear_image_for_gif, &QPushButton::clicked, this,
          &S21View::ClearImageForGif);
  connect(ui_->undoButton, &QPushButton::clicked, this,
          &S21View::AffinCommandCancel);
  connect(ui_->roll_back, &QPushButton::clicked, this,
          &S21View::AffinCommandRollBack);
  connect(ui_->MoveButton, &QPushButton::clicked, this, &S21View::ShiftWindow);
  connect(ui_->Clear_XYZ_Button, &QPushButton::clicked, this,
          &S21View::ShiftClear);
  connect(ui_->RotateButton, &QPushButton::clicked, this,
          &S21View::RotateWindow);
  connect(ui_->Clear_XYZ_Rot_Button, &QPushButton::clicked, this,
          &S21View::RotateClear);
  connect(ui_->ScaleButton, &QPushButton::clicked, this, &S21View::ScaleWindow);
  connect(ui_->Clear_XYZ_Scale_Button, &QPushButton::clicked, this,
          &S21View::ScaleClear);
  connect(ui_->isometric, &QCheckBox::stateChanged, this,
          &S21View::UpdateSettings);
  connect(ui_->is_point_view, &QCheckBox::stateChanged, this,
          &S21View::UpdateSettings);
  connect(ui_->is_line_view, &QCheckBox::stateChanged, this,
          &S21View::UpdateSettings);
  connect(ui_->is_line_stipple, &QCheckBox::stateChanged, this,
          &S21View::UpdateSettings);
  connect(
      ui_->points_shape,
      static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
      this, &S21View::UpdateSettings);
  connect(
      ui_->points_color,
      static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
      this, &S21View::UpdateSettings);
  connect(
      ui_->lines_color,
      static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
      this, &S21View::UpdateSettings);
  connect(
      ui_->back_color,
      static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
      this, &S21View::UpdateSettings);
  connect(ui_->points_size,
          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this,
          &S21View::UpdateSettings);
  connect(ui_->line_thickness,
          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this,
          &S21View::UpdateSettings);
  connect(glwidget_, &GLWidget::MouseMove, this, &S21View::MouseMove);
  connect(glwidget_, &GLWidget::MouseMoveMiddle, this,
          &S21View::MouseMoveMiddle);
  connect(glwidget_, &GLWidget::MouseRotate, this, &S21View::MouseRotate);
  connect(glwidget_, &GLWidget::MouseScale, this, &S21View::MouseScale);
}

S21View::~S21View() {
  QString file_name = dir_path_.path() + "/settings.txt";
  controller_->SaveSettingsFunction(file_name.toLocal8Bit().toStdString());
  delete ui_;
  delete glwidget_;
}

void S21View::ButtonsEnable(bool condition) {
  ui_->MoveButton->setEnabled(condition);
  ui_->RotateButton->setEnabled(condition);
  ui_->ScaleButton->setEnabled(condition);
  ui_->undoButton->setEnabled(condition);
  ui_->roll_back->setEnabled(condition);
}

void S21View::MouseMove() {
  if (mouse_enable_ == true) {
    ui_->ZMoveEdit->setValue(0);
    ui_->XMoveEdit->setValue((glwidget_->mouse_x_coord_move_new -
                              glwidget_->mouse_x_coord_move_old) *
                             controller_->GetMoveFactor());
    ui_->YMoveEdit->setValue((glwidget_->mouse_y_coord_move_old -
                              glwidget_->mouse_y_coord_move_new) *
                             controller_->GetMoveFactor());
    emit ui_->MoveButton->clicked();
  }
}

void S21View::MouseMoveMiddle() {
  if (mouse_enable_ == true) {
    ui_->XMoveEdit->setValue(0);
    ui_->YMoveEdit->setValue(0);
    ui_->ZMoveEdit->setValue((glwidget_->mouse_z_coord_move_new -
                              glwidget_->mouse_z_coord_move_old) *
                             controller_->GetMoveFactor());
    emit ui_->MoveButton->clicked();
  }
}

void S21View::MouseRotate() {
  if (mouse_enable_ == true) {
    ui_->XRotEdit->setValue((glwidget_->mouse_x_coord_rotate_new -
                             glwidget_->mouse_x_coord_rotate_old) /
                            rotate_factor_);
    ui_->YRotEdit->setValue((glwidget_->mouse_y_coord_rotate_new -
                             glwidget_->mouse_y_coord_rotate_old) /
                            rotate_factor_);
    emit ui_->RotateButton->clicked();
  }
}

void S21View::MouseScale() {
  if (mouse_enable_ == true) {
    if (glwidget_->scroll_up == true) {
      ui_->XScaleEdit->setValue(scale_down_factor_);
      ui_->YScaleEdit->setValue(scale_down_factor_);
      ui_->ZScaleEdit->setValue(scale_down_factor_);
    } else {
      ui_->XScaleEdit->setValue(scale_up_factor_);
      ui_->YScaleEdit->setValue(scale_up_factor_);
      ui_->ZScaleEdit->setValue(scale_up_factor_);
    }
    emit ui_->ScaleButton->clicked();
  }
}

void S21View::UpdateSettings() {
  controller_->SetViewingPoints(ui_->is_point_view->isChecked() ? 1 : 0);
  controller_->SetPointShape(ui_->points_shape->currentIndex());
  controller_->SetPointSize(ui_->points_size->value());
  controller_->SetColorPoints(ui_->points_color->currentIndex());
  controller_->SetViewingLine(ui_->is_line_view->isChecked() ? 1 : 0);
  controller_->SetLineStipple(ui_->is_line_stipple->isChecked() ? 1 : 0);
  controller_->SetLineThickness(ui_->line_thickness->value());
  controller_->SetColorLines(ui_->lines_color->currentIndex());
  controller_->SetBackgroundColor(ui_->back_color->currentIndex());
  controller_->SetIsometric(ui_->isometric->isChecked() ? 1 : 0);
  glwidget_->update();
}

void S21View::GetSettings() {
  ui_->is_point_view->setChecked(controller_->GetViewingPoints());
  ui_->points_shape->setCurrentIndex(controller_->GetPointShape());
  ui_->points_size->setValue(controller_->GetPointSize());
  ui_->points_color->setCurrentIndex(controller_->GetColorPoints());
  ui_->is_line_view->setChecked(controller_->GetViewingLine());
  ui_->is_line_stipple->setChecked(controller_->GetLineStipple());
  ui_->line_thickness->setValue(controller_->GetLineThickness());
  ui_->lines_color->setCurrentIndex(controller_->GetColorLines());
  ui_->back_color->setCurrentIndex(controller_->GetBackgroundColor());
  ui_->isometric->setChecked(controller_->GetIsometric());
}

void S21View::FilePushButtonClicked() {
  SetBuzy();
  QString file_name;
  QDir file_open_dir = dir_path_;
  file_open_dir.cdUp();
  file_name = QFileDialog::getOpenFileName(
      this, "Open a .obj file", file_open_dir.path(),
      "OBJ Files (*.obj) ;; All Files (*.*)");
  if (file_name.isNull()) {
    ui_->labelStatus->setText("Error! File not selected.");
  } else {
    int err = controller_->SetData(file_name.toLocal8Bit().toStdString());
    if (!err) {
      QString dir_name = file_name;
      while (dir_name.contains("/")) {
        size_t l = dir_name.length();
        dir_name = dir_name.right(l - 1);
      }
      ui_->labelStatus->setText("File load success!");
      ui_->labelFileName->setText("File name: " + dir_name);
      int e_count = 0;
      for (int i = 0; i < controller_->GetCountPoligons(); ++i) {
        e_count += controller_->GetSizePoligon(i);
      }
      ui_->labelData->setText("Count Vertices: " +
                              QString::number(controller_->GetCountVectices()) +
                              ", Count Edge: " + QString::number(e_count));
      ButtonsEnable(true);
      mouse_enable_ = true;
    } else if (err <= 3) {
      ui_->labelStatus->setText("File open error!");
      ui_->labelData->setText("...");
      ui_->labelFileName->setText("...");
      ButtonsEnable(false);
      mouse_enable_ = false;
    } else if (err <= 4) {
      ui_->labelStatus->setText("Memory error!");
      ui_->labelData->setText("...");
      ui_->labelFileName->setText("...");
      ButtonsEnable(false);
      mouse_enable_ = false;
    } else if (err <= 5) {
      ui_->labelStatus->setText("Vertices error!");
      ui_->labelData->setText("...");
      ui_->labelFileName->setText("...");
      ButtonsEnable(false);
      mouse_enable_ = false;
    } else if (err <= 6) {
      ui_->labelStatus->setText("Polygons error!");
      ui_->labelData->setText("...");
      ui_->labelFileName->setText("...");
      ButtonsEnable(false);
      mouse_enable_ = false;
    } else {
      ui_->labelStatus->setText("Other error!");
      ui_->labelData->setText("...");
      ui_->labelFileName->setText("...");
      ButtonsEnable(false);
    }
  }
  SetReady();
  glwidget_->update();
}

void S21View::ShiftWindow() {
  controller_->AffinCommand(ICommand::kMoveX, ui_->XMoveEdit->value());
  controller_->AffinCommand(ICommand::kMoveY, ui_->YMoveEdit->value());
  controller_->AffinCommand(ICommand::kMoveZ, ui_->ZMoveEdit->value());
  glwidget_->update();
}

void S21View::ShiftClear() {
  ui_->XMoveEdit->setValue(0.0);
  ui_->YMoveEdit->setValue(0.0);
  ui_->ZMoveEdit->setValue(0.0);
}

void S21View::RotateWindow() {
  controller_->AffinCommand(ICommand::kRotateX, ui_->XRotEdit->value());
  controller_->AffinCommand(ICommand::kRotateY, ui_->YRotEdit->value());
  controller_->AffinCommand(ICommand::kRotateZ, ui_->ZRotEdit->value());
  glwidget_->update();
}

void S21View::RotateClear() {
  ui_->XRotEdit->setValue(0.0);
  ui_->YRotEdit->setValue(0.0);
  ui_->ZRotEdit->setValue(0.0);
}

void S21View::ScaleWindow() {
  controller_->AffinCommand(ICommand::kXScale, ui_->XScaleEdit->value());
  controller_->AffinCommand(ICommand::kYScale, ui_->YScaleEdit->value());
  controller_->AffinCommand(ICommand::kZScale, ui_->ZScaleEdit->value());
  glwidget_->update();
}

void S21View::ScaleClear() {
  ui_->XScaleEdit->setValue(1.0);
  ui_->YScaleEdit->setValue(1.0);
  ui_->ZScaleEdit->setValue(1.0);
}

void S21View::AffinCommandCancel() {
  controller_->AffinCommandCancel();
  glwidget_->update();
}

void S21View::AffinCommandRollBack() {
  controller_->AffinCommandRollBack();
  glwidget_->update();
}

void S21View::SaveImage() {
  QString file_name;
  file_name = QFileDialog::getSaveFileName(
      this, "Save a .obj file", dir_path_.path() + "/Screenshot.bmp",
      "BMP Files (*.bmp) ;; JPG Files (*.jpg) ;; PNG Files (*.png)");
  if (file_name.isNull()) {
    ui_->labelStatus->setText("Error! File for screenshot not selected.");
  } else {
    ui_->labelStatus->setText("Screenshot saved success!");
    glwidget_->grabFramebuffer().save(file_name);
  }
}

void S21View::SaveImageForGif() {
  QDir dir = dir_path_.path() + "/ForGif";
  if (!dir.exists()) {
    dir.mkpath(dir.path());
  }
  QString tmp = ui_->CountGifImage->text().left(2);
  int count = tmp.toInt();
  if (count < 50) {
    QString file_name = dir.path() + "/";
    if (count < 10) {
      file_name += "0" + ui_->CountGifImage->text().left(1) + ".png";
    } else {
      file_name += ui_->CountGifImage->text().left(2) + ".png";
    }
    ui_->labelStatus->setText("Shot " + QString::number(count) +
                              ".png for GIF success saved!");
    glwidget_->grabFramebuffer().save(file_name);
    count++;
    ui_->CountGifImage->setText(QString::number(count) + " pcs");
  } else {
    ui_->labelStatus->setText("Error! Reached MAX count of GIF frames.");
  }
}

void S21View::ClearImageForGif() {
  QDir dir = dir_path_.path() + "/ForGif";
  if (dir.exists()) {
    dir.removeRecursively();
    ui_->CountGifImage->setText(QString::number(0) + " pcs");
    ui_->labelStatus->setText("All shots for GIF success removed!");
  } else {
    ui_->labelStatus->setText("Error! Path to shots for GIF is missing.");
  }
}

void S21View::CreateGif() {
  QDir dir = dir_path_.path() + "/ForGif";
  if (dir.exists()) {
    QStringList pngFiles;
    QStringList filters;
    filters << "*.png";
    dir.setNameFilters(filters);
    dir.setFilter(QDir::Files | QDir::NoDotAndDotDot);
    QFileInfoList fileList = dir.entryInfoList();
    for (const QFileInfo &fileInfo : fileList) {
      pngFiles.append(fileInfo.absoluteFilePath());
    }
    if (!(pngFiles.isEmpty())) {
      QGifImage gifImage;
      gifImage.setDefaultDelay(10);
      gifImage.setLoopCount(0);
      for (const QString &pngFile : pngFiles) {
        QImage image(pngFile);
        if (image.isNull() || image.size().isEmpty()) {
          qDebug() << "Failed to load image.png";
        } else {
          image = image.scaled(640, 480, Qt::KeepAspectRatio);
          QImage destBackground(640, 480, QImage::Format_RGB32);
          RGBColors colors;
          float r = 0, g = 0, b = 0;
          colors.GetColor(controller_->GetBackgroundColor(), r, g, b);
          destBackground.fill(QColor(r * 255, g * 255, b * 255));
          QPainter p(&destBackground);
          p.setCompositionMode(QPainter::CompositionMode_SourceAtop);
          p.drawImage((640 - image.width()) / 2, (480 - image.height()) / 2,
                      image);
          gifImage.addFrame(destBackground);
        }
      }
      gifImage.save(dir_path_.path() + "/animation.gif");
      ui_->labelStatus->setText("animation.gif success created");
    } else {
      ui_->labelStatus->setText(
          "Error! Shots in directory for GIF is missing.");
      ui_->CountGifImage->setText(QString::number(0) + " pcs");
    }
  } else {
    ui_->labelStatus->setText(
        "Error! Directory with shots for GIF is missing.");
    ui_->CountGifImage->setText(QString::number(0) + " pcs");
  }
}

void S21View::SetBuzy() {
  ui_->labelBuzy->setText("   BUZY   ");
  ui_->labelBuzy->setStyleSheet(
      "QLabel { background-color : red; color : black; }");
  ui_->labelStatus->setText("Loading...");
}

void S21View::SetReady() {
  ui_->labelBuzy->setText("  READY!  ");
  ui_->labelBuzy->setStyleSheet(
      "QLabel { background-color : green; color : black; }");
}

}  // namespace s21
