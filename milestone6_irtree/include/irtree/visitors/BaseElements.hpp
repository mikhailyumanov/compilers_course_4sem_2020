//
// Created by akhtyamovpavel on 4/14/20.
// Modified by Mikahil Yumanov on 7/21/20
//

#include "irtree/nodes/expressions/NameExpression.hpp"
#include "irtree/nodes/expressions/CallExpression.hpp"
#include "irtree/nodes/expressions/BinopExpression.hpp"
#include "irtree/nodes/expressions/ConstExpression.hpp"
#include "irtree/nodes/expressions/MemExpression.hpp"
#include "irtree/nodes/expressions/TempExpression.hpp"

#include "irtree/nodes/statements/ExpStatement.hpp"
#include "irtree/nodes/statements/JumpConditionalStatement.hpp"
#include "irtree/nodes/statements/JumpStatement.hpp"
#include "irtree/nodes/statements/LabelStatement.hpp"
#include "irtree/nodes/statements/MoveStatement.hpp"
#include "irtree/nodes/statements/SeqStatement.hpp"

#include "irtree/nodes/ExpressionList.hpp"
