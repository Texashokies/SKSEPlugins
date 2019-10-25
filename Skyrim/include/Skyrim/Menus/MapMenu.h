#pragma once

#include "IMenu.h"
#include "../BSCore/BSTArray.h"
#include "../NetImmerse/BSRenderTargetGroup.h"
#include "../NetImmerse/NiCullingProcess.h"
#include "../NetImmerse/NiAlphaAccumulator.h"
#include "../Camera/MapCamera.h"
#include "../Camera/LocalMapCamera.h"
#include "../BSDevices/MenuEventHandler.h"

class TESFullName;
class MapMenu;


// 1C8
class BSShaderAccumulator : public NiAlphaAccumulator
{
public:
	// @add
	virtual void Unk_26(void);							// 26 00C94EB0
	virtual void Unk_27(void);							// 27 00C955C0
	virtual void Unk_28(UInt32 arg1, UInt32 arg2);		// 28 00C928D0 { return; }

	// @members
	//void	** _vtbl;	// 00 - 01153BB8

private:
	DEFINE_MEMBER_FN(ctor, BSShaderAccumulator*, 0x00C94620, UInt32 arg1, UInt32 arg2);	// arg1 = 0x63 or 0x64, arg2 = 1 // called in class Main::ctor
};


// 2A8
struct LocalMapMenu
{
public:
	/*==============================================================================
	class LocalMapMenu::InputHandler +0000 (_vtbl=010E9060)
	0000: class LocalMapMenu::InputHandler
	0000: |   class MenuEventHandler
	0004: |   |   struct BSIntrusiveRefCounted
	==============================================================================*/
	// 10
	class InputHandler : public MenuEventHandler
	{
		// @members
		//void			**_vtbl;			// 00 - 010E9060
		LocalMapMenu	* localMapMenu;		// 0C
	};


	// 238
	class LocalMapCullingProcess
	{
	public:
		// @members
		BSCullingProcess	cullingProcess;					// 000
		LocalMapCamera		localMapCamera;					// 170
		BSShaderAccumulator	* shaderAccumulator;			// 1BC
		BSRenderTargetGroup	* localMapTexture;				// 1C0
		UInt32				unk1C4[(0x230 - 0x1C4) >> 2];	// 1C4
		UInt32				width;							// 230
		UInt32				height;							// 234
		NiNode				* niNode;						// 238

	private:
		DEFINE_MEMBER_FN(ctor, void, 0x00487610);
		DEFINE_MEMBER_FN(CreateMapTarget, BSRenderTargetGroup **, 0x00486590, UInt32 width, UInt32 height);
		DEFINE_MEMBER_FN(Init, void, 0x00487D20);
		DEFINE_MEMBER_FN(Process, void, 0x00487900);
	};
	STATIC_ASSERT(offsetof(LocalMapCullingProcess, localMapCamera) == 0x170);
	STATIC_ASSERT(offsetof(LocalMapCullingProcess, niNode) == 0x238);

	struct Texture
	{
		NiRenderedTexture		* renderedLocalMapTexture;		// 00 26C 2A4
		UInt32					unk270;							// 04 270 2A8
	};

	// @members
	BSTArray<UInt32>		unk00;							// 000 (38)
	UInt32					unk0C;							// 00C (3C)
	GFxValue				markerData;						// 010 (40)
	float					unk20;							// 020 (50) - 192.0f
	float					unk24;							// 024 (54) - 200.0f
	float					unk28;							// 028 (58) - 832.0f
	float					unk2C;							// 02C (5C) - 560.0f
	LocalMapCullingProcess	cullingProcess;					// 030 (60)
	Texture					texture;						// 26C (2A4)
	GFxValue				localMapRoot;					// 278 (2B0)
	GFxValue				mapRoot;						// 288 (2C0)
	GFxMovieView			* view;							// 298 (2D0) - init'd nullptr
	InputHandler			* inputHandler;					// 29C (2D4) - init'd nullptr
	SInt32					unk2A0;							// 2A0 (2D8) - init'd -1
	UInt8					unk2A4;							// 2A4 (2DC) - init'd 0
	UInt8					unk2A5;							// 2A5 (2DD) - init'd 0
	UInt8					unk2A6;							// 2A6 (2DE) - init'd 1
	UInt8					pad2A7;							// 2A7 (2DF)

	DEFINE_MEMBER_FN(ctor, LocalMapMenu *, 0x0089B2C0);
};
STATIC_ASSERT(offsetof(LocalMapMenu, cullingProcess) == 0x30);
STATIC_ASSERT(offsetof(LocalMapMenu, texture) == 0x26C);


/*==============================================================================
class MapInputHandler +0000 (_vtbl=????????)
0000: class MapInputHandler
0000: |   class MenuEventHandler
0004: |   |   struct BSIntrusiveRefCounted
==============================================================================*/
class MapInputHandler : public MenuEventHandler
{
public:
	// @members
	MapMenu*	mapMenu;	// 0C
};


/*==============================================================================
class MapLookHandler +0000 (_vtbl=010E94D4)
0000: class MapLookHandler
0000: |   class MapInputHandler
0000: |   |   class MenuEventHandler
0004: |   |   |   struct BSIntrusiveRefCounted
==============================================================================*/
// 14
class MapLookHandler : public MapInputHandler
{
	// @members
	bool	unk10;
};

/*==============================================================================
class MapZoomHandler +0000 (_vtbl=010E94F0)
0000: class MapZoomHandler
0000: |   class MapInputHandler
0000: |   |   class MenuEventHandler
0004: |   |   |   struct BSIntrusiveRefCounted
==============================================================================*/
// 10
class MapZoomHandler : public MapInputHandler
{
};

/*==============================================================================
class MapMoveHandler +0000 (_vtbl=010E950C)
0000: class MapMoveHandler
0000: |   class MapInputHandler
0000: |   |   class MenuEventHandler
0004: |   |   |   struct BSIntrusiveRefCounted
==============================================================================*/
// 18
class MapMoveHandler : public MapInputHandler
{
	// @members
	UInt32	unk10;		// init'd [012C25B0]
	UInt32	unk14;		// init'd [012C25B4]
};

/*==============================================================================
struct IMapCameraCallbacks +0000 (_vtbl=010E926C)
0000: struct IMapCameraCallbacks
==============================================================================*/
struct IMapCameraCallbacks
{
	virtual void IMapCameraCallbacks_Unk_00(void) = 0;		// MapMenu::IMapCameraCallbacks_Unk_00
	virtual void IMapCameraCallbacks_Unk_01(void) = 0;		// MapMenu::IMapCameraCallbacks_Unk_01 { return; }

	virtual ~IMapCameraCallbacks();		// 0089BED0

	MapMoveHandler*	mapMoveHandler;		// 04 - init'd 0
	MapLookHandler*	mapLookHandler;		// 08 - init'd 0
	MapZoomHandler*	mapZoomHandler;		// 0C - init'd 0
};


/*==============================================================================
class MapMenu +0000 (_vtbl=010E95B4)
0000: class MapMenu
0000: |   class IMenu
0000: |   |   class FxDelegateHandler
0000: |   |   |   class GRefCountBase<class FxDelegateHandler,2>
0000: |   |   |   |   class GRefCountBaseStatImpl<class GRefCountImpl,2>
0000: |   |   |   |   |   class GRefCountImpl
0000: |   |   |   |   |   |   class GRefCountImplCore
001C: |   class BSTEventSink<class MenuOpenCloseEvent>
0020: |   struct IMapCameraCallbacks
==============================================================================*/
// 3B8
class MapMenu : public IMenu,
	public BSTEventSink<class MenuOpenCloseEvent>,		// 1C
	public IMapCameraCallbacks							// 20
{
public:
	// unk0C - 3
	// Flags - 0x9005
	// unk14 - 7
	enum
	{
		kMarkerType_Location = 0
	};

	// 20
	struct MarkerData
	{
		TESFullName * name;			// 00
		UInt32		refHandle;		// 04
		GFxValue	unk08;			// 08
		UInt32		unk18;			// 18
		bool		unk1C;			// 1C
	};

	virtual ~MapMenu();				// 008A1DF0

	// @override class IMenu : (vtbl=010E95B4)
	virtual void	Accept(CallbackProcessor *processor) override;	// 008A34F0
	virtual UInt32	ProcessMessage(UIMessage *message) override;	// 008A2B60
	virtual void	NextFrame(UInt32 arg0, UInt32 arg1) override;	// 008A27C0
	virtual void	Unk_07(void) override;							// 0089F630
	virtual void	InitMovie(void) override;						// 0089F8A0
	
	// @override class BSTEventSink<class MenuOpenCloseEvent> : (vtbl=010E95A8)
	virtual EventResult ReceiveEvent(MenuOpenCloseEvent *, BSTEventSource<MenuOpenCloseEvent>*) override;	 // 008A0B90

	// @override struct IMapCameraCallbacks : (vtbl=010E9598)
	virtual void IMapCameraCallbacks_Unk_00(void) override;		// 008A1C50
	virtual void IMapCameraCallbacks_Unk_01(void) override;		// 006C50E0 { return; }


	static IMenu * Create()
	{
		return ((IMenu*(*)())0x008A1D90)();
	}

	// @members
	//void					** _vtbl;								// 000 - 010E95B4
	//MapMoveHandler*		IMapCameraCallbacks::mapMoveHandler;	// 024 - init'd 0
	//MapLookHandler*		IMapCameraCallbacks::mapLookHandler;	// 028 - init'd 0
	//MapZoomHandler*		IMapCameraCallbacks::mapZoomHandler;	// 02C - init'd 0
	UInt32					unk030; 								// 030 - init'd 0
	UInt32					unk034; 								// 034
	LocalMapMenu			localMap;								// 038
	UInt32					unk2E0;									// 2E0
	UInt32					unk2E4;									// 2E4
	UInt32					unk2E8;									// 2E8
	UInt32					unk2EC;									// 2EC
	BSTArray<MarkerData>	markers;								// 2F0
	BSTArray<GFxValue>		unk2FC;									// 2FC
	MapCamera				mapCamera;								// 308
	//																// 368
	// ..

private:
	DEFINE_MEMBER_FN(ctor, MapMenu *, 0x008A0F30);
	DEFINE_MEMBER_FN(dtor, void, 0x008A1410);
};
STATIC_ASSERT(offsetof(MapMenu, localMap) == 0x38);
STATIC_ASSERT(offsetof(MapMenu, markers) == 0x2F0);
