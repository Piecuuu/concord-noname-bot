#include "db.h"
#include "bot.h"
#include "config.h"

static void db_init_prepared_statements(PGconn* conn) {

}

PGconn* db_connect() {
  PGconn* conn = PQconnectdb(bot_global->config->db_conn_str);
  if(PQstatus(conn) != CONNECTION_OK) {
    log_fatal("Error while connecting to the database: %s", PQerrorMessage(conn));
    PQfinish(conn);
    exit(1);
  }

  log_info("Connected to the database `%s`", PQdb(conn));
  log_info("Initialising prepared statements...");

  db_init_prepared_statements(conn);

  log_info("Initialised prepared statements.");

  bot_global->db_conn = conn;
}

