#ifndef __ACCOUNT_INFO_H__
#define __ACCOUNT_INFO_H__

#ifndef IF_EDITION_BUS
#define DEFAULT_ADMIN_ACCOUNT   TEXT("\x01\x02\x03\x04\x10\x20\x30\x40")
#else
#define DEFAULT_ADMIN_ACCOUNT   TEXT("superuser")
#endif

#define DEFAULT_ADMIN_PASSWD    TEXT("kb*danmal")

#endif // __ACCOUNT_INFO_H__
