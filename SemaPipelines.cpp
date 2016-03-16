#include "Sema.hpp"

namespace fxc
{
	bool Sema::CheckProgramPipeline(clang::CXXRecordDecl* Declaration)
	{
		auto& OS = llvm::errs();

		// assigned resource slots
		unsigned lastTextureSlot = 0;
		unsigned lastUniformBufferSlot = 0;
		unsigned lastRWBufferSlot = 0;

		for (auto f : Declaration->fields())
		{
			// check for special types

			if (auto fieldType = f->getType()->getAs<clang::RecordType>())
			{
				auto fieldTypeDecl = fieldType->getDecl();
				const clang::AGFXBuiltinTypeAttr* attr = nullptr;
				if (GetSpecialDeclKind(fieldTypeDecl, attr) == SpecialDeclKind::BuiltinType)
				{
					assert(attr);
					switch (attr->getKind())
					{
					case clang::AGFXBuiltinTypeAttr::Texture1D:
					case clang::AGFXBuiltinTypeAttr::Texture2D:
					case clang::AGFXBuiltinTypeAttr::Texture3D:
						lastTextureSlot++;
						break;
					case clang::AGFXBuiltinTypeAttr::Vec1:
					case clang::AGFXBuiltinTypeAttr::Vec2:
					case clang::AGFXBuiltinTypeAttr::Vec3:
					case clang::AGFXBuiltinTypeAttr::Vec4:
					case clang::AGFXBuiltinTypeAttr::Mat2:
					case clang::AGFXBuiltinTypeAttr::Mat3:
					case clang::AGFXBuiltinTypeAttr::Mat4:
						lastUniformBufferSlot++;
						break;
					}
				}
			}
		}

		OS << lastTextureSlot << "\n" << lastUniformBufferSlot << "\n";
		return false;
	}
}