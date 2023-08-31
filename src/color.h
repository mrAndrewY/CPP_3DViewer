#ifndef CPP4_3DVIEWER_V_2_0_SRC_COLOR_H_
#define CPP4_3DVIEWER_V_2_0_SRC_COLOR_H_

#include <QComboBox>

namespace s21 {

enum Colors {
  kBlack,
  kWhite,
  kRed,
  kOrange,
  kYellow,
  kGreen,
  kCyan,
  kBlue,
  kViolet,
  kPurple,
  kLightBlue,
  kOrangeBrown,
  kBlueGreen,
  kBabyBlue,
  kLilac,
  kDarkGrey,
  kDarkPurple,
  kBronze,
  kDarkBlue,
  kForestGreen
};

class S21Color {
 public:
  virtual ~S21Color() {}
  virtual void FillColor(QComboBox* comboBox) = 0;
};

class DefaultColor : public S21Color {
 public:
  void FillColor(QComboBox* comboBox) override {
    comboBox->addItem("BLACK");
    comboBox->addItem("WHITE");
  }
};

class BackgroundColor : public S21Color {
 public:
  void FillColor(QComboBox* comboBox) override {
    comboBox->addItem("BLACK");
    comboBox->addItem("WHITE");
    comboBox->addItem("RED");
    comboBox->addItem("ORANGE");
    comboBox->addItem("YELLOW");
    comboBox->addItem("GREEN");
    comboBox->addItem("CYAN");
    comboBox->addItem("BLUE");
    comboBox->addItem("VIOLET");
  }
};

class LineAndPointColor : public S21Color {
 public:
  void FillColor(QComboBox* comboBox) override {
    comboBox->addItem("BLACK");
    comboBox->addItem("WHITE");
    comboBox->addItem("RED");
    comboBox->addItem("ORANGE");
    comboBox->addItem("YELLOW");
    comboBox->addItem("GREEN");
    comboBox->addItem("CYAN");
    comboBox->addItem("BLUE");
    comboBox->addItem("VIOLET");
    comboBox->addItem("PURPLE");
    comboBox->addItem("LIGHT_BLUE");
    comboBox->addItem("ORANGE_BROWN");
    comboBox->addItem("BLUE_GREEN");
    comboBox->addItem("BABY_BLUE");
    comboBox->addItem("LILAC");
    comboBox->addItem("DARK_GREY");
    comboBox->addItem("DARK_PURPLE");
    comboBox->addItem("BRONZE");
    comboBox->addItem("DARK_BLUE");
    comboBox->addItem("FOREST_GREEN");
  }
};

class ColorComboBox : public QComboBox {
 public:
  ColorComboBox(S21Color* color, QComboBox* comboBox)
      : color_(color), comboBox_(comboBox) {
    color_->FillColor(comboBox_);
  }

 private:
  S21Color* color_;
  QComboBox* comboBox_;
};

class RGBColors {
 public:
  void GetColor(int index, float& r, float& g, float& b) {
    switch (index) {
      case kBlack:
        r = 0.0f;
        g = 0.0f;
        b = 0.0f;
        break;
      case kWhite:
        r = 1.0f;
        g = 1.0f;
        b = 1.0f;
        break;
      case kRed:
        r = 1.0f;
        g = 0.0f;
        b = 0.0f;
        break;
      case kOrange:
        r = 1.0f;
        g = 0.5f;
        b = 0.0f;
        break;
      case kYellow:
        r = 1.0f;
        g = 1.0f;
        b = 0.0f;
        break;
      case kGreen:
        r = 0.0f;
        g = 1.0f;
        b = 0.0f;
        break;
      case kCyan:
        r = 0.0f;
        g = 1.0f;
        b = 1.0f;
        break;
      case kBlue:
        r = 0.0f;
        g = 0.0f;
        b = 1.0f;
        break;
      case kViolet:
        r = 0.6f;
        g = 0.0f;
        b = 1.0f;
        break;
      case kPurple:
        r = 1.0f;
        g = 0.0f;
        b = 1.0f;
        break;
      case kLightBlue:
        r = 0.7f;
        g = 0.8f;
        b = 0.9f;
        break;
      case kOrangeBrown:
        r = .7f;
        g = 0.4f;
        b = 0.2f;
        break;
      case kBlueGreen:
        r = 0.1f;
        g = 0.6f;
        b = 0.7f;
        break;
      case kBabyBlue:
        r = 0.5f;
        g = 0.8f;
        b = 1.0f;
        break;
      case kLilac:
        r = 0.9f;
        g = 0.8f;
        b = 1.0f;
        break;
      case kDarkGrey:
        r = 0.6f;
        g = 0.6f;
        b = 0.6f;
        break;
      case kDarkPurple:
        r = 0.2f;
        g = 0.1f;
        b = 0.5f;
        break;
      case kBronze:
        r = 0.6f;
        g = 0.5f;
        b = 0.2f;
        break;
      case kDarkBlue:
        r = 0.0f;
        g = 0.0f;
        b = 0.5f;
        break;
      case kForestGreen:
        r = 0.0f;
        g = 0.2f;
        b = 0.1f;
        break;
      default:
        r = 0.0f;
        g = 0.0f;
        b = 0.0f;
    }
  }
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V_2_0_SRC_COLOR_H_
