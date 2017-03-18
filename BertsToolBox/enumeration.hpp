#ifndef _ENUMERATION_H_
#define _ENUMERATION_H_

template <class _T>
class CEnumeration
{
public:
	virtual bool hasMoreElements() = 0;
	virtual _T nextElement() =0;
};

#endif


