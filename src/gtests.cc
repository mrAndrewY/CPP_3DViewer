#include "gtests.h"

void create_obj_file_qudro();
double **create_matrix();

TEST(Test_create_quadro, create) { create_obj_file_qudro(); }

TEST(Test_affin, MoveX) {
  s21::S21Model model;
  model.FillData("./quadro.obj");
  model.AffinCommand(s21::ICommand::ICommandCommandNames::kMoveX, 1);
  EXPECT_DOUBLE_EQ(model.GetAxisValue(0, 0, 0), 2);
  EXPECT_DOUBLE_EQ(model.GetAxisValue(0, 0, 1), 1);
  EXPECT_DOUBLE_EQ(model.GetAxisValue(0, 0, 2), -4);

  model.AffinCommandCancel();
  EXPECT_NEAR(model.GetAxisValue(0, 0, 0), 1, 1e-7);
  EXPECT_NEAR(model.GetAxisValue(0, 0, 1), 1, 1e-7);
  EXPECT_NEAR(model.GetAxisValue(0, 0, 2), -4, 1e-7);
  model.AffinCommandRollBack();
  model.AffinCommand(s21::ICommand::ICommandCommandNames::kMoveX, 1);
  model.AffinCommand(s21::ICommand::ICommandCommandNames::kMoveX, 1);
  model.AffinCommand(s21::ICommand::ICommandCommandNames::kMoveX, 1);
  model.AffinCommandRollBack();
}

TEST(Test_affin, MoveY) {
  s21::S21Model model;
  model.FillData("./quadro.obj");
  model.AffinCommand(s21::ICommand::ICommandCommandNames::kMoveY, 1);
  EXPECT_DOUBLE_EQ(model.GetAxisValue(0, 0, 0), 1);
  EXPECT_DOUBLE_EQ(model.GetAxisValue(0, 0, 1), 2);
  EXPECT_DOUBLE_EQ(model.GetAxisValue(0, 0, 2), -4);
  model.AffinCommandCancel();
  EXPECT_NEAR(model.GetAxisValue(0, 0, 0), 1, 1e-7);
  EXPECT_NEAR(model.GetAxisValue(0, 0, 1), 1, 1e-7);
  EXPECT_NEAR(model.GetAxisValue(0, 0, 2), -4, 1e-7);
}

TEST(Test_affin, MoveZ) {
  s21::S21Model model;
  model.FillData("./quadro.obj");
  model.AffinCommand(s21::ICommand::ICommandCommandNames::kMoveZ, 1);
  EXPECT_DOUBLE_EQ(model.GetAxisValue(0, 0, 0), 1);
  EXPECT_DOUBLE_EQ(model.GetAxisValue(0, 0, 1), 1);
  EXPECT_DOUBLE_EQ(model.GetAxisValue(0, 0, 2), -3);
  model.AffinCommandCancel();
  EXPECT_NEAR(model.GetAxisValue(0, 0, 0), 1, 1e-7);
  EXPECT_NEAR(model.GetAxisValue(0, 0, 1), 1, 1e-7);
  EXPECT_NEAR(model.GetAxisValue(0, 0, 2), -4, 1e-7);
}

TEST(Test_affin, RotateXobj) {
  s21::S21Model model;
  model.FillData("./quadro.obj");
  model.AffinCommand(s21::ICommand::ICommandCommandNames::kRotateX, 15);
  EXPECT_NEAR(model.GetAxisValue(0, 0, 0), 1, 1e-7);
  EXPECT_NEAR(model.GetAxisValue(0, 0, 1), 0.96592585, 1e-7);
  EXPECT_NEAR(model.GetAxisValue(0, 0, 2), -3.7411810, 1e-7);
  model.AffinCommandCancel();
  EXPECT_NEAR(model.GetAxisValue(0, 0, 0), 1, 1e-7);
  EXPECT_NEAR(model.GetAxisValue(0, 0, 1), 1, 1e-7);
  EXPECT_NEAR(model.GetAxisValue(0, 0, 2), -4, 1e-7);
  model.AffinCommandRollBack();
}

TEST(Test_affin, RotateYobj) {
  s21::S21Model model;
  model.FillData("./quadro.obj");
  model.AffinCommand(s21::ICommand::ICommandCommandNames::kRotateY, 15);
  EXPECT_NEAR(model.GetAxisValue(0, 0, 0), 0.9659258, 1e-7);
  EXPECT_NEAR(model.GetAxisValue(0, 0, 1), 1, 1e-7);
  EXPECT_NEAR(model.GetAxisValue(0, 0, 2), -4.25881895468, 1e-7);
  model.AffinCommandCancel();
  EXPECT_NEAR(model.GetAxisValue(0, 0, 0), 1, 1e-7);
  EXPECT_NEAR(model.GetAxisValue(0, 0, 1), 1, 1e-7);
  EXPECT_NEAR(model.GetAxisValue(0, 0, 2), -4, 1e-7);
  model.AffinCommandRollBack();
}

TEST(Test_affin, RotateZobj) {
  s21::S21Model model;
  model.FillData("./quadro.obj");
  model.AffinCommand(s21::ICommand::ICommandCommandNames::kRotateZ, 15);
  EXPECT_NEAR(model.GetAxisValue(0, 0, 0), 0.70710689583, 1e-7);
  EXPECT_NEAR(model.GetAxisValue(0, 0, 1), 1.22474480, 1e-7);
  EXPECT_NEAR(model.GetAxisValue(0, 0, 2), -4, 1e-7);
  model.AffinCommandCancel();
  EXPECT_NEAR(model.GetAxisValue(0, 0, 0), 1, 1e-7);
  EXPECT_NEAR(model.GetAxisValue(0, 0, 1), 1, 1e-7);
  EXPECT_NEAR(model.GetAxisValue(0, 0, 2), -4, 1e-7);
  model.AffinCommandRollBack();
}

TEST(Test_affin, Scale) {
  s21::S21Model model;
  model.FillData("./quadro.obj");
  model.AffinCommand(s21::ICommand::ICommandCommandNames::kScale, 0.5);
  EXPECT_NEAR(model.GetAxisValue(0, 0, 0), 0.5, 1e-7);
  EXPECT_NEAR(model.GetAxisValue(0, 0, 1), 0.5, 1e-7);
  EXPECT_NEAR(model.GetAxisValue(0, 0, 2), -4, 1e-7);
  model.AffinCommandCancel();
  EXPECT_NEAR(model.GetAxisValue(0, 0, 0), 1, 1e-7);
  EXPECT_NEAR(model.GetAxisValue(0, 0, 1), 1, 1e-7);
  EXPECT_NEAR(model.GetAxisValue(0, 0, 2), -4, 1e-7);
  model.AffinCommand(s21::ICommand::ICommandCommandNames::kScale, 0.000001);
}

TEST(Test_affin, ScaleX) {
  s21::S21Model model;
  model.FillData("./quadro.obj");
  model.AffinCommand(s21::ICommand::ICommandCommandNames::kXScale, 0.5);
  EXPECT_NEAR(model.GetAxisValue(0, 0, 0), 0.5, 1e-7);
  EXPECT_NEAR(model.GetAxisValue(0, 0, 1), 1, 1e-7);
  EXPECT_NEAR(model.GetAxisValue(0, 0, 2), -4, 1e-7);
  model.AffinCommandCancel();
  EXPECT_NEAR(model.GetAxisValue(0, 0, 0), 1, 1e-7);
  EXPECT_NEAR(model.GetAxisValue(0, 0, 1), 1, 1e-7);
  EXPECT_NEAR(model.GetAxisValue(0, 0, 2), -4, 1e-7);
}

TEST(Test_affin, ScaleY) {
  s21::S21Model model;
  model.FillData("./quadro.obj");
  model.AffinCommand(s21::ICommand::ICommandCommandNames::kYScale, 0.5);
  EXPECT_NEAR(model.GetAxisValue(0, 0, 0), 1, 1e-7);
  EXPECT_NEAR(model.GetAxisValue(0, 0, 1), 0.5, 1e-7);
  EXPECT_NEAR(model.GetAxisValue(0, 0, 2), -4, 1e-7);
  model.AffinCommandCancel();
  EXPECT_NEAR(model.GetAxisValue(0, 0, 0), 1, 1e-7);
  EXPECT_NEAR(model.GetAxisValue(0, 0, 1), 1, 1e-7);
  EXPECT_NEAR(model.GetAxisValue(0, 0, 2), -4, 1e-7);
}

TEST(Test_affin, ScaleZ) {
  s21::S21Model model;
  model.FillData("./quadro.obj");
  model.AffinCommand(s21::ICommand::ICommandCommandNames::kZScale, 0.2);
  EXPECT_NEAR(model.GetAxisValue(0, 0, 0), 1, 1e-7);
  EXPECT_NEAR(model.GetAxisValue(0, 0, 1), 1, 1e-7);
  EXPECT_NEAR(model.GetAxisValue(0, 0, 2), -4, 1e-7);
  model.AffinCommandCancel();
  EXPECT_NEAR(model.GetAxisValue(0, 0, 0), 1, 1e-7);
  EXPECT_NEAR(model.GetAxisValue(0, 0, 1), 1, 1e-7);
  EXPECT_NEAR(model.GetAxisValue(0, 0, 2), -4, 1e-7);
}

TEST(Test_affin, Alighn_to_center) {
  s21::Affins affins;
  double **test_matrix = create_matrix();
  affins.MoveX(test_matrix, 1, 8);
  affins.MoveY(test_matrix, 1, 8);
  affins.MoveZ(test_matrix, 1, 8);
  affins.AlignObjectToCenter(test_matrix, 8);
  EXPECT_NEAR(test_matrix[1][0], 1, 1e-7);
  EXPECT_NEAR(test_matrix[1][1], 1, 1e-7);
  EXPECT_NEAR(test_matrix[1][2], 1, 1e-7);
  EXPECT_NEAR(test_matrix[2][0], -1, 1e-7);
  EXPECT_NEAR(test_matrix[2][1], 1, 1e-7);
  EXPECT_NEAR(test_matrix[2][2], 1, 1e-7);
  EXPECT_NEAR(test_matrix[3][0], -1, 1e-7);
  EXPECT_NEAR(test_matrix[3][1], -1, 1e-7);
  EXPECT_NEAR(test_matrix[3][2], 1, 1e-7);
  EXPECT_NEAR(test_matrix[4][0], 1, 1e-7);
  EXPECT_NEAR(test_matrix[4][1], -1, 1e-7);
  EXPECT_NEAR(test_matrix[4][2], 1, 1e-7);
  EXPECT_NEAR(test_matrix[5][0], 1, 1e-7);
  EXPECT_NEAR(test_matrix[5][1], 1, 1e-7);
  EXPECT_NEAR(test_matrix[5][2], -1, 1e-7);
  EXPECT_NEAR(test_matrix[6][0], -1, 1e-7);
  EXPECT_NEAR(test_matrix[6][1], 1, 1e-7);
  EXPECT_NEAR(test_matrix[6][2], -1, 1e-7);
  EXPECT_NEAR(test_matrix[7][0], 1, 1e-7);
  EXPECT_NEAR(test_matrix[7][1], -1, 1e-7);
  EXPECT_NEAR(test_matrix[7][2], -1, 1e-7);
  EXPECT_NEAR(test_matrix[8][0], -1, 1e-7);
  EXPECT_NEAR(test_matrix[8][1], -1, 1e-7);
  EXPECT_NEAR(test_matrix[8][2], -1, 1e-7);
  delete[] test_matrix[0];
  delete[] test_matrix;
}

TEST(Test_affin, Get_min_max) {
  s21::Affins affins;
  double **test_matrix = create_matrix();
  affins.MoveX(test_matrix, 1, 8);
  affins.MoveY(test_matrix, 1, 8);
  affins.MoveZ(test_matrix, 1, 8);
  affins.AlignObjectToCenter(test_matrix, 8);
  double min_x = 0;
  double min_y = 0;
  double min_z = 0;
  double max_x = 0;
  double max_y = 0;
  double max_z = 0;
  affins.GetMinMax(min_x, min_y, min_z, max_x, max_y, max_z, test_matrix, 8);
  affins.AlignObjectToCenter(test_matrix, 8);
  EXPECT_NEAR(min_x, -1, 1e-7);
  EXPECT_NEAR(min_y, -1, 1e-7);
  EXPECT_NEAR(min_z, -1, 1e-7);
  EXPECT_NEAR(max_x, 1, 1e-7);
  EXPECT_NEAR(max_y, 1, 1e-7);
  EXPECT_NEAR(max_z, 1, 1e-7);
  affins.GetMinMax(min_x, min_y, min_z, max_x, max_y, max_z, test_matrix, 8);
  affins.AlignObjectToCenter(test_matrix, 8);
  test_matrix[2][0] += 5;
  test_matrix[2][1] += 5;
  test_matrix[2][2] += 5;
  affins.GetMinMax(min_x, min_y, min_z, max_x, max_y, max_z, test_matrix, 8);
  test_matrix[2][0] -= 5;
  test_matrix[2][1] -= 5;
  test_matrix[2][2] -= 5;
  affins.GetMinMax(min_x, min_y, min_z, max_x, max_y, max_z, test_matrix, 8);
  EXPECT_NEAR(min_x, -1, 1e-7);
  EXPECT_NEAR(min_y, -1, 1e-7);
  EXPECT_NEAR(min_z, -1, 1e-7);
  EXPECT_NEAR(max_x, 1, 1e-7);
  EXPECT_NEAR(max_y, 1, 1e-7);
  EXPECT_NEAR(max_z, 1, 1e-7);
  delete[] test_matrix[0];
  delete[] test_matrix;
}

TEST(Test_affin, Set_vert_position) {
  s21::Affins affins;
  double **test_matrix = create_matrix();
  double min_x = 0;
  double min_y = 0;
  double min_z = 0;
  double max_x = 0;
  double max_y = 0;
  double max_z = 0;
  test_matrix[2][0] += 0;
  test_matrix[2][1] += 5;
  test_matrix[2][2] += 19;
  affins.SetVertPosition(min_x, min_y, min_z, max_x, max_y, max_z, 8,
                         test_matrix);
  delete[] test_matrix[0];
  delete[] test_matrix;
}

TEST(MODEL, test_001) {
  s21::S21Model m;
  std::string file_name = "samples_obj/привет.obj";
  int err = m.FillData(file_name);
  EXPECT_EQ(err, 0);
  EXPECT_EQ(m.GetCountVectices(), 10);
  EXPECT_EQ(m.GetCountPoligons(), 12);
  EXPECT_EQ(m.GetSizePoligons(3), 4);
  EXPECT_NEAR(m.GetAxisValue(8, 2, 0), -1.5, 1E-6);
  EXPECT_NEAR(m.GetAxisValue(8, 2, 1), 0, 1E-6);
  EXPECT_NEAR(m.GetAxisValue(8, 2, 2), -6, 1E-6);
}

TEST(MODEL, test_002) {
  s21::S21Model m;
  std::string file_name = "samples_obj/привет.obj";
  m.FillData(file_name);
  file_name = "samples_obj/square_int.obj";
  int err = m.FillData(file_name);
  EXPECT_EQ(err, 0);
  EXPECT_EQ(m.GetCountVectices(), 4);
  EXPECT_EQ(m.GetCountPoligons(), 2);
  EXPECT_EQ(m.GetSizePoligons(0), 3);
  EXPECT_NEAR(m.GetAxisValue(1, 1, 0), 1, 1E-6);
  EXPECT_NEAR(m.GetAxisValue(1, 1, 1), 1, 1E-6);
  EXPECT_NEAR(m.GetAxisValue(1, 1, 2), -4, 1E-6);
}

TEST(MODEL, test_003) {
  s21::S21Model m;
  std::string file_name = "samples_obj/Empty.obj";
  int err = m.FillData(file_name);
  EXPECT_EQ(err, 6);
  EXPECT_EQ(m.GetCountVectices(), 0);
  EXPECT_EQ(m.GetCountPoligons(), 0);
}

TEST(MODEL, test_004) {
  s21::S21Model m;
  std::string file_name = "samples_obj/123.obj";
  int err = m.FillData("samples_obj/111.obj");
  EXPECT_EQ(err, 1);
  EXPECT_EQ(m.GetCountVectices(), 0);
  EXPECT_EQ(m.GetCountPoligons(), 0);
  std::ofstream file(file_name);
  file.close();
  err = m.FillData(file_name);
  EXPECT_EQ(err, 2);
  EXPECT_EQ(m.GetCountVectices(), 0);
  EXPECT_EQ(m.GetCountPoligons(), 0);
  std::remove("samples_obj/123.obj");
}

TEST(MODEL, test_005) {
  s21::S21Model m;
  std::string file_name = "samples_obj/123.obj";
  std::ofstream file(file_name);
  file << "f 1 2 4\n";
  file.close();
  int err = m.FillData(file_name);
  EXPECT_EQ(err, 5);
  EXPECT_EQ(m.GetCountVectices(), 0);
  EXPECT_EQ(m.GetCountPoligons(), 0);
  std::remove("samples_obj/123.obj");
}

TEST(MODEL, test_006) {
  s21::S21Model m;
  std::string file_name = "samples_obj/123.obj";
  std::ofstream file(file_name);
  file << "v 1 1\n";
  file.close();
  int err = m.FillData(file_name);
  EXPECT_EQ(err, 5);
  EXPECT_EQ(m.GetCountVectices(), 0);
  EXPECT_EQ(m.GetCountPoligons(), 0);
  std::remove("samples_obj/123.obj");
}

TEST(MODEL, test_007) {
  s21::S21Model m;
  std::string file_name = "samples_obj/pyramid.obj";
  int err = m.FillData(file_name);
  EXPECT_EQ(err, 0);
  EXPECT_EQ(m.GetCountVectices(), 5);
  EXPECT_EQ(m.GetCountPoligons(), 6);
}

TEST(MODEL, test_008) {
  s21::S21Model m;
  std::string file_name = "samples_obj/skull.obj";
  int err = m.FillData(file_name);
  EXPECT_EQ(err, 0);
  EXPECT_EQ(m.GetCountVectices(), 6122);
  EXPECT_EQ(m.GetCountPoligons(), 9537);
}

TEST(MODEL, test_009) {
  s21::S21Model m;
  std::string file_name = "samples_obj/123.obj";
  std::ofstream file(file_name);
  file << "v 1 1 1\n"
       << "f 1 1 FF 1\n";
  file.close();
  int err = m.FillData(file_name);
  EXPECT_EQ(err, 6);
  EXPECT_EQ(m.GetCountVectices(), 0);
  EXPECT_EQ(m.GetCountPoligons(), 0);
  std::remove("samples_obj/123.obj");
  std::remove("quadro.obj");
}

void create_obj_file_qudro() {
  std::ofstream file("quadro.obj");
  file << "v 1 1 0\n"
       << "v -1 1 0\n"
       << "v 1 -1 0\n"
       << "v -1 -1 0\n"
       << "f 1 2 4 3 1\n";
}

double **create_matrix() {
  int rows = 9;
  int cols = 3;
  double **matrix = new double *[rows];
  matrix[0] = new double[rows * cols]();
  for (int i = 0; i < rows; i++) {
    matrix[i] = matrix[0] + i * cols;
  }
  matrix[0][0] = 0;
  matrix[0][1] = 0;
  matrix[0][2] = 0;
  matrix[1][0] = 1;
  matrix[1][1] = 1;
  matrix[1][2] = 1;
  matrix[2][0] = -1;
  matrix[2][1] = 1;
  matrix[2][2] = 1;
  matrix[3][0] = -1;
  matrix[3][1] = -1;
  matrix[3][2] = 1;
  matrix[4][0] = 1;
  matrix[4][1] = -1;
  matrix[4][2] = 1;
  matrix[5][0] = 1;
  matrix[5][1] = 1;
  matrix[5][2] = -1;
  matrix[6][0] = -1;
  matrix[6][1] = 1;
  matrix[6][2] = -1;
  matrix[7][0] = 1;
  matrix[7][1] = -1;
  matrix[7][2] = -1;
  matrix[8][0] = -1;
  matrix[8][1] = -1;
  matrix[8][2] = -1;
  return matrix;
}
