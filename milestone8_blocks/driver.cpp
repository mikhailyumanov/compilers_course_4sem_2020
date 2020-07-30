#include "driver.hh"
#include "parser.hh"

#if DEBUG_ON
std::ofstream debug_output_stream;
#endif

Driver::Driver() :
    trace_parsing(false),
    trace_scanning(false),
    trace_tree_building(false),
    scanner(*this), parser(scanner, *this) {
}


int Driver::parse(const std::string& f) {
    file = f;
    location.initialize(&file);
    scan_begin();
    parser.set_debug_level(trace_parsing);
    int res = parser();
    scan_end();

#if DEBUG_ON
debug_output_stream = std::ofstream(tree_output + "_debug.txt");
#endif
  
//    PrintTree(tree_output);
//    Eval();
/*
    try {
      BuildSymbolTree(tree_output);
    } catch (std::runtime_error err) {
      std::cout << err.what() << std::endl;
    }
*/

//    PrintIrtree(tree_output);

    PrintBlockTree(tree_output);

    return res;
}

void Driver::scan_begin() {
    scanner.set_debug(trace_scanning);
  if (file.empty () || file == "-") {
  } else {
    stream.open(file);
    std::cout << file << std::endl;
    scanner.yyrestart(&stream);
  }
}

void Driver::scan_end()
{
    stream.close();
}

void Driver::BuildSymbolTree(const std::string& filename = "") const {
  std::shared_ptr<SymbolTreeVisitor> visitor;

  if (filename != "") {
    visitor = std::make_shared<SymbolTreeVisitor>(filename);
  } else {
    visitor = std::make_shared<SymbolTreeVisitor>();
  }

  program->Accept(visitor);

  /*
  std::cout << "TEST ITERATOR" << std::endl;
  std::shared_ptr<ScopeLayerTree> tree = visitor->GetTree();

  for (auto it = tree->begin(); it != tree->end(); ++it) {
    std::cout 
      << it.current_parent_ << " " 
      << it.current_parent_->GetChild(it.current_child_index_) << " "
      << it.current_child_index_ << std::endl;

    for (auto symbol_value : it->GetVars()) {
      std::cout << symbol_value.first.GetName() << " " 
                << symbol_value.second->GetType().type << std::endl;
    }
    std::cout << std::endl;
  }
  std::cout << "TEST FINISHED" << std::endl;
  */
}

void Driver::PrintTree(const std::string& filename) const {
  auto visitor = std::make_shared<PrintVisitor>(filename);
  program->Accept(visitor);
}

int Driver::Eval() const {
  std::shared_ptr<Interpreter> visitor;
  if (!trace_tree_building) {
    visitor = std::make_shared<Interpreter>();
  } else {
    visitor = std::make_shared<Interpreter>(tree_output);
  }

  return visitor->GetResult(program);
  return 0;
}

void Driver::PrintIrtree(const std::string& filename) const {
  auto irtree_build_visitor = std::make_shared<IrtreeBuildVisitor>(filename);
  irtree_build_visitor->Visit(program);
  IrtMapping methods = irtree_build_visitor->GetTrees();

  auto print_visitor = std::make_shared<IRT::PrintVisitor>(
      filename + "_irtree.txt");

  for (auto& pair : methods) {
    DEBUG_SINGLE(pair.first)
    pair.second = std::make_shared<IRT::DoubleCallEliminationVisitor>()->Accept(pair.second).stmt;
    pair.second = std::make_shared<IRT::EseqEliminationVisitor>()->Accept(pair.second).stmt;
    pair.second = std::make_shared<IRT::LinearizeVisitor>()->Accept(pair.second).stmt;
    pair.second->Accept(print_visitor);
  }
}

void Driver::PrintBlockTree(const std::string& filename) const {
  auto irtree_build_visitor = std::make_shared<IrtreeBuildVisitor>(filename);
  irtree_build_visitor->Visit(program);
  IrtMapping methods = irtree_build_visitor->GetTrees();
  
  std::string output = filename + "_irtree.txt";
  for (auto& pair : methods) {
    auto block_tree = std::make_shared<IRT::BlockTree>(pair.second);
    block_tree->PrintTree(output);
  }
}

