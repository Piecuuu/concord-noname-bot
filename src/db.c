#include "db.h"
#include "bot.h"
#include "config.h"

static void db_check_prepare(PGresult* prepared_result, PGconn* conn) {
  if(PQresultStatus(prepared_result) != PGRES_COMMAND_OK) {
    log_fatal("Failed to prepare statement: %s", PQerrorMessage(conn));
    PQclear(prepared_result);
    PQfinish(conn);
    exit(1);
  }
  PQclear(prepared_result);
}

static void db_check_init_table(PGresult* res, PGconn* conn) {
  if(PQresultStatus(res) != PGRES_COMMAND_OK) {
    log_fatal("Failed to prepare tables: %s", PQerrorMessage(conn));
    PQclear(res);
    PQfinish(conn);
    exit(1);
  }
  PQclear(res);
}

static void db_init_prepared_statements(PGconn* conn) {
  PGresult* res;
  Oid param_types[15];

  //param_types[0] = 25;
  //param_types[1] = 25;
  //res = PQprepare(conn, "test_prepared", "INSERT INTO public.test (\"user\", message) VALUES ($1, $2)", 2, param_types);
  //db_check_prepare(res, conn);
}

void db_init_tables(PGconn* conn) {
  PGresult* res;
  //res = PQexec(conn, "CREATE TABLE IF NOT EXISTS public.test (id INTEGER PRIMARY KEY GENERATED ALWAYS AS IDENTITY, \"user\" VARCHAR(20) NOT NULL, message TEXT NOT NULL)");
  //db_check_init_table(res, conn);
}

PGconn* db_connect() {
  PGconn* conn = PQconnectdb(bot_global->config->db_conn_str);
  if(PQstatus(conn) != CONNECTION_OK) {
    log_fatal("Error while connecting to the database: %s", PQerrorMessage(conn));
    PQfinish(conn);
    exit(1);
  }

  log_info("Connected to the database `%s`", PQdb(conn));

  log_info("Initialising tables...");
  db_init_tables(conn);
  log_info("Initialised tables.");

  log_info("Initialising prepared statements...");
  db_init_prepared_statements(conn);
  log_info("Initialised prepared statements.");

  bot_global->db_conn = conn;
}

