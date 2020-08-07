#include "jouette/visitors/PrintVisitor.hpp"


namespace Jouette {

PrintVisitor::PrintVisitor(const std::string& filename): stream_(filename) {
}

void PrintVisitor::Visit(std::shared_ptr<Add> element) {
  DEBUG_SINGLE("PrintVisitor::Add start")
  PrintTab();
  stream_ << "add\t\t["
          << *element->output << "], "
          << *element->lhs << ", "
          << *element->rhs << std::endl;

  DEBUG_SINGLE("PrintVisitor::Add")
}

void PrintVisitor::Visit(std::shared_ptr<Sub> element) {
  DEBUG_SINGLE("PrintVisitor::Sub start")
  PrintTab();
  stream_ << "sub\t\t["
          << *element->output << "], "
          << *element->lhs << ", "
          << *element->rhs << std::endl;

  DEBUG_SINGLE("PrintVisitor::Sub")
}

void PrintVisitor::Visit(std::shared_ptr<Mul> element) {
  DEBUG_SINGLE("PrintVisitor::Mul start")
  PrintTab();
  stream_ << "mul\t\t["
          << *element->output << "], "
          << *element->lhs << ", "
          << *element->rhs << std::endl;

  DEBUG_SINGLE("PrintVisitor::Mul")
}

void PrintVisitor::Visit(std::shared_ptr<Div> element) {
  DEBUG_SINGLE("PrintVisitor::Div start")
  PrintTab();
  stream_ << "div\t\t["
          << *element->output << "], "
          << *element->lhs << ", "
          << *element->rhs << std::endl;

  DEBUG_SINGLE("PrintVisitor::Div")
}

void PrintVisitor::Visit(std::shared_ptr<Addi> element) {
  DEBUG_SINGLE("PrintVisitor::Addi start")
  PrintTab();
  stream_ << "addi\t\t["
          << *element->output << "], "
          << *element->input << ", " 
          <<  element->cnst << std::endl;

  DEBUG_SINGLE("PrintVisitor::Addi")
}

void PrintVisitor::Visit(std::shared_ptr<Subi> element) {
  DEBUG_SINGLE("PrintVisitor::Subi start")
  PrintTab();
  stream_ << "subi\t\t["
          << *element->output << "], "
          << *element->input << ", "
          <<  element->cnst << std::endl;

  DEBUG_SINGLE("PrintVisitor::Subi")
}

void PrintVisitor::Visit(std::shared_ptr<Movea> element) {
  DEBUG_SINGLE("PrintVisitor::Movea start")
  PrintTab();
  stream_ << "movea\t\t["
          << *element->output << "], "
          << *element->input << std::endl;

  DEBUG_SINGLE("PrintVisitor::Movea")
}

void PrintVisitor::Visit(std::shared_ptr<Moved> element) {
  DEBUG_SINGLE("PrintVisitor::Moved start")
  PrintTab();
  stream_ << "moved\t\t["
          << *element->output << "], "
          << *element->input << std::endl;

  DEBUG_SINGLE("PrintVisitor::Moved")
}

void PrintVisitor::Visit(std::shared_ptr<Load> element) {
  DEBUG_SINGLE("PrintVisitor::Load start")
  PrintTab();
  stream_ << "load\t\t["
          << *element->output << "], "
          << *element->input << ", "
          << element->cnst << std::endl;

  DEBUG_SINGLE("PrintVisitor::Load")
}

void PrintVisitor::Visit(std::shared_ptr<Store> element) {
  DEBUG_SINGLE("PrintVisitor::Store start")
  PrintTab();
  stream_ << "store\t\t"
          << *element->output << ", "
          << element->cnst << ", "
          << *element->input << std::endl;

  DEBUG_SINGLE("PrintVisitor::Store")
}

void PrintVisitor::Visit(std::shared_ptr<Movem> element) {
  DEBUG_SINGLE("PrintVisitor::Movem start")
  PrintTab();
  stream_ << "movem\t\t["
          << *element->output << "], "
          << *element->input << " " << std::endl;

  DEBUG_SINGLE("PrintVisitor::Movem")
}

void PrintVisitor::Visit(std::shared_ptr<Call> element) {
  DEBUG_SINGLE("PrintVisitor::Call start")
  PrintTab();
  stream_ << "call\t\t["
          << *element->output << "], "
          <<  element->label;
  for (auto&& arg : element->args) {
    stream_ << ", " << *arg;
  }
  stream_ << std::endl;

  DEBUG_SINGLE("PrintVisitor::Call")
}

void PrintVisitor::Visit(std::shared_ptr<Return> element) {
  DEBUG_SINGLE("PrintVisitor::Return start")
  PrintTab();
  stream_ << "return" << std::endl;

  DEBUG_SINGLE("PrintVisitor::Return")
}

void PrintVisitor::Visit(std::shared_ptr<Bge> element) {
  DEBUG_SINGLE("PrintVisitor::Bge start")
  PrintTab();
  stream_ << "bge\t\t"
          <<  element->label << ", "
          << *element->input << std::endl;

  DEBUG_SINGLE("PrintVisitor::Bge")
}

void PrintVisitor::Visit(std::shared_ptr<Blt> element) {
  DEBUG_SINGLE("PrintVisitor::Blt start")
  PrintTab();
  stream_ << "blt\t\t"
          <<  element->label << ", "
          << *element->input << std::endl;

  DEBUG_SINGLE("PrintVisitor::Blt")
}

void PrintVisitor::Visit(std::shared_ptr<Beq> element) {
  DEBUG_SINGLE("PrintVisitor::Beq start")
  PrintTab();
  stream_ << "beq\t\t"
          <<  element->label << ", "
          << *element->input << std::endl;

  DEBUG_SINGLE("PrintVisitor::Beq")
}

void PrintVisitor::Visit(std::shared_ptr<Bne> element) {
  DEBUG_SINGLE("PrintVisitor::Bne start")
  PrintTab();
  stream_ << "bne\t\t"
          <<  element->label << ", "
          << *element->input << std::endl;

  DEBUG_SINGLE("PrintVisitor::Bne")
}

void PrintVisitor::Visit(std::shared_ptr<Jump> element) {
  DEBUG_SINGLE("PrintVisitor::Jump start")
  PrintTab();
  stream_ << "jump\t\t"
          <<  element->label << std::endl;

  DEBUG_SINGLE("PrintVisitor::Jump")
}

void PrintVisitor::Visit(std::shared_ptr<Label> element) {
  DEBUG_SINGLE("PrintVisitor::Label (start)")
  stream_ << std::endl << *element << ":" << std::endl;

  DEBUG_SINGLE("PrintVisitor::Label")
}


void PrintVisitor::PrintTab() {
  stream_ << '\t';
}

PrintVisitor::~PrintVisitor() {
  stream_.close();
}

}
