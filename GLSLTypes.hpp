#ifndef GLSLTYPES_HPP
#define GLSLTYPES_HPP

#include <clang/AST/Decl.h>
#include <llvm/Support/Casting.h>

namespace fxc
{
	class GLSLType
	{
	public:
		enum GLSLTypeKind
		{
			// Base types
			TK_ScalarType,
			TK_VectorType,
			TK_MatrixType,
			TK_LastBasicType,

			TK_StructType,
			TK_SamplerType,
			TK_ArrayType
		};

	private:
		GLSLTypeKind kind;

	public:
		GLSLTypeKind getKind() const { return kind; }
		GLSLType(GLSLTypeKind K) : kind(K) {}
	};

	class GLSLBasicType : public GLSLType
	{
	public:
		GLSLBasicType(GLSLTypeKind K) : GLSLType(K) {}
	};

	enum class GLSLScalarKind
	{
		Int,
		UInt,
		Float,
		Double,
		Bool
	};

	class GLSLScalarType : public GLSLBasicType
	{
	public:
		const GLSLScalarKind scalarKind;

		GLSLScalarType(GLSLScalarKind SK) : GLSLBasicType(TK_ScalarType), scalarKind(SK) {}
	};
	
	class GLSLVectorType : public GLSLBasicType
	{
	public:
		const GLSLScalarKind scalarKind;

		GLSLVectorType(GLSLScalarKind SK) : GLSLBasicType(TK_VectorType), scalarKind(SK) {}
	};

	class GLSLMatrixType : public GLSLBasicType
	{
	public:
		const GLSLScalarKind scalarKind;

		GLSLMatrixType(GLSLScalarKind SK) : GLSLBasicType(TK_MatrixType), scalarKind(SK) {}
	};

	class GLSLStructType : public GLSLType
	{
	public:
		struct Field
		{
			GLSLType* type;
			std::string name;
			int byteOffset;
		};

	private:
		std::vector<Field> fields;
	};
}

#endif // !GLSLTYPES_HPP
