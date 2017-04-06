/*****************************************************************************/
/* Copyright (C) 2005 OSS Nokalva, Inc.  All rights reserved.                */
/*****************************************************************************/
/*****************************************************************************/
/* $Id: CList.h,v 1.1.2.1 2007/05/08 06:28:41 pro Exp $ 
 *
 *  Base class for list objects                                             
 *****************************************************************************/

#ifndef INCLUDE_CLIST
#define INCLUDE_CLIST

/// Basic List functionality, provides base classes for collections of 
/// objects (i.e. BSPs, Units, Sessions, etc)


/// The base class for items that can be stored in the list
/**
    @ingroup HelperComponents1
*/
class CCollectionItem
{
public:
    /// default contructor
    CCollectionItem():m_Prev(0), m_Next(0){};
    /// default destructor 
    virtual ~CCollectionItem() {}; 

    // make the list structure the private business of the list class
    friend class CCollection;
protected:
    CCollectionItem* m_Prev;
    CCollectionItem* m_Next;
};


/// The base list class. 
/**
    @ingroup HelperComponents1
*/
class CCollection
{
public:
    /// defualt contructor
    CCollection(): m_Head(0), m_Tail(0), m_Count(0){};

    /// protected to prevent instances of CCollection and force proper inheritance
protected: 
    virtual ~CCollection() {}; 

private:

    CCollectionItem* m_Head; 
    CCollectionItem* m_Tail; 
    unsigned int m_Count;

    // NO STATE, unless thread safe (TLS) storage is implemented. 
    // CCollectionItem* it; // internal iterator 

public:

    // No "auto" locking/serialization. Let the user of this class 
    // to handle the locking via its own locks (i.e. there might
    // be multiple lists that all locked via one lock, so providing
    // a lock as a member of r the list is not always the best)
    // CSWMR    m_Lock;

    /// Get number of items in the list
    unsigned int GetCount()  const {return m_Count;}

    /// Get the list head item
    CCollectionItem* GetFirst()   const {return m_Head;}

    /// Get the list tail item
    CCollectionItem* GetLast()  const {return m_Tail;}

    /// Move to the next item
    CCollectionItem* GetNext(const CCollectionItem *item) const {return item->m_Next;}

    /// Move to the previos item
    CCollectionItem* GetPrev(const CCollectionItem *item) const {return item->m_Prev;}

    /// Removes the itme from the list but not from the memory
    unsigned int Remove(CCollectionItem* Item) ;

    /// Remove the item from the list AND deletes from the memory
    unsigned int Delete(CCollectionItem* Item) ;

    /// Delete all items (from the list and from the memory)
    void DeleteAll();

    /// adds an item to the list
    virtual bool Add(CCollectionItem* pNew);
};

/// FOR_EACH(anItem, theList)  macro is for looping through all items in a list.
///     anItem - is the type (class) of item the list contains. Must match the class 
///             name without the first 'C'
///     theList - the list varibale representing the list to loop through

/// Usage example:
/// FOR_EACH (BSP, BSPs)
/// {
///     // !!! Do not modify the list itself, i.e. move, sort, delete items !!!
///     BSP->DoSomething();
///     MyProp = BSP->GetProp();
/// }
///  // do not use BSP variable here, it is out of scope 

// !!! Do not use this macro to modify the list itself (i.e. to move, sort, delete items)
#define FOR_EACH(anItem,theList) \
    for (C##anItem* (anItem) = (C##anItem*)(theList).GetFirst(); \
    (anItem); \
    (anItem) = (C##anItem*)(theList).GetNext(anItem))

#endif // INCLUDE_CLIST
