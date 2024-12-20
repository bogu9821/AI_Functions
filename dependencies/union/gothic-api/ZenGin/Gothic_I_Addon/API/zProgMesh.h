﻿// Supported with union (c) 2018-2023 Union team
// Licence: GNU General Public License

#ifndef __ZPROG_MESH_H__VER1__
#define __ZPROG_MESH_H__VER1__

namespace Gothic_I_Addon {
  const int NUM_WEDGE_CACHE = 4096;
  const int NUM_POS_CACHE   = 2048;

  enum zTPMRenderFlags {
    zPM_RENDER_FLAG_SW_TRAFO_VERTS     = 1,
    zPM_RENDER_FLAG_PACK_DYNAMIC_VB    = 2,
    zPM_RENDER_FLAG_DONT_SET_TRANSFROM = 4
  };

  enum zTPMLightingMode {
    zPM_LIGHTING_MODE_PRELIT = 0,
    zPM_LIGHTING_MODE_EXACT
  };

  enum zTPMBuildFlags {
    zPM_BUILD_FLAG_NO_LOD                  = 1,
    zPM_BUILD_FLAG_NO_TRIPLANES            = 2,
    zPM_BUILD_FLAG_NO_POSNORMALS           = 4,
    zPM_BUILD_FLAG_FORCE_SMOOTH_NORMALS    = 8,
    zPM_BUILD_FLAG_DONT_REMOVE_DEGEN_POLYS = 16,
    zPM_BUILD_FLAG_CREATE_SUBDIV_DATA      = 32
  };

  // sizeof C0h
  struct zTLazyMesh {
    zOPERATORS_DECLARATION()

    zCArray<int> wedgePermut;                      // sizeof 0Ch    offset 00h
    zCArray<int> wedgeParent;                      // sizeof 0Ch    offset 0Ch
    zCArray<unsigned short int> triMatIndexList;   // sizeof 0Ch    offset 18h
    zCArray<zVEC3> posList;                        // sizeof 0Ch    offset 24h
    zCArray<zVEC3> posNormalList;                  // sizeof 0Ch    offset 30h
    zCArray<zCMaterial*> matList;                  // sizeof 0Ch    offset 3Ch
    zCArray<zTPMTriangle> triList;                 // sizeof 0Ch    offset 48h
    zCArray<zTPMWedge> wedgeList;                  // sizeof 0Ch    offset 54h
    zCArray<float> colorList;                      // sizeof 0Ch    offset 60h
    zCArray<unsigned short int> wedgeMap;          // sizeof 0Ch    offset 6Ch
    zCArray<zTPMVertexUpdate> vertexUpdates;       // sizeof 0Ch    offset 78h
    zCArray<unsigned short int> triPlaneIndexList; // sizeof 0Ch    offset 84h
    zCArray<zTPlane> triPlaneList;                 // sizeof 0Ch    offset 90h
    zCArray<zTPMTriangleEdges> triEdgeList;        // sizeof 0Ch    offset 9Ch
    zCArray<zTPMEdge> edgeList;                    // sizeof 0Ch    offset A8h
    zCArray<float> edgeScoreList;                  // sizeof 0Ch    offset B4h

    void zTLazyMesh_OnInit() zCall( 0x005BE240 );
    zTLazyMesh()             zInit( zTLazyMesh_OnInit() );
    ~zTLazyMesh()            zCall( 0x005BE310 );

    // user API
    #include "zTLazyMesh.inl"
  };

  // sizeof 18h
  struct zTPMWedge {
    zOPERATORS_DECLARATION()

    zVEC3 normal;                // sizeof 0Ch    offset 00h
    zVEC2 texUV;                 // sizeof 08h    offset 0Ch
    unsigned short int position; // sizeof 02h    offset 14h

    zTPMWedge() {}

    // user API
    #include "zTPMWedge.inl"
  };

  // sizeof 06h
  struct zTPMTriangle {
    zOPERATORS_DECLARATION()

    unsigned short int wedge[3]; // sizeof 06h    offset 00h

    zTPMTriangle() {}

    // user API
    #include "zTPMTriangle.inl"
  };

  // sizeof 06h
  struct zTPMTriangleEdges {
    zOPERATORS_DECLARATION()

    unsigned short int edge[3]; // sizeof 06h    offset 00h

    zTPMTriangleEdges() {}

    // user API
    #include "zTPMTriangleEdges.inl"
  };

  // sizeof 04h
  struct zTPMEdge {
    zOPERATORS_DECLARATION()

    unsigned short int wedge[2]; // sizeof 04h    offset 00h

    zTPMEdge() {}

    // user API
    #include "zTPMEdge.inl"
  };

  // sizeof 04h
  struct zTPMVertexUpdate {
    zOPERATORS_DECLARATION()

    unsigned short int numNewTri;   // sizeof 02h    offset 00h
    unsigned short int numNewWedge; // sizeof 02h    offset 02h

    zTPMVertexUpdate() {}

    // user API
    #include "zTPMVertexUpdate.inl"
  };

  // sizeof D4h
  class zCProgMeshProto : public zCVisual {
  public:
    zCLASS_DECLARATION( zCProgMeshProto )

    // sizeof 10h
    struct zTLODRenderArgs {
      zOPERATORS_DECLARATION()

      float vertPerc;     // sizeof 04h    offset 00h
      int numPos;         // sizeof 04h    offset 04h
      int numMinMorphPos; // sizeof 04h    offset 08h
      float morphFrac;    // sizeof 04h    offset 0Ch

      zTLODRenderArgs() {}

      // user API
      #include "zCProgMeshProto_zTLODRenderArgs.inl"
    };

    // sizeof 10h
    struct zTLODParams {
      zOPERATORS_DECLARATION()

      float strength;   // sizeof 04h    offset 00h
      float zDisplace2; // sizeof 04h    offset 04h
      float morphPerc;  // sizeof 04h    offset 08h
      int minVerts;     // sizeof 04h    offset 0Ch

      zTLODParams() {}

      // user API
      #include "zCProgMeshProto_zTLODParams.inl"
    };

    // sizeof 58h
    class zCSubMesh {
    public:
      zOPERATORS_DECLARATION()

      zCMaterial* material;                               // sizeof 04h    offset 00h
      zCArrayAdapt<zTPMTriangle> triList;                 // sizeof 08h    offset 04h
      zCArrayAdapt<zTPMWedge> wedgeList;                  // sizeof 08h    offset 0Ch
      zCArrayAdapt<float> colorList;                      // sizeof 08h    offset 14h
      zCArrayAdapt<unsigned short int> triPlaneIndexList; // sizeof 08h    offset 1Ch
      zCArrayAdapt<zTPlane> triPlaneList;                 // sizeof 08h    offset 24h
      zCArrayAdapt<zTPMTriangleEdges> triEdgeList;        // sizeof 08h    offset 2Ch
      zCArrayAdapt<zTPMEdge> edgeList;                    // sizeof 08h    offset 34h
      zCArrayAdapt<float> edgeScoreList;                  // sizeof 08h    offset 3Ch
      zCArrayAdapt<unsigned short int> wedgeMap;          // sizeof 08h    offset 44h
      zCArrayAdapt<zTPMVertexUpdate> vertexUpdates;       // sizeof 08h    offset 4Ch
      int vbStartIndex;                                   // sizeof 04h    offset 54h

      void zCSubMesh_OnInit() zCall( 0x005C1380 );
      zCSubMesh()             zInit( zCSubMesh_OnInit() );
      ~zCSubMesh()            zCall( 0x005C13D0 );

      // user API
      #include "zCProgMeshProto_zCSubMesh.inl"
    };

    // sizeof 10h
    struct zTLODRenderArgsSubMesh {
      zOPERATORS_DECLARATION()

      int numTri;           // sizeof 04h    offset 00h
      int numWedge;         // sizeof 04h    offset 04h
      int numMinMorphWedge; // sizeof 04h    offset 08h
      int numSubdivEdges;   // sizeof 04h    offset 0Ch

      zTLODRenderArgsSubMesh() {}

      // user API
      #include "zCProgMeshProto_zTLODRenderArgsSubMesh.inl"
    };

    zCArrayAdapt<zVEC3> posList;        // sizeof 08h    offset 34h
    zCArrayAdapt<zVEC3> posNormalList;  // sizeof 08h    offset 3Ch
    zTBBox3D bbox3D;                    // sizeof 18h    offset 44h
    zCOBBox3D obbox3D;                  // sizeof 44h    offset 5Ch
    zCVertexBuffer* vertexBufferStatic; // sizeof 04h    offset A0h
    zCSubMesh* subMeshList;             // sizeof 04h    offset A4h
    int numSubMeshes;                   // sizeof 04h    offset A8h
    unsigned char* dataPool;            // sizeof 04h    offset ACh
    unsigned long dataSize;             // sizeof 04h    offset B0h
    float avgTriArea;                   // sizeof 04h    offset B4h
    zTLODParams lodParams;              // sizeof 10h    offset B8h
    zTPMLightingMode lightingMode;      // sizeof 04h    offset C8h
    unsigned long pmeshID;              // sizeof 04h    offset CCh
    unsigned long renderSortKey;        // sizeof 04h    offset D0h

    zDefineInheritableCtor( zCProgMeshProto ) : zCtor( zCVisual ) {}
    void zCProgMeshProto_OnInit()                                                                                                              zCall( 0x005C1450 );
    zCProgMeshProto() : zCtor( zCVisual )                                                                                                      zInit( zCProgMeshProto_OnInit() );
    void CalcRenderSortKey()                                                                                                                   zCall( 0x005C16C0 );
    void PackStaticVertexBuffers()                                                                                                             zCall( 0x005C1780 );
    int __fastcall CheckRayPolyIntersection( zCSubMesh*, int, zVEC3 const&, zVEC3 const&, zVEC3&, float& ) const                               zCall( 0x005C2590 );
    int __fastcall CheckRayPolyIntersection2Sided( zCSubMesh*, int, zVEC3 const&, zVEC3 const&, zVEC3&, float& ) const                         zCall( 0x005C28A0 );
    int GetNumTri() const                                                                                                                      zCall( 0x005C2D70 );
    float __fastcall CalcLODRenderVertPerc( zTRenderContext const& )                                                                           zCall( 0x005C2FD0 );
    int __fastcall CalcLODRenderArgs( zTRenderContext const&, zTLODRenderArgs& )                                                               zCall( 0x005C31D0 );
    int __fastcall CalcLODRenderArgsSubMesh( zTRenderContext const&, zTLODRenderArgs const&, zCSubMesh const*, zTLODRenderArgsSubMesh& )       zCall( 0x005C33C0 );
    int __fastcall RenderProgMesh( zTRenderContext&, int, zTLODRenderArgs*, zCRenderLightContainer*, float, float )                            zCall( 0x005C3480 );
    int __fastcall RenderStatic( zTRenderContext&, int, zTLODRenderArgs*, zCRenderLightContainer* )                                            zCall( 0x005C3A90 );
    int __fastcall RenderStaticLOD( zTRenderContext&, int, zTLODRenderArgs*, zCRenderLightContainer* )                                         zCall( 0x005C3B80 );
    void __fastcall SoftwareTransformVerts( int, zTLODRenderArgs*, float, float )                                                              zCall( 0x005C3E00 );
    int __fastcall RenderDynamicLOD( zTRenderContext&, int, zTLODRenderArgs*, zCRenderLightContainer*, float, float )                          zCall( 0x005C4180 );
    void __fastcall CalcSubdiv( int, zTLODRenderArgs const* )                                                                                  zCall( 0x005C4910 );
    void __fastcall CalcNumSubdivEdges( zCSubMesh*, zTLODRenderArgs const*, zTLODRenderArgsSubMesh& )                                          zCall( 0x005C49E0 );
    void __fastcall CalcSubdivSubMesh( zCSubMesh*, zCVertexBuffer*, zTLODRenderArgs const*, zCRenderLightContainer*, zTLODRenderArgsSubMesh& ) zCall( 0x005C4A40 );
    int __fastcall RenderDynamicSubdiv( zTRenderContext&, int, zTLODRenderArgs*, zCRenderLightContainer*, float, float )                       zCall( 0x005C4DB0 );
    int __fastcall RenderStaticLODShadow( zTRenderContext&, int, zTLODRenderArgs*, zCRenderLightContainer* )                                   zCall( 0x005C5210 );
    static zCObject* _CreateNewInstance()                                                                                                      zCall( 0x005C0F10 );
    static void SetLODParamStrengthModifier( float )                                                                                           zCall( 0x005C1700 );
    static float GetLODParamStrengthModifier()                                                                                                 zCall( 0x005C1760 );
    static zCVisual* Load_novt( zSTRING const& )                                                                                               zCall( 0x005C1A10 );
    static int BuildProgMeshProto( zCMesh*, zCProgMeshProto*, zCArray<int>*, int )                                                             zCall( 0x005C2520 );
    static void InitProgMeshProto()                                                                                                            zCall( 0x005C2D90 );
    static int CreateDynamicVertexBuffer()                                                                                                     zCall( 0x005C2EF0 );
    static void CleanupProgMeshProto()                                                                                                         zCall( 0x005C2F60 );
    static unsigned short GetFileVersion()                                                                                                     zCall( 0x005C55D0 );
    virtual zCClassDef* _GetClassDef() const                                                                                                   zCall( 0x005C1590 );
    virtual ~zCProgMeshProto()                                                                                                                 zCall( 0x005C15D0 );
    virtual int Render( zTRenderContext& )                                                                                                     zCall( 0x005C3460 );
    virtual int IsBBox3DLocal()                                                                                                                zCall( 0x005C1250 );
    virtual zTBBox3D GetBBox3D()                                                                                                               zCall( 0x005C1260 );
    virtual zCOBBox3D* GetOBBox3D()                                                                                                            zCall( 0x005C1290 );
    virtual zSTRING GetVisualName()                                                                                                            zCall( 0x005C19C0 );
    virtual void DynLightVisual( zCArray<zCVobLight*> const&, zMAT4* )                                                                         zCall( 0x005C12A0 );
    virtual unsigned long GetRenderSortKey() const                                                                                             zCall( 0x005C12B0 );
    virtual int CanTraceRay() const                                                                                                            zCall( 0x005C12C0 );
    virtual int TraceRay( zVEC3 const&, zVEC3 const&, int, zTTraceRayReport& )                                                                 zCall( 0x005C2B90 );
    virtual zSTRING const* GetFileExtension( int )                                                                                             zCall( 0x005C1990 );
    virtual zCVisual* LoadVisualVirtual( zSTRING const& ) const                                                                                zCall( 0x005C19B0 );
    virtual int Save( zCFileBIN& )                                                                                                             zCall( 0x005C55E0 );
    virtual int Load( zCFileBIN& )                                                                                                             zCall( 0x005C5A20 );


    // static properties
    static int& s_frameCtr;
    static unsigned short int*& s_wedgeRemap;
    static zVEC3*& s_posCacheList;
    static zVEC3*& s_posNormalCSList;
    static zCArray<unsigned short>& s_workIndexList;
    static int& s_subMeshRenderDir;
    static zCVertexBufferDyn*& s_vertBufferColor;
    static zCVertexBufferDyn*& s_vertBufferNormal;
    static float& s_lodParamStrengthOverride;
    static float& s_lodParamStrengthModifier;
    static int& s_markMeshMaterials;
    static int& s_autoSubdivEnabled;
    static unsigned long& s_classCtorCtr;

    // user API
    #include "zCProgMeshProto.inl"
  };

  // sizeof 01h
  class zCProgMeshBuilder {
  public:
    zOPERATORS_DECLARATION()


    zCProgMeshBuilder() {}
    void CreatePMTriPosList()                                                               zCall( 0x005BB6B0 );
    void CalcPrelight( zTLazyMesh&, zTLazyMesh& )                                           zCall( 0x005BBEA0 );
    void CalcPosNormals( zTLazyMesh& )                                                      zCall( 0x005BC050 );
    void CalcTriPlaneList( zTLazyMesh const&, zTLazyMesh& )                                 zCall( 0x005BC190 );
    void CalcSubdivData( zTLazyMesh const&, zTLazyMesh& )                                   zCall( 0x005BC610 );
    void CreateLazySubMesh( int, zTLazyMesh&, zTLazyMesh& )                                 zCall( 0x005BCC50 );
    void CopySubMeshData( unsigned char*&, zTLazyMesh const&, zCProgMeshProto::zCSubMesh* ) zCall( 0x005BD1B0 );
    void CreateFinalPMData( int )                                                           zCall( 0x005BD3C0 );
    void Clear()                                                                            zCall( 0x005BE4E0 );
    int BuildProgMeshProto( zCMesh*, zCProgMeshProto*, zCArray<int>*, int )                 zCall( 0x005BE6D0 );

    // user API
    #include "zCProgMeshBuilder.inl"
  };

  // sizeof 100h
  class zCMeshSoftSkin : public zCProgMeshProto {
  public:
    zCLASS_DECLARATION( zCMeshSoftSkin )

#pragma pack( push, 1 )
    // sizeof 11h
    struct zTWeightEntry {
      zOPERATORS_DECLARATION()

      float weight;            // sizeof 04h    offset 00h
      zVEC3 vertPosOS;         // sizeof 0Ch    offset 04h
      unsigned char nodeIndex; // sizeof 01h    offset 10h

      void zTWeightEntry_OnInit() zCall( 0x0058CD90 );
      zTWeightEntry()             zInit( zTWeightEntry_OnInit() );

      // user API
      #include "zCMeshSoftSkin_zTWeightEntry.inl"
    };
#pragma pack( pop )

    // sizeof 10h
    struct zTNodeWedgeNormal {
      zOPERATORS_DECLARATION()

      zVEC3 normal;  // sizeof 0Ch    offset 00h
      int nodeIndex; // sizeof 04h    offset 0Ch

      zTNodeWedgeNormal() {}

      // user API
      #include "zCMeshSoftSkin_zTNodeWedgeNormal.inl"
    };

    zCArray<int> nodeIndexList;                     // sizeof 0Ch    offset D4h
    zCArray<zCOBBox3D*> nodeOBBList;                // sizeof 0Ch    offset E0h
    zCArray<zTNodeWedgeNormal> nodeWedgeNormalList; // sizeof 0Ch    offset ECh
    unsigned char* vertWeightStream;                // sizeof 04h    offset F8h
    unsigned char* iterator;                        // sizeof 04h    offset FCh

    void zCMeshSoftSkin_OnInit()                                                                              zCall( 0x005C6270 );
    zCMeshSoftSkin() : zCtor( zCProgMeshProto )                                                               zInit( zCMeshSoftSkin_OnInit() );
    void AllocVertWeightStream( int, int )                                                                    zCall( 0x005C6410 );
    void DeleteVertWeightStream()                                                                             zCall( 0x005C6470 );
    void AddNumWeightEntry( int const& )                                                                      zCall( 0x005C64A0 );
    void AddWeightEntry( zTWeightEntry const& )                                                               zCall( 0x005C64C0 );
    void ResetVertWeightIterator()                                                                            zCall( 0x005C6500 );
    int GetVertWeightStreamSize()                                                                             zCall( 0x005C6510 );
    void BuildNodeIndexList()                                                                                 zCall( 0x005C6560 );
    void DeleteNodeOBBList()                                                                                  zCall( 0x005C6720 );
    void BuildNodeOBBList()                                                                                   zCall( 0x005C6790 );
    int __fastcall RenderSoftSkin( zTRenderContext&, zCArray<zMAT4*> const&, zCRenderLightContainer*, float ) zCall( 0x005C7580 );
    static zCObject* _CreateNewInstance()                                                                     zCall( 0x005C1180 );
    static unsigned short GetFileVersion()                                                                    zCall( 0x005C6D50 );
    virtual zCClassDef* _GetClassDef() const                                                                  zCall( 0x005C12D0 );
    virtual ~zCMeshSoftSkin()                                                                                 zCall( 0x005C6300 );
    virtual int Save( zCFileBIN& )                                                                            zCall( 0x005C7060 );
    virtual int Load( zCFileBIN& )                                                                            zCall( 0x005C6D60 );

    // user API
    #include "zCMeshSoftSkin.inl"
  };

  // sizeof 30h
  class zCProgMeshConvertFileHandler : public zCScanDirFileHandler {
  public:
    zOPERATORS_DECLARATION()


    void zCProgMeshConvertFileHandler_OnInit()                         zCall( 0x005C7C80 );
    zCProgMeshConvertFileHandler() : zCtor( zCScanDirFileHandler )     zInit( zCProgMeshConvertFileHandler_OnInit() );
    virtual ~zCProgMeshConvertFileHandler()                            zCall( 0x00426B10 );
    virtual int HandleFile( zSTRING const&, char const*, zFINDDATA )   zCall( 0x005C7D60 );

    // user API
    #include "zCProgMeshConvertFileHandler.inl"
  };

} // namespace Gothic_I_Addon

#endif // __ZPROG_MESH_H__VER1__