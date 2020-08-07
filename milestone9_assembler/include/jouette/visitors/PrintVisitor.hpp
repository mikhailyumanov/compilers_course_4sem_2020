#pragma once

#include <string>
#include <fstream>

#include "jouette/elements.hpp"
#include "jouette/visitors/Visitor.hpp"


namespace Jouette {

class PrintVisitor: public Visitor,
 public std::enable_shared_from_this<PrintVisitor> {

 public:
  explicit PrintVisitor(const std::string& filename);
  ~PrintVisitor() override;

  void Visit(std::shared_ptr<Add> element) override;
  void Visit(std::shared_ptr<Sub> element) override;
  void Visit(std::shared_ptr<Mul> element) override;
  void Visit(std::shared_ptr<Div> element) override;

  void Visit(std::shared_ptr<Addi> element) override;
  void Visit(std::shared_ptr<Subi> element) override;

  void Visit(std::shared_ptr<Movea> element) override;
  void Visit(std::shared_ptr<Moved> element) override;

  void Visit(std::shared_ptr<Load> element) override;
  void Visit(std::shared_ptr<Store> element) override;
  void Visit(std::shared_ptr<Movem> element) override;

  void Visit(std::shared_ptr<Call> element) override;
  void Visit(std::shared_ptr<Return> element) override;

  void Visit(std::shared_ptr<Bge> element) override;
  void Visit(std::shared_ptr<Blt> element) override;
  void Visit(std::shared_ptr<Beq> element) override;
  void Visit(std::shared_ptr<Bne> element) override;
  void Visit(std::shared_ptr<Jump> element) override;

  void Visit(std::shared_ptr<Label> element) override;

 private:
  std::ofstream stream_;

  void PrintTab();
};

}

