#pragma once

#include "irtree/base_elements.hpp"
#include "jouette/visitors/PrintVisitor.hpp"


namespace IRT {

class Block: public std::enable_shared_from_this<Block> {
 public:
  Block() = default;
  Block(std::shared_ptr<IRT::SeqStatement> label, 
      std::shared_ptr<IRT::SeqStatement> jump);

  std::string GetLabelName() const;
  std::shared_ptr<IRT::SeqStatement> GetLabelSeq() const;
  std::shared_ptr<IRT::SeqStatement> GetJumpSeq() const;

  void AddPrev(std::shared_ptr<Block> prev);
  void AddNext(std::shared_ptr<Block> next);
  std::vector<std::shared_ptr<Block>> GetPrev() const;
  std::vector<std::shared_ptr<Block>> GetNext() const;

  void PrintBlock(const std::string&, bool is_main = false) const;

  std::shared_ptr<Jouette::PrintVisitor> GetPrinter(const std::string&) const;
 
 private:
  std::shared_ptr<IRT::SeqStatement> label_;
  std::shared_ptr<IRT::SeqStatement> jump_;

  std::vector<std::shared_ptr<Block>> prev_;
  std::vector<std::shared_ptr<Block>> next_;
};

}
