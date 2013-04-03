 class noncopyable
  {
   protected:
      noncopyable() {}
      ~noncopyable() {}
   private:  // emphasize the following members are private
      noncopyable( const noncopyable& );
      const noncopyable& operator=( const noncopyable& );
  };

template<class T> class intrusive_ptr {
	T * _ptr;
public:

	typedef T element_type;

	intrusive_ptr() : _ptr(NULL) // never throws
	{}

	intrusive_ptr(T * p, bool add_ref = true) : _ptr(p)
	{ if(add_ref && _ptr) intrusive_ptr_add_ref(_ptr); }

	intrusive_ptr(intrusive_ptr const & r) : _ptr(r._ptr)
	{
		if(_ptr) intrusive_ptr_add_ref(_ptr);
	}
    template<class Y> intrusive_ptr(intrusive_ptr<Y> const & r) : _ptr((T*)r._ptr)
	{
		if(_ptr) intrusive_ptr_add_ref(_ptr);
	}

	~intrusive_ptr()
	{
		if(_ptr) intrusive_ptr_release(_ptr);
	}

	intrusive_ptr & operator=(intrusive_ptr const & r)
	{
		intrusive_ptr(r).swap(*this);
		return *this;
	}
	template<class Y> intrusive_ptr & operator=(intrusive_ptr<Y> const & r)
	{
		intrusive_ptr(r).swap(*this);
		return *this;
	}
	intrusive_ptr & operator=(T * r)
	{
		intrusive_ptr(r).swap(*this);
		return *this;
	}

	void reset() { intrusive_ptr().swap(*this); }
	void reset(T * r) { intrusive_ptr(r).swap(*this); }

	T & operator*() const { return *_ptr; } // never throws
	T * operator->() const { return _ptr; } // never throws
	T * get() const { return _ptr; } // never throws

	void swap(intrusive_ptr & b){ // never throws
		T * tmp = b._ptr;
		b._ptr = _ptr;
		_ptr = tmp;
	}
};

template<class T, class U>
bool operator==(intrusive_ptr<T> const & a, intrusive_ptr<U> const & b) // never throws
{ return (a.get() == b.get()); }

template<class T, class U>
bool operator!=(intrusive_ptr<T> const & a, intrusive_ptr<U> const & b) // never throws
{ return (a.get() != b.get()); }

template<class T>
bool operator==(intrusive_ptr<T> const & a, T * b) // never throws
{ return (a.get() == b); }

template<class T>
bool operator!=(intrusive_ptr<T> const & a, T * b) // never throws
{ return (a.get() != b); }

template<class T>
bool operator==(T * a, intrusive_ptr<T> const & b) // never throws
{ return (a == b.get()); }

template<class T>
bool operator!=(T * a, intrusive_ptr<T> const & b) // never throws
{ return (a != b.get()); }

template<class T, class U>
bool operator<(intrusive_ptr<T> const & a, intrusive_ptr<U> const & b) // never throws
{ return std::less<T *>()(a.get(), b.get()); }

template<class T> void swap(intrusive_ptr<T> & a, intrusive_ptr<T> & b) // never throws
{ a.swap(b); }

template<class T> T * get_pointer(intrusive_ptr<T> const & p) // never throws
{ return p.get(); }

template<class T, class U>
intrusive_ptr<T> static_pointer_cast(intrusive_ptr<U> const & r) // never throws
{ return intrusive_ptr<T>(static_cast<T*>(r.get())); }

template<class T, class U>
intrusive_ptr<T> const_pointer_cast(intrusive_ptr<U> const & r) // never throws
{ return intrusive_ptr<T>(const_cast<T*>(r.get())); }

template<class T, class U>
intrusive_ptr<T> dynamic_pointer_cast(intrusive_ptr<U> const & r) // never throws
{ return intrusive_ptr<T>(dynamic_cast<T*>(r.get())); }

template<class E, class T, class Y>
std::basic_ostream<E, T> & operator<< (std::basic_ostream<E, T> & os, intrusive_ptr<Y> const & p)
{ os << p.get(); return os; }
