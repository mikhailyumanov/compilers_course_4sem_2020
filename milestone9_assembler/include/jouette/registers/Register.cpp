#include "jouette/registers/Register.hpp"


namespace Jouette {

Register::Register(const IRT::Temporary& temp) : temp_{temp} {
}

IRT::Temporary Register::GetTemporary() const {
  return temp_;
}

bool Register::IsNull() const {
  return (std::string) *this == (std::string) *GetNullRegister();
}


Register::operator std::string() const {
  return temp_.ToString();
}

std::shared_ptr<Register> GetNullRegister() {
  static auto null_register = std::make_shared<Register>(
      IRT::Temporary("%null"));
  return null_register;
}

std::ostream& operator<<(std::ostream& os, const Register& reg) {
  os << (std::string) reg;
  return os;
}
  
}
