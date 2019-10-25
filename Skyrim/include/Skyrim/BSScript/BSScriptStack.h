#pragma once

// c:_skyrim\code\tesv\bsscript\BSScriptStack.h

#include "../BSSystem/BSTSmartPointer.h"
#include "../BSCore/BSTArray.h"
#include "BSScriptVariable.h"
#include "BSScriptObject.h"
#include "BSScriptInternalCodeTasklet.h"


namespace BSScript
{
	BSSmartPointer(IStackCallbackFunctor);
	BSSmartPointer(BSScriptStack);

	// External Classes
	class IFunction;
	class MemoryPagePolicy;
	
	/*==============================================================================
	class BSScript::IStackCallbackFunctor +0000 (_vtbl=010EAE50)
	0000: class BSScript::IStackCallbackFunctor
	0004: |   struct BSIntrusiveRefCounted
	==============================================================================*/
	// 08
	class IStackCallbackFunctor : public BSIntrusiveRefCounted
	{
	public:
		virtual ~IStackCallbackFunctor();			// 008C5AA0

		virtual void	Unk_01(BSScriptVariable var) = 0;		// 00F51EE8 (pure)
		virtual bool	Unk_02(void);							// 00C3A5E0 { return false; }
		virtual void	Unk_03(BSScriptObjectPtr &arg1) = 0;	// 00F51EE8 (pure)
	};


	// 20 + sizeof(BSScriptVariable) * numArgs
	// the same type as VMState in skse
	class StackFrame
	{
	public:
		BSScriptStack		* stack;		// 00
		StackFrame			* parent;		// 04
		IFunction			* func;			// 08
		void				* unk0C;		// 0C
		UInt32				unk10;			// 10
		BSScriptVariable	baseValue;		// 14
		UInt32				numArgs;		// 1C
		//BSScriptVariable	args[];			// 20

		BSScriptVariable * GetArgs() const {
			return (BSScriptVariable *)(this + 1);
		}
	};

	// 58 - the same type as VMArgList and UnkVMStackData2 in skse)
	class BSScriptStack : public BSIntrusiveRefCounted
	{
	public:
		BSScriptStack();
		~BSScriptStack() { dtor(); }

		// 08 + sizeof(StackFrame)
		// the same type as UnkStackData1 in skse
		struct Chunk
		{
			void *	GetHead(void) const	{ return (void*)(this + 1); }
			void *	GetTail(void) const	{ return (void*)((UInt32)GetHead() + size); }

			bool	IsInRange(void * pointer) const {
				return (pointer >= GetHead()) && (pointer < GetTail());
			}

			UInt32			size;	// 00 - max 128byte?
			//StackFrame	frame	// 04
		};

		// 08
		struct Pair
		{
			Chunk	* chunk;	// 00
			UInt32	unk04;		// 04
		};

		inline UInt32 GetOffset(StackFrame * frame) const {
			return GetOffset_Impl(frame);
		}

		inline BSScript::BSScriptVariable * Get(StackFrame *frame, UInt32 idx, UInt32 offset) const {
			return Get_Impl(frame, idx, offset);
		}

		// @members
		//BSIntrusiveRefCounted		refCount;				// 00
		MemoryPagePolicy			* memoryPagePolicy;		// 04
		UInt32						* unk08;				// 08 - init'd VMState::PolicyHolder::unk14
		BSTSmallArray<Pair, 3>		chunks;					// 0C - stack data is splitted into 128-byte chunks
		UInt32						unk2C;					// 2C - init'd 0
		StackFrame					* current;				// 30 - init'd 0
		UInt32						unk34;					// 34 - init'd 0
		UInt32						unk38;					// 38 - init'd 0
		BSScriptVariable			resultValue;			// 3C - init'd 0
		UInt32						stackID;				// 44
		UInt32						unk48;					// 48
		InternalCodeTaskletData		* taskletData;			// 4C - init'd 0
		IStackCallbackFunctorPtr	callbackFunctorPtr;		// 50
		UInt32						unk54;					// 54 - init'd 0

	private:
		DEFINE_MEMBER_FN(ctor, BSScriptStack *, 0x00C3DA50, MemoryPagePolicy *a_memoryPagePolicy, UInt32 a_unk08, UInt32 a_stackID, UInt32 a_unk48, IStackCallbackPtr &callbackFunctorPtr);
		DEFINE_MEMBER_FN(dtor, void, 0x00C3CCA0);
		DEFINE_MEMBER_FN(Unk_00C3C6C0, bool, 0x00C3C6C0);	// called in dtor

		DEFINE_MEMBER_FN_const(GetOffset_Impl, UInt32, 0x00C3A620, StackFrame * frame);
		DEFINE_MEMBER_FN_const(Get_Impl, BSScript::BSScriptVariable *, 0x00C3AC40, StackFrame * frame, UInt32 idx, UInt32 offset);
	};
	STATIC_ASSERT(offsetof(BSScriptStack, current) == 0x30);
	STATIC_ASSERT(offsetof(BSScriptStack, stackID) == 0x44);
}
