#pragma once

#include "debug.h"

#include "typing.hpp"

#include "jouette/instructions/expressions/BinOneRegInstruction.hpp"
#include "jouette/instructions/expressions/BinTwoRegInstruction.hpp"
#include "jouette/instructions/expressions/Call.hpp"

#include "jouette/instructions/commands/LoadStore.hpp"
#include "jouette/instructions/commands/MoveInstruction.hpp"
#include "jouette/instructions/commands/Return.hpp"
#include "jouette/instructions/commands/Label.hpp"

#include "jouette/instructions/commands/CJumpInstruction.hpp"
#include "jouette/instructions/commands/Jump.hpp"

#include "jouette/registers/Register.hpp"

#include "jouette/visitors/Visitor.hpp"
#include "jouette/visitors/PrintVisitor.hpp"

#include "irtree/jouette_rules/elements.hpp"
