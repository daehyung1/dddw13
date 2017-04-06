/*****************************************************************************/
/* Copyright (C) 2005 OSS Nokalva, Inc.  All rights reserved.                */
/*****************************************************************************/
/*****************************************************************************/
/* $Id: CLock.cpp,v 1.1.2.1 2007/05/08 06:28:41 pro Exp $ 
 *
 *****************************************************************************/

#include "environ.h"
#include "util.hpp"
#include "CLock.hpp"

/**
    @ingroup HelperComponents1
    @file
    This file defines the CReadLock and CWriteLock classes that are helper
    classes to facilitate automatic clearing of synchronization lock when
    the lock is no longer needed.
*/

/*****************************************************************************
 * CReadLock implementation
 *****************************************************************************/

/**
    This constructor initializes the instance and then invokes
    Lock(CRWSyncObject* arg_pLock) to acquire the lock. The user can check
    if the lock is really acquired via the IsAcquired() method.

    @param arg_pLock - (input/output) points to the instance of CRWSyncObject.
*/
CReadLock::CReadLock(CRWSyncObject* arg_pLock)
{
    m_pLock = NULL;
    Lock(arg_pLock);
}

/**
    This constructor initializes the instance and then invokes
    Lock(CRWSyncObject* arg_pLock, TIMEOUT arg_iTimeout) to acquire the lock.
    The user can check if the lock is really acquired via the IsAcquired()
    method.

    @param arg_pLock - (input/output) points to the instance of CRWSyncObject.
    @param arg_Timeout - (input) the timeout in milliseconds.
*/
CReadLock::CReadLock(CRWSyncObject* arg_pLock, TIMEOUT arg_Timeout)
{
    m_pLock = NULL;
    Lock(arg_pLock, arg_Timeout);
}

/**
    The destructor clears the lock by calling the Clear() method.
*/
CReadLock::~CReadLock()
{
    Clear();
}

/**
    Explicitly clears the read lock.

    @return TRUE on success or FALSE on attempt to clear the lock when it
        has not been acquired yet.
*/
BOOL CReadLock::Clear() {
    BOOL result = TRUE;
    if (m_fAcquired) {
        result = m_pLock->endRead();
        m_fAcquired = FALSE;
    }
    m_pLock = NULL;
    return result;
}

/**
    Attempts to acquire the read lock using the synchronization object
    provided.

    @param arg_pLock - (input/output) points to the CRWSyncObject.
    @param arg_iTimeout - (input) the timeout in milliseconds.

    @return TRUE if the read lock is successfully acquired.
*/
BOOL CReadLock::Lock(CRWSyncObject* arg_pLock, TIMEOUT arg_iTimeout)
{
    if (m_pLock != NULL)
        return FALSE;
    else {
        m_pLock = arg_pLock;
        m_fAcquired = m_pLock->beginRead(arg_iTimeout);
        return m_fAcquired;
    }
}

/**
    Attempts to acquire the read lock using the synchronization object
    provided. The timeout to wait for the availability of the lock is
    chosen by the underlying synchronization object.

    @param arg_pLock - (input/output) points to the CRWSyncObject.

    @return TRUE if the read lock is successfully acquired.
*/
BOOL CReadLock::Lock(CRWSyncObject* arg_pLock)
{
    if (m_pLock != NULL)
        return FALSE;
    else {
        m_pLock = arg_pLock;
        m_fAcquired = m_pLock->beginRead();
        return m_fAcquired;
    }
}

/*****************************************************************************
 * CWriteLock implementation
 *****************************************************************************/

/**
    This constructor initializes the instance and then invokes
    Lock(CRWSyncObject* arg_pLock) to acquire the lock. The user can check
    if the lock is really acquired via the IsAcquired() method.

    @param arg_pLock - (input/output) points to the instance of CRWSyncObject.
*/
CWriteLock::CWriteLock(CRWSyncObject* arg_pLock)
{
    m_pLock = NULL;
    Lock(arg_pLock);
}

/**
    This constructor initializes the instance and then invokes
    Lock(CRWSyncObject* arg_pLock, TIMEOUT arg_iTimeout) to acquire the lock.
    The user can check if the lock is really acquired via the IsAcquired()
    method.

    @param arg_pLock - (input/output) points to the instance of CRWSyncObject.
    @param arg_Timeout - (input) max timeout when waiting for the lock is
        available.
*/
CWriteLock::CWriteLock(CRWSyncObject* arg_pLock, TIMEOUT arg_Timeout)
{
    m_pLock = NULL;
    Lock(arg_pLock, arg_Timeout);
}

/**
    The destructor clears the lock by calling the Clear() method.
*/
CWriteLock::~CWriteLock()
{
    Clear();
}

/**
    Explicitly clears the write lock.

    @return TRUE on success or FALSE on attempt to clear the lock when it has
    not been acquired yet.
*/
BOOL CWriteLock::Clear() {
    BOOL result = TRUE;
    if (m_fAcquired) {
        if (m_fIsReadLock) {
            // If the write lock has been changed to the read lock,
            // clear the read lock.
            result = m_pLock->endRead();
            m_fIsReadLock = FALSE;
        } else
            // Clears the write lock.
            result = m_pLock->endWrite();
        m_fAcquired = FALSE;
    }
    m_pLock = NULL;
    return result;
}

/**
    Attempts to acquire the write lock using the synchronization object
    provided.

    @param arg_pLock - (input/output) points to the CRWSyncObject.
    @param arg_iTimeout - (input) the timeout in milliseconds.

    @return TRUE if the write lock is successfully acquired.
*/
BOOL CWriteLock::Lock(CRWSyncObject* arg_pLock, TIMEOUT arg_iTimeout)
{
    if (m_pLock != NULL)
        return FALSE;
    else {
        m_fIsReadLock = FALSE;
        m_pLock = arg_pLock;
        m_fAcquired = m_pLock->beginWrite(arg_iTimeout);
        return m_fAcquired;
    }
}

/**
    Attempts to acquire the write lock using the synchronization object
    provided. The timeout to wait for the availability of the lock is
    chosen by the underlying synchronization object.

    @param arg_pLock - (input/output) points to the CRWSyncObject.

    @return TRUE if the write lock is successfully acquired.
*/
BOOL CWriteLock::Lock(CRWSyncObject* arg_pLock)
{
    if (m_pLock != NULL)
        return FALSE;
    else {
        m_fIsReadLock = FALSE;
        m_pLock = arg_pLock;
        m_fAcquired = m_pLock->beginWrite();
        return m_fAcquired;
    }
}

/**
    Attempts to change the write lock to the read lock. Returns TRUE on
    success. The FALSE indicates that the object does not represent the
    valid write lock and the operation is invalid.

    @return TRUE if the write lock is successfully downgraded to the
        read lock.
*/
BOOL CWriteLock::beginRead() 
{ 
  if (m_fAcquired) {
        m_pLock->endWrite(TRUE);
        m_fIsReadLock = TRUE;
    }

    return m_fAcquired; 
}
