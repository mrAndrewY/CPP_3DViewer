#ifndef CPP4_3DVIEWER_V_2_0_SRC_COMMANDS_H
#define CPP4_3DVIEWER_V_2_0_SRC_COMMANDS_H

#include "affins.h"
#include "memento.h"

namespace s21 {

class ICommand {
 public:
  enum ICommandCommandNames {
    kMoveX,
    kMoveY,
    kMoveZ,
    kRotateX,
    kRotateY,
    kRotateZ,
    kScale,
    kXScale,
    kYScale,
    kZScale
  };
  enum ICommandCommandsQuantity { kCommandsQuantity = 10 };
  ICommand(Affins *affins);
  virtual ~ICommand();
  virtual void ExecOn(double **matrix, double step_value, int v_count) = 0;
  virtual void ExecOff(double **matrix, double step_value, int v_count) = 0;
  virtual double getActionValue() = 0;

 protected:
  Affins *aff_{nullptr};
  S21Memento *memento_{nullptr};
};

class CommandMoveX : public ICommand {
 public:
  CommandMoveX(Affins *affins) : ICommand(affins) {}
  virtual void ExecOn(double **matrix, double step_value, int v_count) override;
  virtual void ExecOff(double **matrix, double step_value,
                       int v_count) override;
  virtual double getActionValue() override;
};

class CommandMoveY : public ICommand {
 public:
  CommandMoveY(Affins *affins) : ICommand(affins) {}
  void ExecOn(double **matrix, double step_value, int v_count) override;
  virtual void ExecOff(double **matrix, double step_value,
                       int v_count) override;
  virtual double getActionValue() override;
};

class CommandMoveZ : public ICommand {
 public:
  CommandMoveZ(Affins *affins) : ICommand(affins) {}
  void ExecOn(double **matrix, double step_value, int v_count) override;
  virtual void ExecOff(double **matrix, double step_value,
                       int v_count) override;
  virtual double getActionValue() override;
};

class CommandRotateX : public ICommand {
 public:
  CommandRotateX(Affins *affins) : ICommand(affins) {}
  void ExecOn(double **matrix, double step_value, int v_count) override;
  void ExecOff(double **matrix, double step_value, int v_count) override;

 private:
  virtual double getActionValue() override;
};

class CommandRotateY : public ICommand {
 public:
  CommandRotateY(Affins *affins) : ICommand(affins) {}
  void ExecOn(double **matrix, double step_value, int v_count) override;
  void ExecOff(double **matrix, double step_value, int v_count) override;
  virtual double getActionValue() override;
};

class CommandRotateZ : public ICommand {
 public:
  CommandRotateZ(Affins *affins) : ICommand(affins) {}
  void ExecOn(double **matrix, double step_value, int v_count) override;
  void ExecOff(double **matrix, double step_value, int v_count) override;
  virtual double getActionValue() override;
};

class CommandScale : public ICommand {
 public:
  CommandScale(Affins *affins) : ICommand(affins) {}
  void ExecOn(double **matrix, double step_value, int v_count) override;
  void ExecOff(double **matrix, double step_value, int v_count) override;
  virtual double getActionValue() override;
};

class CommandXScale : public ICommand {
 public:
  CommandXScale(Affins *affins) : ICommand(affins) {}
  void ExecOn(double **matrix, double step_value, int v_count) override;
  void ExecOff(double **matrix, double step_value, int v_count) override;
  virtual double getActionValue() override;
};

class CommandYScale : public ICommand {
 public:
  CommandYScale(Affins *affins) : ICommand(affins) {}
  void ExecOn(double **matrix, double step_value, int v_count) override;
  void ExecOff(double **matrix, double step_value, int v_count) override;
  virtual double getActionValue() override;
};

class CommandZScale : public ICommand {
 public:
  CommandZScale(Affins *affins) : ICommand(affins) {}
  void ExecOn(double **matrix, double step_value, int v_count) override;
  void ExecOff(double **matrix, double step_value, int v_count) override;
  virtual double getActionValue() override;
};

}  // namespace s21

#endif  // #ifndef CPP4_3DVIEWER_V_2_0_SRC_COMMANDS_H
