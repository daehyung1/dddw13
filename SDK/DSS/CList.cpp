/*****************************************************************************/
/* Copyright (C) 2005 OSS Nokalva, Inc.  All rights reserved.                */
/*****************************************************************************/
/*****************************************************************************/
/* $Id: CList.cpp,v 1.1.2.1 2007/05/08 06:28:41 pro Exp $ 
 *
 *  List class implementation. All objects that can be stored in the list    
 *  should inherit from this class                                           
 *****************************************************************************/

#include "CList.h"

/// Delete all items (from the list and from the memory)
void CCollection::DeleteAll()
{
    while (m_Head) 
        Delete(m_Head);
}

/// Item is just removed from the list, but not deleted from the memory
unsigned int CCollection::Remove(CCollectionItem* Item)
{
    // make sure Item belongs to this list
    CCollectionItem* pli = m_Head;
    while (pli && Item != pli) 
        pli = pli->m_Next;

    if (pli != 0)
    {
        // remove the last one
        if (m_Head == m_Tail)
        {
            m_Head = 0;
            m_Tail = 0;
        }

        // link next with previous and re-assign the head if it was the first one
        if (pli->m_Next)
        {
            pli->m_Next->m_Prev = pli->m_Prev;

            if (pli->m_Prev == 0)
                m_Head = pli->m_Next;

        }

        // link previous with next and re-assign the tail if it was the last one
        if (pli->m_Prev)
        {
            pli->m_Prev->m_Next = pli->m_Next;
            if (pli->m_Next == 0)
                m_Tail = pli->m_Prev;
        }

        // cut off both sides
        pli->m_Next = 0;
        pli->m_Prev = 0;

        m_Count--;
    }

    return m_Count;
};

/// item is both removed from the list and deleted from the memory
unsigned int CCollection::Delete(CCollectionItem* Item) 
{
    if (Item)
    {
        Remove(Item);

        delete Item;
    }

    return m_Count;
};

/// Adds item to the list
bool CCollection::Add(CCollectionItem* pNew)
{
    if (pNew == 0)
        return false;

    if (m_Head == 0)
        m_Head = pNew;
    else
    {
        m_Tail->m_Next = pNew;
        pNew->m_Prev = m_Tail;
    }
    m_Tail = pNew;
    m_Count++;

    return true;
};

