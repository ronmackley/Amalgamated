//**************************************************************************
//
//	ref_counted.hpp -- Definition of a template class for managing
//					   a pointer an keeping a count of references
//
//  $LastChangedBy$
//  $LastChangedDate$
//  $LastChangedRevision$
//  $HeadURL$
//
//  Copyright (C) 2004-2009 Ronald G. Mackley.
//  All rights reserved.
//
//  $Id$
//
//**************************************************************************

#ifndef REF_COUNTED_HPP
#define REF_COUNTED_HPP


#include <cstdlib>
#include <iostream>

template< typename _T>
class ref_counted
{

	//***************************************************************************
	// Private nested implementation class.
	// The pointer and reference count are held here. The intention is
	// that the outer class checkes the reference count when its dtor
	// is called and destroys the impl when the last reference is
	// removed.

	template< typename _U >
	class _impl
	{
		_U*				d_ptr;
		long			d_refs;
	  public:
				
		_impl( _U* a_ptr ) : d_ptr(a_ptr), d_refs(0)
		{ 
			//std::cout << d_ptr << ':' << d_refs << std::endl;
			(void)addRef(); 
		}
		
		// no default ctor, copy ctor, or assignment operator
		// don't want impl's floating around
		_impl(); 
		_impl( const _impl& );
		_impl& operator=( const _impl& );
		
		~_impl()			{ delete d_ptr; }

		_U*  ptr()			{ return d_ptr; }
		
		long addRef() 		
		{ 
//			std::cout << '+';
			return ++d_refs; 
		}
		
		long removeRef() throw ()
		{
			if( d_refs == 0 )
			{
				std::cerr << "removeRef() no references" << std::endl;
				throw "removeRef() no references";
			}
//			std::cout << '-';
			return --d_refs;
		}
	};
	//***************************************************************************

	typedef	_impl<_T>	impl;
	impl*				d_implPtr;

  public:
	// useful types
	typedef	_T&					RefType;
	typedef	const _T&			ConstRefType;
	
	typedef _T*					PtrType;
	typedef const _T*			ConstPtrType;

	typedef ref_counted<_T>		RefCountedType;

	//
	// default ctor
	//
	// Assign NULL to d_implPtr to indicate it holds nothing
	//
	ref_counted()  : d_implPtr(NULL) { }

	//
	// _T* ctor -- create the impl and the first reference to the pointer
	//
	ref_counted( PtrType a_ptr ) : d_implPtr(NULL)
	{
		set( a_ptr );
	}

	//
	// _T& ctor -- create the impl and the first reference to the object
	//!			   Makes a copy of the passed in reference. No ownership
	//!			   here.
	//
	ref_counted( RefType a_ref ) : d_implPtr(NULL)
	{
		set( new _T( a_ref ) )	;
	}

	//
	// Copy ctor and assignment operator adds references but keeps a single impl
	//
	ref_counted<_T>( const RefCountedType&	a_src )
	{
		// Use the impl passed in to us.
		if( a_src.assigned() )
		{
			this->d_implPtr = a_src.d_implPtr;
			(void)this->d_implPtr->addRef();
		}
	}

	//
	// Default assignment operator
	//
	RefCountedType&	operator=( const RefCountedType&	a_src )
	{		
		// Default ctor initializes d_implPtr. Override iff we a_src is
		// assigned after initialization
		if( a_src.assigned() )
		{
			d_implPtr = a_src.d_implPtr;
			d_implPtr->addRef();	
		}
		return *this;
	}

	//
	// Assignment from pointer to object of held type
	//
	ref_counted&	operator=( PtrType a_ptr ) throw ()
	{
		
		// If we hold an impl, relinquish it and delete it if we're the
		// last impl standing
		if( d_implPtr != NULL && d_implPtr->removeRef() == 0 )
		{
			delete d_implPtr;
		}
		set( a_ptr );
		return *this;
	}

	//
	// ~Destructor manages destroying the impl if the final reference
	//	is deallocated.
	//
	virtual ~ref_counted()
	{
		if( d_implPtr != NULL )
		{
			long refCount =	d_implPtr->removeRef();
			// If we are the last reference to this impl, destroy the impl
			if( refCount == 0 )
			{
				//std::cout << "deleting impl: ";
				//std::cout.setf( std::ios_base::hex, std::ios_base::basefield );
				//std::cout << d_implPtr;
				//std::cout.setf( std::ios_base::dec, std::ios_base::basefield );
				//std::cout << std::endl;
				delete d_implPtr;
			}
		}
	}
	
	//
	// Assign a pointer and cause an _impl to be created
	//
	void	set( PtrType	a_ptr ) throw ()
	{
		// If we're setting the ptr to NULL, do nothing. We don't want
		// refs to NULL impls.
		if( a_ptr == NULL )
		{
			return;	
		}
		
		if( d_implPtr != NULL ) 
		{
			throw "already set";	
		}
		
		d_implPtr = new impl(a_ptr);
	}
	
	
	// test to see of an object is held by this ref_counted
	bool	assigned() const
	{
		return d_implPtr != NULL;
	}
	
	RefCountedType&	operator()()
	{
		RefCountedType* newRefCountedType = new RefCountedType( this );
		return *newRefCountedType;
	}
	
	PtrType	operator->() const
	{
		return d_implPtr->ptr();
	}
	
	RefType operator*() const
	{
		return *(d_implPtr->ptr());
	}
	
	//
	// Access to the pointer or the held object.
	//
	PtrType	ptr() const
	{
		if( d_implPtr == NULL )
		{
			return NULL;
		}
		else
		{
			return d_implPtr->ptr();
		}
	}
	
	//
	// Access to const versions of the pointer of the held object.
	//
	ConstPtrType	constPtr() const
	{
		if( d_implPtr == NULL )
		{
			return NULL;
		}
		else
		{
			return d_implPtr->ptr();
		}
	}

};

#endif // REF_COUNTED_HPP
