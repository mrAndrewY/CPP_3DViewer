#ifndef CPP4_3DVIEWER_V_2_0_SRC_MULTIPULT_H
#define CPP4_3DVIEWER_V_2_0_SRC_MULTIPULT_H

#include <stack>
#include <vector>

#include "commands.h"

namespace s21 {

struct CommandStackNode {
  ICommand *command;
  double parameter = 0;
};

class Multipult {
 public:
  Multipult(Affins *affins, double **matrix, int v_count);
  void PressOnCommand(int command_i, double value);
  void PressCanselCommand();
  void PressRollBackCommand();
  ~Multipult();
  enum MultipultBundle { kBundleCommands = 3 };

 private:
  void SetCommands(Affins *affins);

  std::stack<CommandStackNode *> history_;
  std::vector<ICommand *> commands_;
  double **matrix_;
  int v_count_;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V_2_0_SRC_MULTIPULT_H
