#include "view.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::S21Model model;
  s21::S21Settings setting;
  s21::S21Controller controller(&model, &setting);
  s21::S21View view(&controller);
  view.show();
  return a.exec();
}
