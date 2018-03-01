

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Thu Mar 01 13:57:50 2018
 */
/* Compiler settings for TVWallAX.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __TVWallAXidl_h__
#define __TVWallAXidl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DTVWallAX_FWD_DEFINED__
#define ___DTVWallAX_FWD_DEFINED__
typedef interface _DTVWallAX _DTVWallAX;

#endif 	/* ___DTVWallAX_FWD_DEFINED__ */


#ifndef ___DTVWallAXEvents_FWD_DEFINED__
#define ___DTVWallAXEvents_FWD_DEFINED__
typedef interface _DTVWallAXEvents _DTVWallAXEvents;

#endif 	/* ___DTVWallAXEvents_FWD_DEFINED__ */


#ifndef __TVWallAX_FWD_DEFINED__
#define __TVWallAX_FWD_DEFINED__

#ifdef __cplusplus
typedef class TVWallAX TVWallAX;
#else
typedef struct TVWallAX TVWallAX;
#endif /* __cplusplus */

#endif 	/* __TVWallAX_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_TVWallAX_0000_0000 */
/* [local] */ 

#pragma once
#pragma region Desktop Family
#pragma endregion


extern RPC_IF_HANDLE __MIDL_itf_TVWallAX_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_TVWallAX_0000_0000_v0_0_s_ifspec;


#ifndef __TVWallAXLib_LIBRARY_DEFINED__
#define __TVWallAXLib_LIBRARY_DEFINED__

/* library TVWallAXLib */
/* [control][version][uuid] */ 


EXTERN_C const IID LIBID_TVWallAXLib;

#ifndef ___DTVWallAX_DISPINTERFACE_DEFINED__
#define ___DTVWallAX_DISPINTERFACE_DEFINED__

/* dispinterface _DTVWallAX */
/* [uuid] */ 


EXTERN_C const IID DIID__DTVWallAX;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("287392D1-CAFD-4EBA-9B4C-E87C491F3638")
    _DTVWallAX : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DTVWallAXVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DTVWallAX * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DTVWallAX * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DTVWallAX * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DTVWallAX * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DTVWallAX * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DTVWallAX * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DTVWallAX * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _DTVWallAXVtbl;

    interface _DTVWallAX
    {
        CONST_VTBL struct _DTVWallAXVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DTVWallAX_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DTVWallAX_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DTVWallAX_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DTVWallAX_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DTVWallAX_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DTVWallAX_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DTVWallAX_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DTVWallAX_DISPINTERFACE_DEFINED__ */


#ifndef ___DTVWallAXEvents_DISPINTERFACE_DEFINED__
#define ___DTVWallAXEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DTVWallAXEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__DTVWallAXEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("8E0C406E-DBCD-4EE0-8F89-618CBDEF4765")
    _DTVWallAXEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DTVWallAXEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DTVWallAXEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DTVWallAXEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DTVWallAXEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DTVWallAXEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DTVWallAXEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DTVWallAXEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DTVWallAXEvents * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _DTVWallAXEventsVtbl;

    interface _DTVWallAXEvents
    {
        CONST_VTBL struct _DTVWallAXEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DTVWallAXEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DTVWallAXEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DTVWallAXEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DTVWallAXEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DTVWallAXEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DTVWallAXEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DTVWallAXEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DTVWallAXEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_TVWallAX;

#ifdef __cplusplus

class DECLSPEC_UUID("C639E623-F7C2-445E-B889-9D72B467D4F4")
TVWallAX;
#endif
#endif /* __TVWallAXLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


