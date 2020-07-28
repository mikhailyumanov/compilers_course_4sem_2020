#include "types/Class.hpp"

Class::Class(const std::string& type) : Object({type, false}) {
}

void Class::SetValue(Symbol name, std::shared_ptr<Object> value) {
  fields_[name] = value;
}

std::shared_ptr<Object> Class::GetValue(Symbol name) const {
  return fields_.at(name);
}

bool Class::IsClass() const {
  return true;
}

void Class::Print(std::ostream& stream) const {
  stream << "Class " << type_ << "; fields: {\n";
  for (auto&& field : fields_) {
    stream << "-> " << field.first.GetName() << " ";
    field.second->Print(stream);
  }
  stream << "}" << std::endl;
}
