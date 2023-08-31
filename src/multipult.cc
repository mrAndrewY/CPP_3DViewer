#include "multipult.h"

namespace s21 {

Multipult::Multipult(Affins *affins, double **matrix, int v_count) {
  commands_.resize(ICommand::kCommandsQuantity);
  matrix_ = matrix;
  v_count_ = v_count;
  SetCommands(affins);
}

void Multipult::PressOnCommand(int command_i, double value) {
  commands_[command_i]->ExecOn(matrix_, value, v_count_);
  CommandStackNode *node = new CommandStackNode;
  node->command = commands_[command_i];
  node->parameter = value;
  history_.push(node);
}

void Multipult::PressCanselCommand() {
  CommandStackNode *node = nullptr;
  if (!history_.empty()) {
    int iter = kBundleCommands;
    while (!history_.empty() && iter) {
      node = history_.top();
      node->command->ExecOff(matrix_, node->parameter, v_count_);
      delete node;
      history_.pop();
      iter--;
    }
  }
}

void Multipult::PressRollBackCommand() {
  CommandStackNode *node_rollback = new CommandStackNode;
  for (auto it = commands_.begin(); it < commands_.end(); ++it) {
    if ((*it != commands_[ICommand::kRotateX]) &&
        (*it != commands_[ICommand::kRotateY]) &&
        (*it != commands_[ICommand::kRotateZ])) {
      node_rollback->command = *it;
      node_rollback->command->ExecOff(
          matrix_, node_rollback->command->getActionValue(), v_count_);
    }
  }
  delete node_rollback;
  node_rollback = nullptr;
  while (!history_.empty()) {
    int iter = kBundleCommands;
    while ((!history_.empty()) && (iter)) {
      node_rollback = history_.top();
      if ((node_rollback->command == commands_[ICommand::kRotateX]) ||
          (node_rollback->command == commands_[ICommand::kRotateY]) ||
          (node_rollback->command == commands_[ICommand::kRotateZ])) {
        node_rollback->command->ExecOff(matrix_, node_rollback->parameter,
                                        v_count_);
      }
      delete node_rollback;
      history_.pop();
      iter--;
    }
  }
}

Multipult::~Multipult() {
  while (!history_.empty()) {
    CommandStackNode *node = history_.top();
    delete node;
    node = nullptr;
    history_.pop();
  }
  for (auto it = commands_.begin(); it != commands_.end(); ++it) {
    delete (*it);
    *it = nullptr;
  }
}

void Multipult::SetCommands(Affins *affins) {
  commands_[ICommand::kMoveX] = new CommandMoveX(affins);
  commands_[ICommand::kMoveY] = new CommandMoveY(affins);
  commands_[ICommand::kMoveZ] = new CommandMoveZ(affins);
  commands_[ICommand::kRotateX] = new CommandRotateX(affins);
  commands_[ICommand::kRotateY] = new CommandRotateY(affins);
  commands_[ICommand::kRotateZ] = new CommandRotateZ(affins);
  commands_[ICommand::kXScale] = new CommandXScale(affins);
  commands_[ICommand::kYScale] = new CommandYScale(affins);
  commands_[ICommand::kZScale] = new CommandZScale(affins);
  commands_[ICommand::kScale] = new CommandScale(affins);
}

}  // namespace s21
