#include "settings.h"

namespace s21 {

void S21Settings::SetupSettingsFunction(std::string name_file) {
  if (ReadSettingsFromFile(name_file)) {
    settings_.point_view_ = 1;
    settings_.point_shape_ = 0;
    settings_.point_size_ = 1;
    settings_.point_color_ = 1;
    settings_.line_view_ = 1;
    settings_.line_stipple_ = 0;
    settings_.line_thickness_ = 1;
    settings_.lines_color_ = 1;
    settings_.background_color_ = 0;
    settings_.isometric_ = 0;
  }
}

void S21Settings::SaveSettingsFunction(std::string name_file) {
  std::ofstream file;
  file.open(name_file);
  if (file.is_open()) {
    file << settings_.point_view_ << " " << settings_.point_shape_ << " "
         << settings_.point_size_ << " " << settings_.point_color_ << " "
         << settings_.line_view_ << " " << settings_.line_stipple_ << " "
         << settings_.line_thickness_ << " " << settings_.lines_color_ << " "
         << settings_.background_color_ << " " << settings_.isometric_ << "\n";
  }
  file.close();
}

int S21Settings::ReadSettingsFromFile(std::string name_file) {
  int err = err_ok;
  std::ifstream file;
  file.open(name_file);
  if (!file.is_open()) {
    err = err_file_open;
  } else {
    std::string line;
    std::getline(file, line);
    if (line.empty()) {
      err = err_file_empty;
    } else {
      size_t shift = 0, pos = 0;
      try {
        settings_.point_view_ = std::stoi(line.substr(pos), &shift);
        pos += shift + 1;
        settings_.point_shape_ = std::stoi(line.substr(pos), &shift);
        pos += shift + 1;
        settings_.point_size_ = std::stoi(line.substr(pos), &shift);
        pos += shift + 1;
        settings_.point_color_ = std::stoi(line.substr(pos), &shift);
        pos += shift + 1;
        settings_.line_view_ = std::stoi(line.substr(pos), &shift);
        pos += shift + 1;
        settings_.line_stipple_ = std::stoi(line.substr(pos), &shift);
        pos += shift + 1;
        settings_.line_thickness_ = std::stoi(line.substr(pos), &shift);
        pos += shift + 1;
        settings_.lines_color_ = std::stoi(line.substr(pos), &shift);
        pos += shift + 1;
        settings_.background_color_ = std::stoi(line.substr(pos), &shift);
        pos += shift + 1;
        settings_.isometric_ = std::stoi(line.substr(pos), &shift);
      } catch (...) {
        err = err_file_fault;
      }
    }
  }
  file.close();
  return err;
}

int S21Settings::GetViewingPoints() { return settings_.point_view_; }

int S21Settings::GetPointShape() { return settings_.point_shape_; }

int S21Settings::GetPointSize() { return settings_.point_size_; }

int S21Settings::GetColorPoints() { return settings_.point_color_; }

int S21Settings::GetViewingLine() { return settings_.line_view_; }

int S21Settings::GetLineStipple() { return settings_.line_stipple_; }

int S21Settings::GetLineThickness() { return settings_.line_thickness_; }

int S21Settings::GetColorLines() { return settings_.lines_color_; }

int S21Settings::GetBackgroundColor() { return settings_.background_color_; }

int S21Settings::GetIsometric() { return settings_.isometric_; }

void S21Settings::SetViewingPoints(int value) { settings_.point_view_ = value; }

void S21Settings::SetPointShape(int value) { settings_.point_shape_ = value; }

void S21Settings::SetPointSize(int value) { settings_.point_size_ = value; }

void S21Settings::SetColorPoints(int value) { settings_.point_color_ = value; }

void S21Settings::SetViewingLine(int value) { settings_.line_view_ = value; }

void S21Settings::SetLineStipple(int value) { settings_.line_stipple_ = value; }

void S21Settings::SetLineThickness(int value) {
  settings_.line_thickness_ = value;
}

void S21Settings::SetColorLines(int value) { settings_.lines_color_ = value; }

void S21Settings::SetBackgroundColor(int value) {
  settings_.background_color_ = value;
}

void S21Settings::SetIsometric(int value) { settings_.isometric_ = value; }

}  // namespace s21
