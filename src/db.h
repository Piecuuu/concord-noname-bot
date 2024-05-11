#ifndef DB_H
#define DB_H

#include <libpq-fe.h>

PGconn* db_connect();

#endif // DB_H
