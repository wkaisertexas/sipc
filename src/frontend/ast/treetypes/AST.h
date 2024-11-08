#pragma once

/*
 * This include is for convenience when defining algorithms spanning
 * the AST type hierarchy, e.g., visitors, code generation, pretty printing.
 *
 * It should be used sparingly as it introduces coupling to the entire
 * AST type hierarchy.
 */

#include "ASTAccessExpr.h"
#include "ASTAllocExpr.h"
#include "ASTAssignStmt.h"
#include "ASTArrayExpr.h"
#include "ASTArrayLenExpr.h"
#include "ASTTernaryExpr.h"
#include "ASTBinaryExpr.h"
#include "ASTBlockStmt.h"
#include "ASTDeRefExpr.h"
#include "ASTDeclNode.h"
#include "ASTDeclStmt.h"
#include "ASTErrorStmt.h"
#include "ASTExpr.h"
#include "ASTFieldExpr.h"
#include "ASTForStmt.h"
#include "ASTFunAppExpr.h"
#include "ASTFunction.h"
#include "ASTIfStmt.h"
#include "ASTInputExpr.h"
#include "ASTNode.h"
#include "ASTNotExpr.h"
#include "ASTNegExpr.h"
#include "ASTNullExpr.h"
#include "ASTNumberExpr.h"
#include "ASTOutputStmt.h"
#include "ASTProgram.h"
#include "ASTUpdateStmt.h"
#include "ASTRecordExpr.h"
#include "ASTRefExpr.h"
#include "ASTReturnStmt.h"
#include "ASTStmt.h"
#include "ASTIndexingExpr.h"
#include "ASTVariableExpr.h"
#include "ASTWhileStmt.h"
#include "ASTBoolExpr.h"
#include "ASTArrayOfExpr.h"