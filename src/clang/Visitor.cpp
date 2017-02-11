#include <functional>
#include <unordered_map>

#include "clang.hpp"

namespace clang {
const std::unordered_map<
    int,
    std::function<Result(Visitor *, Cursor const &, Cursor const &)>>
    bindings{
        {CXCursor_UnexposedDecl, &Visitor::visit_unexposed_decl},
        {CXCursor_StructDecl, &Visitor::visit_struct_decl},
        {CXCursor_UnionDecl, &Visitor::visit_union_decl},
        {CXCursor_ClassDecl, &Visitor::visit_class_decl},
        {CXCursor_EnumDecl, &Visitor::visit_enum_decl},
        {CXCursor_FieldDecl, &Visitor::visit_field_decl},
        {CXCursor_EnumConstantDecl, &Visitor::visit_enum_constant_decl},
        {CXCursor_FunctionDecl, &Visitor::visit_function_decl},
        {CXCursor_VarDecl, &Visitor::visit_var_decl},
        {CXCursor_ParmDecl, &Visitor::visit_parm_decl},
        {CXCursor_TypedefDecl, &Visitor::visit_typedef_decl},
        {CXCursor_TypeRef, &Visitor::visit_type_ref},
        {CXCursor_UnaryOperator, &Visitor::visit_unary_operator},
        {CXCursor_BinaryOperator, &Visitor::visit_binary_operator},
        {CXCursor_LabelStmt, &Visitor::visit_label_stmt},
        {CXCursor_CompoundStmt, &Visitor::visit_compound_stmt},
        {CXCursor_SwitchStmt, &Visitor::visit_switch_stmt},
        {CXCursor_DoStmt, &Visitor::visit_do_stmt},
        {CXCursor_ForStmt, &Visitor::visit_for_stmt},
        {CXCursor_GotoStmt, &Visitor::visit_goto_stmt},
        {CXCursor_IndirectGotoStmt, &Visitor::visit_indirect_goto_stmt},
        {CXCursor_DeclStmt, &Visitor::visit_decl_stmt},
        {CXCursor_MacroDefinition, &Visitor::visit_macro_definition},
        {CXCursor_InclusionDirective, &Visitor::visit_inclusion_directive},
    };

static CXChildVisitResult visitor_wrapper(CXCursor raw_cursor,
                                          CXCursor raw_parent,
                                          CXClientData data) {
  auto visitor = static_cast<Visitor *>(data);
  Cursor cursor{raw_cursor}, parent{raw_parent};
  return visitor->dispatch(cursor, parent);
}

void Visitor::visit(Cursor const &cursor) {
  clang_visitChildren(cursor, visitor_wrapper, this);
}

CXChildVisitResult Visitor::dispatch(Cursor const &cursor,
                                     Cursor const &parent) {
  if (cursor.location().is_in_system_header()) {
    return CXChildVisit_Continue;
  }
  try {
    auto visitor{bindings.at(cursor.kind())};
    int result{static_cast<int>(visitor(this, cursor, parent))};
    return static_cast<CXChildVisitResult>(result);
  } catch (std::out_of_range &e) {
    int result{static_cast<int>(this->visit_unknown(cursor, parent))};
    return static_cast<CXChildVisitResult>(result);
  }
}
}
