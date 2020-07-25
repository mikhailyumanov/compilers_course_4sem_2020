#pragma once

#include "irtree/tree_wrappers/SubtreeWrapper.hpp"
#include "irtree/tree_wrappers/ExpressionWrapper.hpp"
#include "irtree/tree_wrappers/StatementWrapper.hpp"
#include "irtree/tree_wrappers/conditional_wrappers/ConditionalWrapper.hpp"
#include "irtree/tree_wrappers/conditional_wrappers/NegateConditionalWrapper.hpp"
#include "irtree/tree_wrappers/conditional_wrappers/AndConditionalWrapper.hpp"
#include "irtree/tree_wrappers/conditional_wrappers/OrConditionalWrapper.hpp"
#include "irtree/tree_wrappers/conditional_wrappers/RelativeConditionalWrapper.hpp"

#include "irtree/generators/Label.hpp"
#include "irtree/generators/Temporary.hpp"

#include "irtree/nodes/expressions/Expression.hpp"
#include "irtree/nodes/BaseElement.hpp"
#include "irtree/nodes/statements/Statement.hpp"
#include "irtree/nodes/statements/ExpStatement.hpp"
#include "irtree/nodes/statements/JumpConditionalStatement.hpp"
#include "irtree/nodes/statements/JumpStatement.hpp"
#include "irtree/nodes/statements/MoveStatement.hpp"
#include "irtree/nodes/statements/SeqStatement.hpp"
#include "irtree/nodes/statements/LabelStatement.hpp"

#include "irtree/nodes/expressions/ConstExpression.hpp"
#include "irtree/nodes/expressions/BinopExpression.hpp"
#include "irtree/nodes/expressions/TempExpression.hpp"
#include "irtree/nodes/expressions/MemExpression.hpp"
#include "irtree/nodes/expressions/CallExpression.hpp"
#include "irtree/nodes/expressions/NameExpression.hpp"
#include "irtree/nodes/expressions/EseqExpression.hpp"
#include "irtree/nodes/ExpressionList.hpp"

#include "irtree/visitors/Visitor.hpp"
#include "irtree/visitors/PrintVisitor.hpp"
#include "irtree/visitors/BaseElements.hpp"

#include "irtree/types/LogicOperatorType.hpp"
#include "irtree/types/BinaryOperatorType.hpp"
