#pragma once

#include "BGSBaseAlias.h"

class BSFixedString;
class TESObjectREFR;
class Actor;

/*==============================================================================
class BGSRefAlias +0000 (_vtbl=010A3A74)
0000: class BGSRefAlias
0000: |   class BGSBaseAlias
==============================================================================*/
// 28
class BGSRefAlias : public BGSBaseAlias
{
public:
	enum { kTypeID = (UInt32)FormType::ReferenceAlias };

	virtual ~BGSRefAlias();												// 00555270

	// @override
	virtual bool					Unk_01(UInt32 arg1) override;		// 00554090
	virtual void					Unk_02(UInt32 arg1) override;		// 00554BA0
	virtual const BSFixedString &	GetTypeString(void) const override;	// 005533C0 { return BSFixedString("Ref")

	// @add
	virtual void					Unk_04(void);						// 00666552


	void Clear();
	TESObjectREFR* GetReference(void);
	Actor* GetActorReference(void);
	UInt32 ForceRefTo(TESObjectREFR * reference);

	DEFINE_MEMBER_FN(AttachReference, void, 00553400, RefHandle &refHandle);


	// @members
	//void		** _vtbl;		// 00 - 010A3A74
	UInt32		unk18;			// 18 - init'd 0 - One of these is the filltype/filltype filter
	UInt32		unk1C;			// 1C
	UInt32		unk20;			// 20
	void		* unk24;		// 24

private:
	DEFINE_MEMBER_FN(ctor, BGSRefAlias *, 0x005533D0, TESQuest *questOwner, UInt32 aliasId);
	DEFINE_MEMBER_FN(dtor, void, 0x00553C30);
};
