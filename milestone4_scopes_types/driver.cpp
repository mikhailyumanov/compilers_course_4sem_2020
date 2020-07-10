#include "driver.hh"
#include "parser.hh"


Driver::Driver() :
    trace_parsing(false),
    trace_scanning(false),
    scanner(*this), parser(scanner, *this) {
}


int Driver::parse(const std::string& f) {
    file = f;
    location.initialize(&file);
    scan_begin();
    parser.set_debug_level(trace_parsing);
    int res = parser();
    scan_end();
  
//    PrintTree("./printed_tree");
    Eval();
/*
    try {
      BuildSymbolTree("./symbol_tree");
    } catch (std::runtime_error err) {
      std::cout << err.what() << std::endl;
    }
*/

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
  auto visitor = std::make_shared<Interpreter>("../bin/test5_tree");
  return visitor->GetResult(program);
  return 0;
}
