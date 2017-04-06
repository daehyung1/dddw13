/*****************************************************************************/
/* Copyright (C) 2005 OSS Nokalva, Inc.  All rights reserved.                */
/*****************************************************************************/
/*****************************************************************************/
/* $Id: CLock.hpp,v 1.1.2.1 2007/05/08 06:28:41 pro Exp $ 
 *
 *****************************************************************************/

#ifndef CLOCK_HPP_INCLUDED
#define CLOCK_HPP_INCLUDED

#include "environ.h"
#include "CRWSyncObject.hpp"

/**
    @defgroup HelperComponents1 Platform independant helper components
*/

/**
    @ingroup HelperComponents1
    @file
    This file declares helper classes that facilitate use of CRWSyncObject
    synchronization objects in the code:

    - the common interface specified by the abstract CLock class;

    - the utility CWriteLock class that facilitates putting and automatic
      clearing of write locks;

    - the utility CReadLock class that facilitates putting and automatic
      clearing of read locks;
*/

/// Defines the CLock interface.
/**
    @ingroup HelperComponents1

    This abstract class is the common base for the CReadLock and CWriteLock 
    helper classes that wrap CRWSyncObject to facilitate automatic unlocking
    of CRWSyncObject synchronization objects.
*/
class CLock {
public:
    /// The default constructor.
    CLock(): m_pLock(NULL), m_fAcquired(FALSE) {}
    /// The destructor.
    virtual ~CLock() {}

public:
    /// Lock underlying synchronization object using default timeout.
    virtual BOOL Lock(CRWSyncObject* arg_pLock) = 0;
    /// Lock the underlying synchronization object.
    virtual BOOL Lock(CRWSyncObject* arg_pLock, TIMEOUT arg_Timeout) = 0;
    /// Clears the lock that was put by previous call to Lock().
    virtual BOOL Clear() = 0;
    /// Can be used to check if the requested lock was successfully acquired.
    BOOL IsAcquired() const;

protected:
    /// The underlying CRWSyncObject synchronization object.
    CRWSyncObject* m_pLock;
    /// Indicates that the requested lock is successfully acquired.
    BOOL m_fAcquired;
};

/**
    Returns TRUE if the object represents lock that is acquired.
*/
inline BOOL CLock::IsAcquired() const { return m_fAcquired; }

/// Helper class that facilitates the use of read locks.

/**
    @ingroup HelperComponents1

    This class facilitates automatic cleanup of the lock when the
    execution leaves the critical section of the code that is guarded by
    this lock. It exploits the fact that local objects are automatically
    destroyed by the compiler when the execution leaves the corresponding 
    local scope (either due to the normal execution flow or due to the
    stack unwinding on exceptional condition). The supposed use of the class
    is as follows:
    @code
    myMethod() {
        // Begin critical section
        CReaderLock theLock(swmr);

        if (theLock.isAcquired()) {
            <put your critical section here>
        }
        // The compiler will invoke the destructor for the 'theLock' here
        // either the method is exited normally or due to an exception. 
        // It guarantees that the lock is always cleared.
    }
    @endcode
*/
class CReadLock: public CLock {

// Public instance methods
public:
    /// The default constructor.
    /**
        Once the instance is created using the default constructor one has to
        call either Lock(CRWSyncObject* arg_pLock) or 
        Lock(CRWSyncObject* arg_pLock, TIMEOUT arg_iTimeout) to acquire the lock.
    */
    CReadLock(): CLock() {}
    /// Constructs and acquires the read lock using the default timeout.
    CReadLock(CRWSyncObject* arg_pLock);
    /// Constructs and acquires the read lock.
    CReadLock(CRWSyncObject* arg_pLock, TIMEOUT arg_iTimeout);

    /// The destructor clears the read lock if it was acquired.
    virtual ~CReadLock();

    /// Attempts to acquire the read lock using the default timeout.
    BOOL Lock(CRWSyncObject* arg_pLock);
    /// Attempts to acquire the read lock.
    BOOL Lock(CRWSyncObject* arg_pLock, TIMEOUT arg_iTimeout);
    /// Explicitly clears the read lock.
    BOOL Clear();
};

/// Helper class that facilitates the use of write locks.
/**
    @ingroup HelperComponents1

    This class facilitates automatic cleanup of the lock when the
    execution leaves the critical section of the code that is guarded by
    this lock. It exploits the fact that local objects are automatically
    destroyed by the compiler when the execution leaves the corresponding 
    local scope (either due to the normal execution flow or due to the
    stack unwinding on exceptional condition). The supposed use of the class
    is as follows:
    @code
    myMethod() {
        // Begin critical section
        CWriteLock theLock(swmr);

        if (theLock.isAcquired()) {
            <put your critical section here>
            ...
            // Optinally change the write lock to read lock
            theLock.beginRead();
        }
        // The compiler will invoke the destructor for the 'theLock' here
        // either the method is exited normally or due to an exception. 
        // It guarantees that the lock is always cleared.
    }
    @endcode
*/
class CWriteLock: public CLock {

// Public instance methods
public:
    /// The default constructor.
    /**
        Once the instance is created using the default constructor one has to
        call either Lock(CRWSyncObject* arg_pLock) or 
        Lock(CRWSyncObject* arg_pLock, TIMEOUT arg_iTimeout) to acquire the 
        lock.
    */
    CWriteLock(): CLock() {}
    /// Constructs and acquires the write lock using the default timeout 
    CWriteLock(CRWSyncObject* arg_pLock);
    /// Constructs and acquires the write lock.
    CWriteLock(CRWSyncObject* arg_pLock, TIMEOUT arg_iTimeout);

    /// The destructor clears the write lock if it was acquired.
    virtual ~CWriteLock();

    /// Attempts to acquire the write lock using the default timeout.
    BOOL Lock(CRWSyncObject* arg_pLock);
    /// Attempts to acquire the write lock.
    BOOL Lock(CRWSyncObject* arg_pLock, TIMEOUT arg_iTimeout);
    /// Explicitly clears the write lock.
    BOOL Clear();
    /// Attempts to change the write lock to the read lock.
    BOOL beginRead();

protected:
    /// Indicates if the write lock was changed to the read lock by calling the beginRead().
    BOOL m_fIsReadLock;
};

typedef CWriteLock CExclusiveLock;

#endif /* CLOCK_HPP_INCLUDED */
